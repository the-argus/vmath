/*
 * 4x4 Matrix
 * 16 single precision floating point values stored in SIMD registers, arranged
 * in 4 rows of 4.
 */
#ifndef __VMATH_DECL_MAT4X4_F32_H
#define __VMATH_DECL_MAT4X4_F32_H

#include "vmath/decl/vec16_f32.h"
#include "vmath/decl/vec3_f32.h"
#include "vmath/internal/intrinsics.h"

typedef struct
{
	vm_float32_t rows[4][4];
} vm_mat4x4fs_t;

#ifdef VMATH_SIMD_ENABLED
typedef vm_v16f_t vm_mat4x4f_t;
#else
typedef struct
{
	/// Implementation detail in scalar fallback mode
	vm_v16f_t _inner;
} vm_mat4x4f_t;
#endif

/// Load a 4x4 matrix from memory
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_mat4x4f(const vm_mat4x4fs_t* matrix);

/// Load a 3x3 matrix from memory, float buffer variant
VMATH_INLINE_DECL vm_mat4x4f_t vm_loadb_mat4x4f(const vm_float32_t matrix[16]);

/// Store a 3x3 matrix to memory
VMATH_INLINE_DECL void vm_store_mat4x4f(vm_mat4x4fs_t* output,
										vm_mat4x4f_t matrix);
/// Store a 3x3 matrix to memory, float buffer variant
VMATH_INLINE_DECL void vm_storeb_mat4x4f(vm_float32_t output[16],
										 vm_mat4x4f_t matrix);

/// Load the identity transform into registers
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_identity_mat4x4f(void);

/// Create a matrix describing a rotation around the X axis in radians
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_rotation_x_mat4x4f(vm_float32_t theta);
/// Create a matrix describing a rotation around the Y axis in radians
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_rotation_y_mat4x4f(vm_float32_t theta);
/// Create a matrix describing a rotation around the Z axis in radians
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_rotation_z_mat4x4f(vm_float32_t theta);
/// Create a matrix describing rotation on the Y, X, and Z axes, applied in that
/// order
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_rotation_pitch_yaw_roll_mat4x4f(
	vm_float32_t pitch, vm_float32_t yaw, vm_float32_t roll);
/// Create a matrix describing rotation on the Y, X, and Z axes, applied in that
/// order. X, Y, and Z components of input vector are used for pitch/yaw/roll.
VMATH_INLINE_DECL vm_mat4x4f_t
vm_load_rotation_pitch_yaw_rollv_mat4x4f(vm_v3f_t angles);

/// Create a transform describing a translation along X, Y, and Z axes
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_translation_mat4x4f(vm_float32_t x,
														   vm_float32_t y,
														   vm_float32_t z);
/// Create a transform describing a translation along X, Y, and Z axes, vector
/// variant
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_translationv_mat4x4f(vm_v3f_t offset);

/// Create a transform describing a scaling along X, Y, and Z axes
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_scale_mat4x4f(vm_float32_t x,
													 vm_float32_t y,
													 vm_float32_t z);
/// Create a transform describing a scaling along X, Y, and Z axes, vector
/// variant
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_scalev_mat4x4f(vm_v3f_t scale);

/// Multiply two 3x3 matrices
VMATH_INLINE_DECL vm_mat4x4f_t vm_mul_mat4x4f(vm_mat4x4f_t a, vm_mat4x4f_t b);

/*
 * Extension to Vector3 api
 */

VMATH_INLINE_DECL vm_v3f_t vm_transform_mat4x4_v3f(vm_v3f_t vec,
												   vm_mat4x4f_t transform);

#endif
