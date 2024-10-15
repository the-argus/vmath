#ifndef __VMATH_MAT4X4_F32_H
#define __VMATH_MAT4X4_F32_H

#include "vmath/decl/constants.h"
#include "vmath/decl/mat4x4_f32.h"
#include "vmath/decl/scalar.h"
#include "vmath/decl/vec4_f32.h"

VMATH_INLINE vm_mat4x4f_t vm_load_mat4x4f(const vm_mat4x4fs_t* matrix)
{
#ifdef VMATH_SIMD_ENABLED
	return vm_loadb_v16f(matrix->rows[0]);
#else
	vm_mat4x4f_t out;
	out._inner = vm_loadb_v16f(matrix->rows[0]);
	return out;
#endif
}

VMATH_INLINE vm_mat4x4f_t vm_loadb_mat4x4f(const vm_float32_t matrix[16])
{
#ifdef VMATH_SIMD_ENABLED
	return vm_loadb_v16f(matrix);
#else
	vm_mat4x4f_t out;
	out._inner = vm_loadb_v16f(matrix);
	return out;
#endif
}

VMATH_INLINE void vm_store_mat4x4f(vm_mat4x4fs_t* output, vm_mat4x4f_t matrix)
{
#ifdef VMATH_SIMD_ENABLED
	vm_storeb_v16f(output->rows[0], matrix);
#else
	vm_storeb_v16f(output->rows[0], matrix._inner);
#endif
}

VMATH_INLINE void vm_storeb_mat4x4f(vm_float32_t output[16],
									vm_mat4x4f_t matrix)
{
#ifdef VMATH_SIMD_ENABLED
	vm_storeb_v16f(output, matrix);
#else
	vm_storeb_v16f(output, matrix._inner);
#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_identity_mat4x4f(void)
{
#ifdef VMATH_SIMD_ENABLED
	return vm_mat4x4_iden.vector_rep;
#else
	vm_mat4x4f_t mat;
	mat._inner = vm_mat4x4_iden.vector_rep;
	return mat;
#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_rotation_x_mat4x4f(vm_float32_t theta)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)
	vm_float32_t sin;
	vm_float32_t cos;
	vm_sin_cos(&sin, &cos, theta);

	vm_v4f_t v_sin = _mm_set_ss(sin);
	vm_v4f_t v_cos = _mm_set_ss(cos);

	// x = 0,y = cos,z = sin, w = 0
	v_cos = _mm_shuffle_ps(v_cos, v_sin, _MM_SHUFFLE(3, 0, 0, 3)); // NOLINT

	vm_mat4x4f_t matrix;

	matrix.buffer[0] = vm_mat4x4_iden_row0.vector_rep;
	matrix.buffer[1] = v_cos;
	// x = 0,y = sin,z = cos, w = 0
	v_cos = _mm_shuffle_ps(v_cos, v_cos, _MM_SHUFFLE(3, 1, 2, 0)); // NOLINT
	// x = 0,y = -sin,z = cos, w = 0
	v_cos = _mm_mul_ps(v_cos, vm_negate_y.vector_rep);
	matrix.buffer[2] = v_cos;
	matrix.buffer[3] = vm_mat4x4_iden_row3.vector_rep;
	return matrix;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_rotation_y_mat4x4f(vm_float32_t theta)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_rotation_z_mat4x4f(vm_float32_t theta)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_rotation_pitch_yaw_roll_mat4x4f(
	vm_float32_t pitch, vm_float32_t yaw, vm_float32_t roll)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}
VMATH_INLINE vm_mat4x4f_t
vm_load_rotation_pitch_yaw_rollv_mat4x4f(vm_v3f_t angles)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_translation_mat4x4f(vm_float32_t x,
													  vm_float32_t y,
													  vm_float32_t z)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_translationv_mat4x4f(vm_v3f_t offset)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_scale_mat4x4f(vm_float32_t x, vm_float32_t y,
												vm_float32_t z)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_scalev_mat4x4f(vm_v3f_t scale)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_mat4x4f_t vm_mul_mat4x4f(vm_mat4x4f_t a, vm_mat4x4f_t b)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

VMATH_INLINE vm_v3f_t vm_transform_mat4x4_v3f(vm_v3f_t vec,
											  vm_mat4x4f_t transform)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

#endif
}

#endif
