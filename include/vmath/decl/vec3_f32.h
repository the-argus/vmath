/*
 * 3-Element Vector
 * A wrapper around vec4. It is only a distinct type from vec4 when using scalar
 * fallback.
 * Most vec3 functions just call the vec4 counterparts, with the exception of
 * special operations like length etc.
 *
 * Since vec3 storage size does not match 1:1 with an x86 store instruction,
 * load/stores to a vec3 require more instructions than a vec4 or vec2.
 */
#ifndef __VMATH_DECL_VEC3_F32_H
#define __VMATH_DECL_VEC3_F32_H

#include "vmath/decl/vec4_f32.h"

/// vec3 storage type
typedef struct
{
	vm_float32_t x;
	vm_float32_t y;
	vm_float32_t z;
} vm_v3fs_t;

#ifdef VMATH_SIMD_ENABLED
typedef vm_v4f_t vm_v3f_t;
#else
typedef struct
{
	/// Non-simd implementation detail
	vm_v3fs_t _inner;
} vm_v3f_t;
#endif

/// Load a vec3 from memory.
VMATH_INLINE_DECL vm_v3f_t vm_load_v3f(const vm_v3fs_t* vec);
/// Load a vec3 from memory as a float buffer.
VMATH_INLINE_DECL vm_v3f_t vm_loadb_v3f(const vm_float32_t vec[3]);
/// Store a vec3 into memory.
VMATH_INLINE_DECL void vm_store_v3f(vm_v3fs_t* output, vm_v3f_t vector);
/// Store a vec3 into memory as a float buffer.
VMATH_INLINE_DECL void vm_storeb_v3f(vm_float32_t output[3], vm_v3f_t vector);

/// Load a float32 into all elements of a vec4
VMATH_INLINE_DECL vm_v3f_t vm_splat_v3f(vm_float32_t fill);

/// Convert a vector4 to a vector3 by removing the last element
VMATH_INLINE_DECL vm_v3f_t vm_shave4_v3f(vm_v4f_t vec);

/// Add two three-element vectors together, componentwise
VMATH_INLINE_DECL vm_v3f_t vm_add_v3f(vm_v4f_t a, vm_v4f_t b);
/// Subtract a three-element vectors from another, componentwise
VMATH_INLINE_DECL vm_v3f_t vm_sub_v3f(vm_v4f_t a, vm_v4f_t b);
/// Multiply two three-element vectors together, componentwise
VMATH_INLINE_DECL vm_v3f_t vm_mul_v3f(vm_v4f_t a, vm_v4f_t b);
/// Divide a three-element vectors by another, componentwise
VMATH_INLINE_DECL vm_v3f_t vm_div_v3f(vm_v4f_t a, vm_v4f_t b);

/// Add a constant float32 value to all the elements of a 3 element vector
VMATH_INLINE_DECL vm_v3f_t vm_addc_v3f(vm_v4f_t a, vm_float32_t b);
/// Subtract a constant float32 value from all the elements of a 3 element
/// vector
VMATH_INLINE_DECL vm_v3f_t vm_subc_v3f(vm_v4f_t a, vm_float32_t b);
/// Multiply all the elements of a 3 element vector by a constant float32 value
VMATH_INLINE_DECL vm_v3f_t vm_mulc_v3f(vm_v4f_t a, vm_float32_t b);
/// Divide all the elements of a 3 element vector by a constant float32 value
VMATH_INLINE_DECL vm_v3f_t vm_divc_v3f(vm_v4f_t a, vm_float32_t b);

#endif
