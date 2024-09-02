const std = @import("std");
const builtin = @import("builtin");
const zcc = @import("compile_commands");
const app_name = "vmath";

const test_flags = &[_][]const u8{
    "-std=c99", // need inline and restrict
    "-pedantic",
    "-Wall",
    "-Iinclude/",
    // "-march=x86-64-v3", // x84-64 with AVX simd and stuff
};

const test_source_files = &[_][]const u8{
    "vec2_f32.c",
};

pub fn build(b: *std.Build) !void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    // targets which will only build with the run_tests and install_tests steps
    var tests = std.ArrayList(*std.Build.Step.Compile).init(b.allocator);
    defer tests.deinit();

    b.installDirectory(.{
        .source_dir = .{ .src_path = .{
            .sub_path = "include/vmath/",
            .owner = b,
        } },
        .install_dir = .header,
        .install_subdir = "vmath/",
    });

    for (test_source_files) |source_file| {
        var test_exe = b.addExecutable(.{
            .name = std.fs.path.stem(source_file),
            .optimize = optimize,
            .target = target,
        });
        test_exe.addCSourceFile(.{
            .file = .{ .src_path = .{
                .owner = b,
                .sub_path = b.pathJoin(&.{ "tests", source_file }),
            } },
            .flags = test_flags,
        });
        test_exe.linkLibCpp();
        test_exe.linkSystemLibrary("check");
        try tests.append(test_exe);
    }

    const run_tests_step = b.step("run_tests", "Compile and run all the tests");
    const install_tests_step = b.step("install_tests", "Install all the tests but don't run them");
    for (tests.items) |test_exe| {
        const test_install = b.addInstallArtifact(test_exe, .{});
        install_tests_step.dependOn(&test_install.step);

        const test_run = b.addRunArtifact(test_exe);
        if (b.args) |args| {
            test_run.addArgs(args);
        }
        run_tests_step.dependOn(&test_run.step);
    }

    try @import("templates/build.zig").generate(b, "code");

    zcc.createStep(b, "cdb", try tests.toOwnedSlice());
}
