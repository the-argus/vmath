/*
 * 3x3 Matrix
 * 9 single precision floating point values stored in SIMD registers, arranged
 * in 3 rows of 3.
 */
#ifndef __VMATH_DECL_MAT3X3_F32_H
#define __VMATH_DECL_MAT3X3_F32_H

#include "vmath/decl/vec2_f32.h"
#include "vmath/decl/vec3_f32.h"
#include "vmath/internal/intrinsics.h"

typedef struct
{
	vm_v3fs_t r1;
	vm_v3fs_t r2;
	vm_v3fs_t r3;
} vm_mat3x3fs_t;

typedef struct
{
	vm_v3f_t _r1;
	vm_v3f_t _r2;
	vm_v3f_t _r3;
} vm_mat3x3f_t;

/// Load a 3x3 matrix from memory
VMATH_INLINE_DECL vm_mat3x3f_t vm_load_mat3x3f(const vm_mat3x3fs_t* matrix);

/// Load a 3x3 matrix from memory, float buffer variant
VMATH_INLINE_DECL vm_mat3x3f_t vm_loadb_mat3x3f(const vm_float32_t matrix[9]);

/// Store a 3x3 matrix to memory
VMATH_INLINE_DECL void vm_store_mat3x3f(vm_mat3x3fs_t* output,
										vm_mat3x3f_t matrix);
/// Store a 3x3 matrix to memory, float buffer variant
VMATH_INLINE_DECL void vm_storeb_mat3x3f(vm_float32_t output[9],
										 vm_mat3x3f_t matrix);

/// Load the identity transform into registers
VMATH_INLINE_DECL vm_mat3x3f_t vm_load_identity_mat3x3f(void);

/// Create a matrix describing a rotation of some degrees in radians
VMATH_INLINE_DECL vm_mat3x3f_t vm_load_rotation_mat3x3f(vm_float32_t theta);

/// Create a transform describing a translation along local X and Y axes
VMATH_INLINE_DECL vm_mat3x3f_t vm_load_translation_mat3x3f(vm_float32_t x,
														   vm_float32_t y);
/// Create a transform describing a translation along local X and Y axes, vector
/// variant
VMATH_INLINE_DECL vm_mat3x3f_t vm_load_translationv_mat3x3f(vm_v2f_t offset);

/// Create a transform describing a scaling along local X and Y axes
VMATH_INLINE_DECL vm_mat3x3f_t vm_load_scale_mat3x3f(vm_float32_t x,
													 vm_float32_t y);
/// Create a transform describing a scaling along local X and Y axes, vector
/// variant
VMATH_INLINE_DECL vm_mat3x3f_t vm_load_scalev_mat3x3f(vm_v2f_t offset);

/// Multiply two 3x3 matrices
VMATH_INLINE_DECL vm_mat3x3f_t vm_mul_mat3x3f(vm_mat3x3f_t a, vm_mat3x3f_t b);

/*
 * Extension to Vector2 api
 */

VMATH_INLINE_DECL vm_v2f_t vm_transform_mat3x3_v2f(vm_v2f_t vec,
												   vm_mat3x3f_t transform);

#endif
