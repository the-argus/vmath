#ifndef __VMATH_MAT4X4_F32_H
#define __VMATH_MAT4X4_F32_H

#include "vmath/decl/constants.h"
#include "vmath/decl/mat4x4_f32.h"
#include "vmath/decl/scalar.h"
#include "vmath/decl/vec4_f32.h"
#if defined(VMATH_SSE41_ENABLE)
#include "vmath/internal/full_shuffle.h"
#endif
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
#if defined(VMATH_SSE41_ENABLE)
	vm_v3f_t sin_angles;
	vm_v3f_t cos_angles;
	vm_sin_cos_v3f(&sin_angles, &cos_angles, angles);

	// TODO: optimize these full shuffles, some cases can dont need full shuffle
	// and select
	__m128 p0;
	// select: { cos.x, sin.z, cos.z, cos.x }
	// XMVECTOR P0 = XMVectorPermute<XM_PERMUTE_1X, XM_PERMUTE_0Z,
	// XM_PERMUTE_1Z, XM_PERMUTE_1X>(SinAngles, CosAngles); NOLINTNEXTLINE
	VMATH_SSE_FULL_SHUFFLE(p0, sin_angles, cos_angles, _MM_SHUFFLE(0, 2, 2, 0),
						   vm_v4_selectmask_1011)

	__m128 y0;
	// select: { sin.y, cos.x, cos.x, cos.y }
	// XMVECTOR Y0 = XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_1X,
	// XM_PERMUTE_1X, XM_PERMUTE_1Y>(SinAngles, CosAngles); NOLINTNEXTLINE
	VMATH_SSE_FULL_SHUFFLE(y0, sin_angles, cos_angles, _MM_SHUFFLE(1, 0, 0, 1),
						   vm_v4_selectmask_0111)

	__m128 p1;
	// select: { cos.z, sin.z, cos.z, sin.z }
	// XMVECTOR P1 = XMVectorPermute<XM_PERMUTE_1Z, XM_PERMUTE_0Z,
	// XM_PERMUTE_1Z, XM_PERMUTE_0Z>(SinAngles, CosAngles); NOLINTNEXTLINE
	VMATH_SSE_FULL_SHUFFLE(p1, sin_angles, cos_angles, _MM_SHUFFLE(2, 2, 2, 2),
						   vm_v4_selectmask_1010)

	__m128 y1;
	// select: { cos.y, cos.y, sin.y, sin.y }
	// XMVECTOR Y1 = XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_1Y,
	// XM_PERMUTE_0Y, XM_PERMUTE_0Y>(SinAngles, CosAngles); NOLINTNEXTLINE
	VMATH_SSE_FULL_SHUFFLE(y1, sin_angles, cos_angles, _MM_SHUFFLE(1, 1, 1, 1),
						   vm_v4_selectmask_1100)

	__m128 p2;
	// select: { sin.z, cos.z, sin.z, cos.z }
	// XMVECTOR P2 = XMVectorPermute<XM_PERMUTE_0Z, XM_PERMUTE_1Z,
	// XM_PERMUTE_0Z, XM_PERMUTE_1Z>(SinAngles, CosAngles); NOLINTNEXTLINE
	VMATH_SSE_FULL_SHUFFLE(p2, sin_angles, cos_angles, _MM_SHUFFLE(2, 2, 2, 2),
						   vm_v4_selectmask_0101)

	__m128 p3;
	// select: { sin.y, sin.y, cos.y, cos.y }
	// XMVECTOR P3 = XMVectorPermute<XM_PERMUTE_0Y, XM_PERMUTE_0Y,
	// XM_PERMUTE_1Y, XM_PERMUTE_1Y>(SinAngles, CosAngles); NOLINTNEXTLINE
	VMATH_SSE_FULL_SHUFFLE(p3, sin_angles, cos_angles, _MM_SHUFFLE(1, 1, 1, 1),
						   vm_v4_selectmask_0011)

	// select { sin.x, sin.x, sin.x, sin.x }
	const __m128 y2 =
		// NOLINTNEXTLINE
		_mm_shuffle_ps(sin_angles, sin_angles, _MM_SHUFFLE(0, 0, 0, 0));
	const __m128 ns = _mm_mul_ps(sin_angles, vm_v4_negative_one.vector_rep);

	__m128 q0 = _mm_mul_ps(p0, y0);
	__m128 q1 = _mm_mul_ps(p1, vm_v4_pitchyawroll_signs.vector_rep);
	q1 = _mm_mul_ps(q1, y1);
	__m128 q2 = _mm_mul_ps(p2, y2);
	q2 = VMATH_FMADD_PS(q2, p3, q1);

	// XMVECTOR V0 = XMVectorPermute<XM_PERMUTE_1X, XM_PERMUTE_0Y,
	// XM_PERMUTE_1Z, XM_PERMUTE_0W>(Q0, Q2);
	const __m128 v0 = vm_select_v4f(q0, q2, vm_v4_selectmask_1010.vector_rep);
	__m128 v1;
	__m128 v2;
	// XMVECTOR V1 = XMVectorPermute<XM_PERMUTE_1Y, XM_PERMUTE_0Z,
	// XM_PERMUTE_1W, XM_PERMUTE_0W>(Q0, Q2); NOLINTNEXTLINE
	VMATH_SSE_FULL_SHUFFLE(v1, q0, q2, _MM_SHUFFLE(1, 2, 3, 3),
						   vm_v4_selectmask_1010)
	// XMVECTOR V2 = XMVectorPermute<XM_PERMUTE_0X, XM_PERMUTE_1X,
	// XM_PERMUTE_0W, XM_PERMUTE_0W>(Q0, NS); NOLINTNEXTLINE
	VMATH_SSE_FULL_SHUFFLE(v2, q0, ns, _MM_SHUFFLE(0, 0, 3, 3),
						   vm_v4_selectmask_0100)

	vm_mat4x4f_t matrix;

