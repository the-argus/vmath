#ifndef __VMATH_MAT4X4_F32_H
#define __VMATH_MAT4X4_F32_H

#include "vmath/decl/constants.h"
#include "vmath/decl/mat4x4_f32.h"
#include "vmath/decl/scalar.h"
#include "vmath/decl/vec4_f32.h"
#if !defined(VMATH_SIMD_ENABLED)
#include <string.h>
#endif

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
#if defined(VMATH_SSE41_ENABLE)
	vm_float32_t sin;
	vm_float32_t cos;
	vm_sin_cos(&sin, &cos, theta);

	vm_v4f_t v_sin = _mm_set_ss(sin);
	vm_v4f_t v_cos = _mm_set_ss(cos);

	// x = 0,y = cos,z = sin, w = 0
	v_cos = _mm_shuffle_ps(v_cos, v_sin, _MM_SHUFFLE(3, 0, 0, 3)); // NOLINT

	vm_mat4x4f_t matrix;

	// perform load of values into matrix differently depending on internal rep
	// TODO: is insert with m128s the best way to do this in avx2/avx512?
#if defined(VMATH_AVX512_GENERIC_ENABLE)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
	matrix = _mm512_insertf32x4(matrix, vm_mat4x4_iden_row0.vector_rep, 0);
#pragma clang diagnostic pop
	matrix = _mm512_insertf32x4(matrix, v_cos, 1);
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	matrix.buffer[0] = _mm256_insertf128_ps(matrix.buffer[0],
											vm_mat4x4_iden_row0.vector_rep, 0);
	matrix.buffer[0] = _mm256_insertf128_ps(matrix.buffer[0], v_cos, 1);
#else
	matrix.buffer[0] = vm_mat4x4_iden_row0.vector_rep;
	matrix.buffer[1] = v_cos;
#endif
	// x = 0,y = sin,z = cos, w = 0
	v_cos = _mm_shuffle_ps(v_cos, v_cos, _MM_SHUFFLE(3, 1, 2, 0)); // NOLINT
	// x = 0,y = -sin,z = cos, w = 0
	v_cos = _mm_mul_ps(v_cos, vm_negate_y.vector_rep);

#if defined(VMATH_AVX512_GENERIC_ENABLE)
	matrix = _mm512_insertf32x4(matrix, v_cos, 2);
	matrix = _mm512_insertf32x4(matrix, vm_mat4x4_iden_row3.vector_rep, 3);
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	matrix.buffer[1] = _mm256_insertf128_ps(matrix.buffer[1], v_cos, 0);
	matrix.buffer[1] = _mm256_insertf128_ps(matrix.buffer[1],
											vm_mat4x4_iden_row3.vector_rep, 1);
#else
	matrix.buffer[2] = v_cos;
	matrix.buffer[3] = vm_mat4x4_iden_row3.vector_rep;
#endif
	return matrix;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_float32_t sin;
	vm_float32_t cos;
	vm_sin_cos(&sin, &cos, theta);

	vm_mat4x4f_t matrix;
	// row 0 is identity
	memcpy(matrix._inner.buffer, vm_mat4x4_iden_row0.float_rep,
		   sizeof(vm_mat4x4_iden_row0.float_rep));
	// row 1
	matrix._inner.buffer[4] = 0;
	matrix._inner.buffer[5] = cos;
	matrix._inner.buffer[6] = sin;
	matrix._inner.buffer[7] = 0;
	// row 2
	matrix._inner.buffer[8] = 0;
	matrix._inner.buffer[9] = -sin;
	matrix._inner.buffer[10] = cos;
	matrix._inner.buffer[11] = 0;
	// row 3 is identity
	memcpy(matrix._inner.buffer + 12, vm_mat4x4_iden_row3.float_rep,
		   sizeof(vm_mat4x4_iden_row3.float_rep));
	return matrix;
