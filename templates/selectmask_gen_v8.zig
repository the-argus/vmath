const std = @import("std");
const h_filename = "selectmask_decls.h";
const impl_filename = "selectmask_impl.h";

const generator = @import("selectmask_gen.zig");

pub fn hFileContents(ally: std.mem.Allocator) ![]u8 {
    return try generator.generateDeclsForBinaryNumberOfSize(ally, 8);
}

pub fn implFileContents(ally: std.mem.Allocator) ![]u8 {
    return try generator.generateImplForBinaryNumberOfSize(ally, 8);
}
