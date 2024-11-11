const std = @import("std");

const decl_begin_template = "VMATH_EXTERN_CONST vm_uintinit_v4f vm_v4_selectmask_";
const impl_begin_template = "const vm_uintinit_v4f vm_v4_selectmask_";
// 0001 = {{0,         0,          0,          0xFFFFFFFF}};

fn replace4With(allocator: std.mem.Allocator, size: u64, str: []const u8) ![]u8 {
    var builder = std.ArrayList(u8).init(allocator);
    errdefer builder.deinit();
    const numstr = try std.fmt.allocPrint(allocator, "{}", .{size});
    defer allocator.free(numstr);
    for (str) |char| {
        if (char != '4') {
            try builder.append(char);
        } else {
            try builder.appendSlice(numstr);
        }
    }
    return builder.toOwnedSlice();
}

pub fn generateDeclsForBinaryNumberOfSize(allocator: std.mem.Allocator, size: u64) ![]u8 {
    var builder = std.ArrayList(u8).init(allocator);
    errdefer builder.deinit();

    const decl_begin = try replace4With(allocator, size, decl_begin_template);
    defer allocator.free(decl_begin);

    const binary_number_scratch = try allocator.alloc(u8, size);
    defer allocator.free(binary_number_scratch);

    const num_binary_nums = @as(u64, 1) << @intCast(size);
    for (0..num_binary_nums) |index| {
        try builder.appendSlice(decl_begin);
        const printed = try std.fmt.bufPrint(binary_number_scratch, "{b}", .{index});
        try builder.appendNTimes('0', size - printed.len);
        try builder.appendSlice(printed);
        try builder.appendSlice(";\n");
    }

    return builder.toOwnedSlice();
}

pub fn generateImplForBinaryNumberOfSize(allocator: std.mem.Allocator, size: u64) ![]u8 {
    var builder = std.ArrayList(u8).init(allocator);
    errdefer builder.deinit();
    var binary_number_string_scratch = std.ArrayList(u8).init(allocator);
    defer binary_number_string_scratch.deinit();

    const impl_begin = try replace4With(allocator, size, impl_begin_template);
    defer allocator.free(impl_begin);

    const binary_number_scratch = try allocator.alloc(u8, size);
    defer allocator.free(binary_number_scratch);

    const num_binary_nums = @as(u64, 1) << @intCast(size);
    for (0..num_binary_nums) |index| {
        try builder.appendSlice(impl_begin);
        const printed = try std.fmt.bufPrint(binary_number_scratch, "{b}", .{index});
        // append to both scratch and str to keep copy
        try builder.appendNTimes('0', size - printed.len);
        try builder.appendSlice(printed);
        try binary_number_string_scratch.appendNTimes('0', size - printed.len);
        try binary_number_string_scratch.appendSlice(printed);
        // endcap
        try builder.appendSlice(" = {{");

        for (binary_number_string_scratch.items) |digit| {
            switch (digit) {
                '0' => try builder.appendSlice("0,"),
                '1' => try builder.appendSlice("0xFFFFFFFF,"),
                else => {
                    @panic("bad binary print");
                },
            }
        }
        binary_number_string_scratch.clearRetainingCapacity();

        try builder.appendSlice("}};\n");
    }

    return builder.toOwnedSlice();
}
