const std = @import("std");
const builtin = @import("builtin");

const folders = &[_][]const u8{
    "v2f",
    "v4f",
    "v8f",
    "v16f",
};

const TemplateConfig = struct {
    file_name_replacement_index: u64 = 0,
    replacements: []const []const u8,
    sets: []const []const []const u8,

    // checks to make sure each set in sets has the same number of things to
    // replace as there are replacements
    pub fn validate(self: @This()) bool {
        for (self.sets) |set| {
            if (set.len != self.replacements.len) {
                return false;
            }
        }
        return true;
    }
};

/// Create and register a step to generate some header files
/// from templated code
pub fn generate(b: *std.Build, name: []const u8) !void {
    const step = b.allocator.create(std.Build.Step) catch @panic("Allocation failure, probably OOM");

    step.* = std.Build.Step.init(.{
        .id = .custom,
        .name = "cc_file",
        .makeFn = generateCode,
        .owner = b,
    });

    const generate_step = b.step(name, "Create compile_commands.json");
    generate_step.dependOn(step);
}

fn generateCode(step: *std.Build.Step, prog_node: std.Progress.Node) anyerror!void {
    _ = prog_node;

    const TemplatePair = struct {
        has_json: bool,
        has_h: bool,
    };

    var completed_stems = std.ArrayList([]const u8).init(step.owner.allocator);
    defer completed_stems.deinit();

    for (folders) |folder| {
        var pairs = std.StringHashMap(TemplatePair).init(step.owner.allocator);
        defer pairs.deinit();
        const root = step.owner.path(step.owner.pathJoin(&.{ "templates", folder })).getPath(step.owner);
        var directory: std.fs.Dir = std.fs.openDirAbsolute(root, std.fs.Dir.OpenDirOptions{ .iterate = true }) catch |err| {
            std.log.warn("Invalid folder templates/{s}, got error {}, skipping", .{ folder, err });
            continue;
        };
        defer directory.close();
        var iterator = directory.iterate();
        while (try iterator.next()) |entry| {
            switch (entry.kind) {
                .file => {
                    const extension = std.fs.path.extension(entry.name);
                    const stem = std.fs.path.stem(entry.name);
                    const is_json = std.mem.eql(u8, extension, ".json");
                    const is_h = std.mem.eql(u8, extension, ".h");
                    if (!is_json and !is_h) {
                        std.log.warn("File {s} with unknown extension {s} found in {s} folder, skipping", .{ entry.name, extension, root });
                        continue;
                    }

                    const owned_key = step.owner.pathJoin(&.{ folder, stem });
                    const getOrPutResult = try pairs.getOrPut(owned_key);
                    if (!getOrPutResult.found_existing) {
                        getOrPutResult.value_ptr.* = TemplatePair{
                            .has_h = is_h,
                            .has_json = is_json,
                        };
                    } else {
                        const template_pair: TemplatePair = getOrPutResult.value_ptr.*;
                        std.debug.assert(!template_pair.has_h or !template_pair.has_json);
                        std.debug.assert(template_pair.has_h != template_pair.has_json);
                        if ((template_pair.has_json and is_h) or (template_pair.has_h and is_json)) {
                            _ = pairs.remove(owned_key);
                            try completed_stems.append(owned_key);
                        }
                    }
                },
                else => {
                    std.log.warn("Non-file {s} found in folder {s}, skipping", .{ entry.name, root });
                },
            }
        }
    }

    // okay we collected all the names of templates, not including file extensions.
    // open up the .json and .h versions of these and perform text replacement

    // output directory for re-use by all loop iterations
    var output_dir = try std.fs.openDirAbsolute(step.owner.path("include/vmath/generated").getPath(step.owner), .{ .access_sub_paths = true });
    defer output_dir.close();

    // use each pair of files to replace and then write to a subfolder in output_dir
    for (completed_stems.items) |stem| {
        const stem_with_h = step.owner.fmt("{s}.h", .{stem});
        defer step.owner.allocator.free(stem_with_h);
        const h_path = step.owner.path(step.owner.pathJoin(&.{ "templates", stem_with_h })).getPath(step.owner);
        defer step.owner.allocator.free(h_path);
        const stem_with_json = step.owner.fmt("{s}.json", .{stem});
        defer step.owner.allocator.free(stem_with_json);
        const json_path = step.owner.path(step.owner.pathJoin(&.{ "templates", stem_with_json })).getPath(step.owner);
        defer step.owner.allocator.free(json_path);
        const header_template = try std.fs.openFileAbsolute(h_path, .{});
        defer header_template.close();
        const json = try std.fs.openFileAbsolute(json_path, .{});
        defer json.close();
        const json_contents = try json.readToEndAlloc(step.owner.allocator, 100000);
        defer step.owner.allocator.free(json_contents);
        const template_config_parsed = try std.json.parseFromSlice(TemplateConfig, step.owner.allocator, json_contents, std.json.ParseOptions{});
        defer template_config_parsed.deinit();
        const template_config = &template_config_parsed.value;
        if (!template_config.validate()) {
            std.log.warn("Invalid config in json file {s}, skipping", .{json_path});
            continue;
        }
        const header_contents = try header_template.readToEndAlloc(step.owner.allocator, 100000);
        defer step.owner.allocator.free(header_contents);

        // write modified header_contents to a file in include/vmath/generated/
        // start by making the directory before replacements happen
        const subdir_name = std.fs.path.dirname(stem) orelse {
            std.log.err("no dirname could be extracted from {s}, skipping", .{stem});
            continue;
        };
        output_dir.makeDir(subdir_name) catch |err| {
            if (err != std.fs.Dir.MakeError.PathAlreadyExists) {
                std.log.err("Parsed file pair {s} successfully but unable to create output directory: {}", .{ stem, err });
                continue;
            }
        };

        // text replacement time
        for (template_config.sets) |replacement_set| {
            var replacement_contents = header_contents;
            for (replacement_set, 0..) |replacement, index| {
                const needle = template_config.replacements[index];
                const replaced_buffer = try std.mem.replaceOwned(u8, step.owner.allocator, replacement_contents, needle, replacement);
                // original contents no longer needed, we've allocated a new one with the first thing replaced
                if (replacement_contents.ptr != header_contents.ptr) {
                    step.owner.allocator.free(replacement_contents);
                }
                // replace this one on the next time around
                replacement_contents = replaced_buffer;
            }
            // replacement_contents all good now
            const file_subpath = step.owner.fmt("{s}_{s}{s}", .{ stem, replacement_set[template_config.file_name_replacement_index], ".h" });
            output_dir.deleteFile(file_subpath) catch |err| {
                switch (err) {
                    std.fs.Dir.DeleteFileError.FileNotFound => {},
                    else => {
                        std.log.err("attempted to delete file to clear cache, got err {}, aborting", .{err});
                        return;
                    },
                }
            }; // always create a new one
            const output_file = output_dir.createFile(file_subpath, .{}) catch |err| {
                std.log.err("got err {}", .{err});
                return err;
            };
            defer output_file.close();
            const written = try output_file.write(replacement_contents);
            std.debug.assert(written == replacement_contents.len);
        }
    }
}
