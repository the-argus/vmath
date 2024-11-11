const std = @import("std");

const decl_begin_template = "VMATH_EXTERN_CONST vm_uintinit_v4f vm_v4_selectmask_";
const impl_begin_template = "const vm_uintinit_v4f vm_v4_selectmask_";
// 0001 = {{0,         0,          0,          0xFFFFFFFF}};

fn replace4With(allocator: std.mem.Allocator, size: u64, str: []const u8) ![]u8 {
    var builder = std.ArrayList(u8).init(allocator);
    try builder.resize(str.len);
    defer builder.deinit();
    for (str) |char| {
        if (char != '4') {
            try builder.append(char);
        } else {
            const offset: u8 = @intCast(size);
            try builder.append('0' + offset);
        }
    }
    return builder.toOwnedSlice();
}

pub fn generateDeclsForBinaryNumberOfSize(allocator: std.mem.Allocator, size: u64) ![]u8 {
    var builder = std.ArrayList(u8).init(allocator);
    defer builder.deinit();

    // (template + the binary representation of the number + 5 for extra newline and semicolon and some to be safe)
    const linelength = (decl_begin_template.len + size + 5);
    try builder.resize(linelength * size);

    const decl_begin = try replace4With(allocator, size, decl_begin_template);
    defer allocator.free(decl_begin);

    const binary_number_scratch = try allocator.alloc(u8, size);
    defer allocator.free(binary_number_scratch);

    for (0..size) |index| {
        try builder.appendSlice(decl_begin);
        _ = try std.fmt.bufPrint(binary_number_scratch, "{b}", .{index});
        try builder.appendSlice(binary_number_scratch);
        try builder.appendSlice(";\n");
    }

    return builder.toOwnedSlice();
}

pub fn generateImplForBinaryNumberOfSize(allocator: std.mem.Allocator, size: u64) ![]u8 {
    var builder = std.ArrayList(u8).init(allocator);
    defer builder.deinit();

    const impl_begin = try replace4With(allocator, size, impl_begin_template);
    defer allocator.free(impl_begin);

    const binary_number_scratch = try allocator.alloc(u8, size);
    defer allocator.free(binary_number_scratch);

    for (0..size) |index| {
        try builder.appendSlice(impl_begin);
        @memset(binary_number_scratch, 0);
        _ = try std.fmt.bufPrint(binary_number_scratch, "{b}", .{index});
        try builder.appendSlice(binary_number_scratch);
        try builder.appendSlice(" = {{");

        for (binary_number_scratch) |digit| {
            switch (digit) {
                '0', 0 => try builder.appendSlice("0,"),
                '1' => try builder.appendSlice("0xFFFFFFFF,"),
                else => {
                    @panic("bad binary print");
                },
            }
        }

        try builder.appendSlice("}};\n");
    }

    return builder.toOwnedSlice();
}
