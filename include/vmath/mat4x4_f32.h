#ifndef __VMATH_MAT4X4_F32_H
#define __VMATH_MAT4X4_F32_H

#include "vmath/decl/constants.h"
#include "vmath/decl/mat4x4_f32.h"
#include <assert.h>

VMATH_INLINE_DECL vm_mat4x4f_t vm_load_mat4x4f(const vm_mat4x4fs_t* matrix)
{
#ifdef VMATH_SIMD_ENABLED
	return vm_loadb_v16f(matrix->rows[0]);
#else
	vm_mat4x4f_t out;
	out->_inner = vm_load_v16f(matrix->rows[0]);
	return out;
#endif
}

VMATH_INLINE_DECL vm_mat4x4f_t vm_loadb_mat4x4f(const vm_float32_t matrix[16])
{
#ifdef VMATH_SIMD_ENABLED
	return vm_loadb_v16f(matrix);
#else
	vm_mat4x4f_t out;
	out->_inner = vm_load_v16f(matrix);
	return out;
#endif
}

VMATH_INLINE_DECL void vm_store_mat4x4f(vm_mat4x4fs_t* output,
										vm_mat4x4f_t matrix)
{
#ifdef VMATH_SIMD_ENABLED
	vm_storeb_v16f(output->rows[0], matrix);
#else
	vm_storeb_v16f(output->rows[0], matrix->_inner);
#endif
}

VMATH_INLINE_DECL void vm_storeb_mat4x4f(vm_float32_t output[16],
										 vm_mat4x4f_t matrix)
{
#ifdef VMATH_SIMD_ENABLED
	vm_storeb_v16f(output, matrix);
#else
	vm_storeb_v16f(output, matrix->_inner);
#endif
}

VMATH_INLINE_DECL vm_mat4x4f_t vm_load_identity_mat4x4f(void)
{
#ifdef VMATH_SIMD_ENABLED
	return vm_mat4x4_iden.vector_rep;
#else
	return vm_mat4x4_iden.vector_rep->_inner;
#endif
}

VMATH_INLINE_DECL vm_mat4x4f_t vm_load_rotation_x_mat4x4f(vm_float32_t theta);

VMATH_INLINE_DECL vm_mat4x4f_t vm_load_rotation_y_mat4x4f(vm_float32_t theta);

VMATH_INLINE_DECL vm_mat4x4f_t vm_load_rotation_z_mat4x4f(vm_float32_t theta);

VMATH_INLINE_DECL vm_mat4x4f_t vm_load_rotation_pitch_yaw_roll_mat4x4f(
	vm_float32_t pitch, vm_float32_t yaw, vm_float32_t roll);
VMATH_INLINE_DECL vm_mat4x4f_t
vm_load_rotation_pitch_yaw_rollv_mat4x4f(vm_v3f_t angles);
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_translation_mat4x4f(vm_float32_t x,
														   vm_float32_t y,
														   vm_float32_t z);
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_translationv_mat4x4f(vm_v3f_t offset);
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_scale_mat4x4f(vm_float32_t x,
													 vm_float32_t y,
													 vm_float32_t z);
VMATH_INLINE_DECL vm_mat4x4f_t vm_load_scalev_mat4x4f(vm_v3f_t scale);
VMATH_INLINE_DECL vm_mat4x4f_t vm_mul_mat4x4f(vm_mat4x4f_t a, vm_mat4x4f_t b);
VMATH_INLINE_DECL vm_v3f_t vm_transform_mat4x4_v3f(vm_v3f_t vec,
												   vm_mat4x4f_t transform);

#endif