#if defined(VMATH_AVX512_GENERIC_ENABLE)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
	matrix = _mm512_insertf32x4(matrix,
								vm_select_v4f(vm_v4_zero.vector_rep, v0,
											  vm_v4_selectmask_1110.vector_rep),
								0);
#pragma clang diagnostic pop
	matrix = _mm512_insertf32x4(matrix,
								vm_select_v4f(vm_v4_zero.vector_rep, v1,
											  vm_v4_selectmask_1110.vector_rep),
								1);
	matrix = _mm512_insertf32x4(matrix,
								vm_select_v4f(vm_v4_zero.vector_rep, v2,
											  vm_v4_selectmask_1110.vector_rep),
								2);
	matrix = _mm512_insertf32x4(matrix, vm_mat4x4_iden_row3.vector_rep, 3);
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	matrix.buffer[0] =
		_mm256_insertf128_ps(matrix.buffer[0],
							 vm_select_v4f(vm_v4_zero.vector_rep, v0,
										   vm_v4_selectmask_1110.vector_rep),
							 0);
	matrix.buffer[0] =
		_mm256_insertf128_ps(matrix.buffer[0],
							 vm_select_v4f(vm_v4_zero.vector_rep, v1,
										   vm_v4_selectmask_1110.vector_rep),
							 1);
	matrix.buffer[1] =
		_mm256_insertf128_ps(matrix.buffer[1],
							 vm_select_v4f(vm_v4_zero.vector_rep, v2,
										   vm_v4_selectmask_1110.vector_rep),
							 0);
	matrix.buffer[1] = _mm256_insertf128_ps(matrix.buffer[1],
											vm_mat4x4_iden_row3.vector_rep, 1);
#else
	matrix.buffer[0] = vm_select_v4f(vm_v4_zero.vector_rep, v0,
									 vm_v4_selectmask_1110.vector_rep);
	matrix.buffer[1] = vm_select_v4f(vm_v4_zero.vector_rep, v1,
									 vm_v4_selectmask_1110.vector_rep);
	matrix.buffer[2] = vm_select_v4f(vm_v4_zero.vector_rep, v2,
									 vm_v4_selectmask_1110.vector_rep);
	matrix.buffer[3] = vm_mat4x4_iden_row3.vector_rep;
#endif

	return matrix;

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

	vm_mat4x4f_t matrix = vm_mat4x4_iden.vector_rep;
	const __m128 r3 = vm_select_v4f(vm_mat4x4_iden_row3.vector_rep, offset,
									vm_v4_selectmask_1110.vector_rep);
	_mm512_insertf32x4(matrix, r3, 3);
	return matrix;

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

	vm_mat4x4f_t matrix;
	matrix.buffer[0] = vm_mat4x4_iden_rows_0_and_1.vector_rep;
	const __m128 r3 = vm_select_v4f(vm_mat4x4_iden_row3.vector_rep, offset,
									vm_v4_selectmask_1110.vector_rep);
	matrix.buffer[1] = _mm256_insertf128_ps(matrix.buffer[1], r3, 1);
	return matrix;