#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_rotation_y_mat4x4f(vm_float32_t theta)
{
#if defined(VMATH_SSE41_ENABLE)
	vm_float32_t sin;
	vm_float32_t cos;
	vm_sin_cos(&sin, &cos, theta);

	vm_v4f_t v_sin = _mm_set_ss(sin);
	vm_v4f_t v_cos = _mm_set_ss(cos);

	// x = sin,y = 0,z = cos, w = 0
	v_sin = _mm_shuffle_ps(v_sin, v_cos, _MM_SHUFFLE(3, 0, 3, 0)); // NOLINT
	vm_mat4x4f_t matrix;

#if defined(VMATH_AVX512_GENERIC_ENABLE)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
	matrix = _mm512_insertf32x4(matrix, vm_mat4x4_iden_row1.vector_rep, 1);
#pragma clang diagnostic pop
	matrix = _mm512_insertf32x4(matrix, v_sin, 2);
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	matrix.buffer[0] = _mm256_insertf128_ps(matrix.buffer[0],
											vm_mat4x4_iden_row1.vector_rep, 1);
	matrix.buffer[1] = _mm256_insertf128_ps(matrix.buffer[1], v_sin, 0);
#else
	matrix.buffer[1] = vm_mat4x4_iden_row1.vector_rep;
	matrix.buffer[2] = v_sin;
#endif

	// x = cos,y = 0,z = sin, w = 0
	v_sin = _mm_shuffle_ps(v_sin, v_sin, _MM_SHUFFLE(3, 0, 1, 2)); // NOLINT
	// x = cos,y = 0,z = -sin, w = 0
	v_sin = _mm_mul_ps(v_sin, vm_negate_z.vector_rep);

#if defined(VMATH_AVX512_GENERIC_ENABLE)
	matrix = _mm512_insertf32x4(matrix, v_sin, 0);
	matrix = _mm512_insertf32x4(matrix, vm_mat4x4_iden_row3.vector_rep, 3);
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	matrix.buffer[0] = _mm256_insertf128_ps(matrix.buffer[0], v_sin, 0);
	matrix.buffer[1] = _mm256_insertf128_ps(matrix.buffer[1],
											vm_mat4x4_iden_row3.vector_rep, 1);
#else
	matrix.buffer[0] = v_sin;
	matrix.buffer[3] = vm_mat4x4_iden_row3.vector_rep;
#endif
	return matrix;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_float32_t sin;
	vm_float32_t cos;
	vm_sin_cos(&sin, &cos, theta);

	vm_mat4x4f_t matrix;
	// row 0
	matrix._inner.buffer[0] = cos;
	matrix._inner.buffer[1] = 0.F;
	matrix._inner.buffer[2] = -sin;
	matrix._inner.buffer[3] = 0.F;
	// row 1 is identity
	memcpy(matrix._inner.buffer, vm_mat4x4_iden_row1.float_rep,
		   sizeof(vm_mat4x4_iden_row1.float_rep));
	// row 2
	matrix._inner.buffer[8] = sin;
	matrix._inner.buffer[9] = 0.F;
	matrix._inner.buffer[10] = cos;
	matrix._inner.buffer[11] = 0.F;
	// row 3 is identity
	memcpy(matrix._inner.buffer + 12, vm_mat4x4_iden_row3.float_rep,
		   sizeof(vm_mat4x4_iden_row3.float_rep));
	return matrix;
#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_rotation_z_mat4x4f(vm_float32_t theta)
{
#if defined(VMATH_SSE41_ENABLE)
	vm_float32_t sin;
	vm_float32_t cos;
	vm_sin_cos(&sin, &cos, theta);

	vm_v4f_t v_sin = _mm_set_ss(sin);
	vm_v4f_t v_cos = _mm_set_ss(cos);

	// x = cos,y = sin,z = 0, w = 0
	v_cos = _mm_unpacklo_ps(v_cos, v_sin);

	vm_mat4x4f_t matrix;

	// perform load of values into matrix differently depending on internal rep
	// TODO: is insert with m128s the best way to do this in avx2/avx512?
#if defined(VMATH_AVX512_GENERIC_ENABLE)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
	matrix = _mm512_insertf32x4(matrix, v_cos, 0);
#pragma clang diagnostic pop
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	matrix.buffer[0] = _mm256_insertf128_ps(matrix.buffer[0], v_cos, 0);
#else
	matrix.buffer[0] = v_cos;
#endif

	// x = sin,y = cos,z = 0, w = 0
	v_cos = _mm_shuffle_ps(v_cos, v_cos, _MM_SHUFFLE(3, 2, 0, 1)); // NOLINT
	// x = cos,y = -sin,z = 0, w = 0
	v_cos = _mm_mul_ps(v_cos, vm_negate_x.vector_rep);

#if defined(VMATH_AVX512_GENERIC_ENABLE)
	matrix = _mm512_insertf32x4(matrix, v_cos, 1);
	matrix =
		_mm512_insertf32x8(matrix, vm_mat4x4_iden_rows_2_and_3.vector_rep, 1);
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	matrix.buffer[0] = _mm256_insertf128_ps(matrix.buffer[0], v_cos, 1);
	matrix.buffer[1] = vm_mat4x4_iden_rows_2_and_3.vector_rep;
#else
	matrix.buffer[1] = v_cos;
	matrix.buffer[2] = vm_mat4x4_iden_row2.vector_rep;
	matrix.buffer[3] = vm_mat4x4_iden_row3.vector_rep;
#endif
	return matrix;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_float32_t sin;
	vm_float32_t cos;
	vm_sin_cos(&sin, &cos, theta);

	vm_mat4x4f_t matrix;
	// row 0
	matrix._inner.buffer[0] = cos;
	matrix._inner.buffer[1] = sin;
	matrix._inner.buffer[2] = 0.F;
	matrix._inner.buffer[3] = 0.F;
	// row 1
	matrix._inner.buffer[4] = -sin;
	matrix._inner.buffer[5] = cos;
	matrix._inner.buffer[6] = 0.F;
	matrix._inner.buffer[7] = 0.F;
	// row 2 + 3 are identity
	memcpy(matrix._inner.buffer + 8, vm_mat4x4_iden_rows_2_and_3.float_rep,
		   sizeof(vm_mat4x4_iden_rows_2_and_3.float_rep));
	return matrix;
#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_rotation_pitch_yaw_roll_mat4x4f(
	vm_float32_t pitch, vm_float32_t yaw, vm_float32_t roll)
{
	const vm_v3fs_t pitch_yaw_roll = {pitch, yaw, roll};
	return vm_load_rotation_pitch_yaw_rollv_mat4x4f(
		vm_load_v3f(&pitch_yaw_roll));
}

VMATH_INLINE vm_mat4x4f_t
vm_load_rotation_pitch_yaw_rollv_mat4x4f(vm_v3f_t angles)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

#elif defined(VMATH_SSE41_ENABLE)
    vm_v3f_t sin_angles; 
    vm_v3f_t cos_angles; 
    vm_sin_cos_v3f(&sin_angles, &cos_angles, angles);

    // XMVECTOR P0 = XMVectorPermute<XM_PERMUTE_1X, XM_PERMUTE_0Z, XM_PERMUTE_1Z, XM_PERMUTE_1X>(SinAngles, CosAngles);
    // XMVECTOR Y0 = XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_1X, XM_PERMUTE_1X, XM_PERMUTE_1Y>(SinAngles, CosAngles);
    // XMVECTOR P1 = XMVectorPermute<XM_PERMUTE_1Z, XM_PERMUTE_0Z, XM_PERMUTE_1Z, XM_PERMUTE_0Z>(SinAngles, CosAngles);
    // XMVECTOR Y1 = XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_1Y, XM_PERMUTE_0Y, XM_PERMUTE_0Y>(SinAngles, CosAngles);
    // XMVECTOR P2 = XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_1Z, XM_PERMUTE_0Z, XM_PERMUTE_1Z>(SinAngles, CosAngles);
    // XMVECTOR P3 = XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0Y, XM_PERMUTE_1Y, XM_PERMUTE_1Y>(SinAngles, CosAngles);
    // XMVECTOR Y2 = XMVectorSplatX(SinAngles);
    // XMVECTOR NS = XMVectorNegate(SinAngles);

    // XMVECTOR Q0 = XMVectorMultiply(P0, Y0);
    // XMVECTOR Q1 = XMVectorMultiply(P1, Sign.v);
    // Q1 = XMVectorMultiply(Q1, Y1);
    // XMVECTOR Q2 = XMVectorMultiply(P2, Y2);
    // Q2 = XMVectorMultiplyAdd(Q2, P3, Q1);

    // XMVECTOR V0 = XMVectorPermute<XM_PERMUTE_1X, XM_PERMUTE_0Y, XM_PERMUTE_1Z, XM_PERMUTE_0W>(Q0, Q2);
    // XMVECTOR V1 = XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_0Z, XM_PERMUTE_1W, XM_PERMUTE_0W>(Q0, Q2);
    // XMVECTOR V2 = XMVectorPermute<XM_PERMUTE_0X, XM_PERMUTE_1X, XM_PERMUTE_0W, XM_PERMUTE_0W>(Q0, NS);

    // XMMATRIX M;
    // M.r[0] = XMVectorSelect(g_XMZero, V0, g_XMSelect1110.v);
    // M.r[1] = XMVectorSelect(g_XMZero, V1, g_XMSelect1110.v);
    // M.r[2] = XMVectorSelect(g_XMZero, V2, g_XMSelect1110.v);
    // M.r[3] = g_XMIdentityR3;
    // return M;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3fs_t angles_readable;
	vm_store_v3f(&angles_readable, angles);

	vm_float32_t cos_pitch;
	vm_float32_t sin_pitch;
	vm_sin_cos(&sin_pitch, &cos_pitch, angles_readable.x);

	vm_float32_t cos_yaw;
	vm_float32_t sin_yaw;
	vm_sin_cos(&sin_yaw, &cos_yaw, angles_readable.y);

	vm_float32_t cos_roll;
	vm_float32_t sin_roll;
	vm_sin_cos(&sin_roll, &cos_roll, angles_readable.z);

	vm_mat4x4f_t matrix;
	matrix._inner.buffer[0] =
		cos_roll * cos_yaw + sin_roll * sin_pitch * sin_yaw;
	matrix._inner.buffer[1] = sin_roll * cos_pitch;
	matrix._inner.buffer[2] =
		sin_roll * sin_pitch * cos_yaw - cos_roll * sin_yaw;
	matrix._inner.buffer[3] = 0.F;

	matrix._inner.buffer[4] =
		cos_roll * sin_pitch * sin_yaw - sin_roll * cos_yaw;
	matrix._inner.buffer[5] = cos_roll * cos_pitch;
	matrix._inner.buffer[6] =
		sin_roll * sin_yaw + cos_roll * sin_pitch * cos_yaw;
	matrix._inner.buffer[7] = 0.F;

	matrix._inner.buffer[8] = cos_pitch * sin_yaw;
	matrix._inner.buffer[9] = -sin_pitch;
	matrix._inner.buffer[10] = cos_pitch * cos_yaw;
	matrix._inner.buffer[11] = 0.F;

	matrix._inner.buffer[12] = 0.F;
	matrix._inner.buffer[13] = 0.F;
	matrix._inner.buffer[14] = 0.F;
	matrix._inner.buffer[15] = 1.F;
	return matrix;
#endif
}

VMATH_INLINE vm_mat4x4f_t vm_load_translation_mat4x4f(vm_float32_t x,
													  vm_float32_t y,
													  vm_float32_t z)
{
	const vm_v3fs_t offset = {x, y, z};
	return vm_load_translationv_mat4x4f(vm_load_v3f(&offset));
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
	const vm_v3fs_t scale = {x, y, z};
	return vm_load_scalev_mat4x4f(vm_load_v3f(&scale));
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