#elif defined(VMATH_SSE41_ENABLE)

	vm_mat4x4f_t matrix;
	matrix.buffer[0] = vm_mat4x4_iden_row0.vector_rep;
	matrix.buffer[1] = vm_mat4x4_iden_row1.vector_rep;
	matrix.buffer[2] = vm_mat4x4_iden_row2.vector_rep;
	matrix.buffer[3] = vm_select_v4f(vm_mat4x4_iden_row3.vector_rep, offset,
									 vm_v4_selectmask_1110.vector_rep);
	return matrix;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	vm_mat4x4f_t matrix;
	matrix._inner = vm_loadb_v16f(vm_mat4x4_iden.float_rep);
	matrix._inner.buffer[12] = offset._inner.x;
	matrix._inner.buffer[13] = offset._inner.y;
	matrix._inner.buffer[14] = offset._inner.z;
	return matrix;

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
	vm_mat4x4f_t matrix;
	const __m128 r0 = _mm_and_ps(scale, vm_v4_selectmask_1000.vector_rep);
	const __m128 r1 = _mm_and_ps(scale, vm_v4_selectmask_0100.vector_rep);
	const __m128 r2 = _mm_and_ps(scale, vm_v4_selectmask_0010.vector_rep);
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
	matrix = _mm512_insertf32x4(matrix, r0, 0);
#pragma clang diagnostic pop
	matrix = _mm512_insertf32x4(matrix, r1, 1);
	matrix = _mm512_insertf32x4(matrix, r2, 2);
	matrix = _mm512_insertf32x4(matrix, vm_mat4x4_iden_row3.vector_rep, 3);
	return matrix;

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

	vm_mat4x4f_t matrix;
	const __m128 r0 = _mm_and_ps(scale, vm_v4_selectmask_1000.vector_rep);
	const __m128 r1 = _mm_and_ps(scale, vm_v4_selectmask_0100.vector_rep);
	const __m128 r2 = _mm_and_ps(scale, vm_v4_selectmask_0010.vector_rep);
	matrix.buffer[0] = _mm256_insertf128_ps(matrix.buffer[0], r0, 0);
	matrix.buffer[0] = _mm256_insertf128_ps(matrix.buffer[0], r1, 1);
	matrix.buffer[1] = _mm256_insertf128_ps(matrix.buffer[1], r2, 0);
	matrix.buffer[1] = _mm256_insertf128_ps(matrix.buffer[1],
											vm_mat4x4_iden_row3.vector_rep, 0);
	return matrix;

#elif defined(VMATH_SSE41_ENABLE)

	vm_mat4x4f_t matrix;
	matrix.buffer[0] = _mm_and_ps(scale, vm_v4_selectmask_1000.vector_rep);
	matrix.buffer[1] = _mm_and_ps(scale, vm_v4_selectmask_0100.vector_rep);
	matrix.buffer[2] = _mm_and_ps(scale, vm_v4_selectmask_0010.vector_rep);
	matrix.buffer[3] = vm_mat4x4_iden_row3.vector_rep;
	return matrix;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	vm_mat4x4f_t matrix;
	matrix._inner.buffer[0] = scale._inner.x;
	matrix._inner.buffer[1] = 0.0F;
	matrix._inner.buffer[2] = 0.0F;
	matrix._inner.buffer[3] = 0.0F;

	matrix._inner.buffer[4] = 0.0F;
	matrix._inner.buffer[5] = scale._inner.y;
	matrix._inner.buffer[6] = 0.0F;
	matrix._inner.buffer[7] = 0.0F;

	matrix._inner.buffer[8] = 0.0F;
	matrix._inner.buffer[9] = 0.0F;
	matrix._inner.buffer[10] = scale._inner.z;
	matrix._inner.buffer[11] = 0.0F;

	matrix._inner.buffer[12] = 0.0F;
	matrix._inner.buffer[13] = 0.0F;
	matrix._inner.buffer[14] = 0.0F;
	matrix._inner.buffer[15] = 1.0F;
	return matrix;

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
