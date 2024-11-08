/*
 * Implementation file for vec3 operations. See vmath/decl/vec3_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC3_F32_H
#define __VMATH_VEC3_F32_H

#include "vmath/decl/vec3_f32.h"
#if !defined(VMATH_SIMD_ENABLED)
#include "vmath/scalar.h"
#endif
#include "vmath/vec4_f32.h"
#include <assert.h>

VMATH_INLINE vm_v3f_t vm_load_v3f(const vm_v3fs_t* vec)
{
	assert(vec);
#if defined(VMATH_SSE41_ENABLE)
	__m128 xy = _mm_castpd_ps(_mm_load_sd((const double*)vec));
	__m128 z = _mm_load_ss(&vec->z);
	return _mm_insert_ps(xy, z, 0x20);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3f_t output;
	output._inner.x = vec->x;
	output._inner.y = vec->y;
	output._inner.z = vec->z;
	return output;
#endif
}

VMATH_INLINE vm_v3f_t vm_loadb_v3f(const vm_float32_t vec[3])
{
	assert(vec);
	assert(sizeof(vm_float32_t[3]) == sizeof(vm_v3fs_t));
	return vm_load_v3f((const vm_v3fs_t*)vec);
}

VMATH_INLINE void vm_store_v3f(vm_v3fs_t* output, vm_v3f_t vector)
{
	assert(output);
#if defined(VMATH_SSE41_ENABLE)
	*(int*)&output->x = _mm_extract_ps(vector, 0);
	*(int*)&output->y = _mm_extract_ps(vector, 1);
	*(int*)&output->z = _mm_extract_ps(vector, 2);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	output->x = vector._inner.x;
	output->y = vector._inner.y;
	output->z = vector._inner.z;
#endif
}

VMATH_INLINE void vm_storeb_v3f(vm_float32_t output[3], vm_v3f_t vector)
{
	assert(output);
	assert(sizeof(vm_float32_t[3]) == sizeof(vm_v3fs_t));
	vm_store_v3f((vm_v3fs_t*)output, vector);
}

VMATH_INLINE vm_v3f_t vm_splat_v3f(vm_float32_t fill)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_set_ps(0, fill, fill, fill);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3f_t output;
	output._inner.x = fill;
	output._inner.y = fill;
	output._inner.z = fill;
	return output;
#endif
}

VMATH_INLINE vm_v3f_t vm_shave4_v3f(vm_v4f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return vec;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3f_t output;
	output._inner.x = vec._inner.x;
	output._inner.y = vec._inner.y;
	output._inner.z = vec._inner.z;
	return output;
#endif
}

VMATH_INLINE vm_v3f_t vm_nearest_int_round_v3f(vm_v3f_t vec)
{
#if defined(VMATH_SIMD_ENABLED)
	return vm_nearest_int_round_v4f(vec);
#else
	vm_v3f_t out;
	out._inner.x = vm_nearest_int_round(vec._inner.x);
	out._inner.y = vm_nearest_int_round(vec._inner.y);
	out._inner.z = vm_nearest_int_round(vec._inner.z);
	return out;
#endif
}

VMATH_INLINE vm_v3f_t vm_negative_multiply_subtract_v3f(vm_v3f_t mul1,
														vm_v3f_t mul2,
														vm_v3f_t base)
{
#if defined(VMATH_SIMD_ENABLED)
	return vm_negative_multiply_subtract_v4f(mul1, mul2, base);
#else
	vm_v3f_t out;
	out._inner.x = base._inner.x - (mul1._inner.x * mul2._inner.x);
	out._inner.y = base._inner.y - (mul1._inner.y * mul2._inner.y);
	out._inner.z = base._inner.z - (mul1._inner.z * mul2._inner.z);
	return out;
#endif
}

VMATH_INLINE_DECL vm_v3f_t vm_mod_pi_v3f(const vm_v3f_t angles)
{
#if defined(VMATH_SSE41_ENABLE)
	vm_v4f_t mod = _mm_mul_ps(angles, vm_v4_2pi_inverse.vector_rep);
	mod = vm_nearest_int_round_v4f(mod);
	return VMATH_FNMADD_PS(mod, vm_v4_2pi.vector_rep, angles);
	return mod;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	const vm_v3f_t one_over_2pi = vm_loadb_v3f(vm_v4_2pi_inverse.float_rep);
	const vm_v3f_t angles_divpi = vm_mul_v3f(angles, one_over_2pi);
	const vm_v3f_t angles_introunded = vm_nearest_int_round_v3f(angles_divpi);
	const vm_v3f_t twopi = vm_loadb_v3f(vm_v4_2pi.float_rep);
	// return angles - (twopi * angles_introunded)
	return vm_negative_multiply_subtract_v3f(twopi, angles_introunded, angles);
#endif
}

VMATH_INLINE void vm_sin_cos_v3f(vm_v3f_t* out_sin, vm_v3f_t* out_cos,
								 vm_v3f_t unclamped_angles)
{
	assert(out_sin != NULL);
	assert(out_cos != NULL);

#if defined(VMATH_SSE41_ENABLE)
	const __m128 angles = vm_mod_pi_v3f(unclamped_angles);
	// Map in [-pi/2,pi/2] with sin(y) = sin(x), cos(y) = sign*cos(x).
	const __m128 sign = _mm_and_ps(angles, vm_v4_negative_zero.vector_rep);
	// pi when angles[i] >= 0, -pi when angles[i] < 0
	const __m128 pi_or_negpi = _mm_or_ps(vm_v4_pi.vector_rep, sign);
	// |angles|
	const __m128 abs_angles = _mm_andnot_ps(sign, angles);
	const __m128 piwrapped = _mm_sub_ps(pi_or_negpi, angles);
	// element[i] = if (|angles[i]| <= pi/2) then 0xFFFFFFFF else 0x00000000
	const __m128 angles_lessthan_halfpi_mask =
		_mm_cmple_ps(abs_angles, vm_v4_pidiv2.vector_rep);
	const __m128 angles_iflessthan_halfpi =
		_mm_and_ps(angles_lessthan_halfpi_mask, angles);
	const __m128 piwrapped_ifgreaterthan_halfpi =
		_mm_andnot_ps(angles_lessthan_halfpi_mask, piwrapped);
	// element[i] = if (|angles[i]| <= pi/2) then angles[i] else piwrapped[i];
	const __m128 merged_selected =
		_mm_or_ps(angles_iflessthan_halfpi, piwrapped_ifgreaterthan_halfpi);

	// element[i] = if (|angles[i]| < pi/2) then 1 else -1
	const __m128 sign_lessthan_halfpi =
		_mm_or_ps(_mm_and_ps(angles_lessthan_halfpi_mask, vm_v4_one.vector_rep),
				  _mm_andnot_ps(angles_lessthan_halfpi_mask,
								vm_v4_negative_one.vector_rep));

	const __m128 selected_angles_squared =
		_mm_mul_ps(merged_selected, merged_selected);

	// sin
	{
		const __m128 sin_coeff_0 = vm_v4_sincoeff_0.vector_rep;
		const __m128 sin_coeff_1 = vm_v4_sincoeff_1.vector_rep;
		const __m128 sin_constants03 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(sin_coeff_0, sin_coeff_0, _MM_SHUFFLE(3, 3, 3, 3));
		const __m128 sin_constants10 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(sin_coeff_1, sin_coeff_1, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 result = VMATH_FMADD_PS(sin_constants10, selected_angles_squared,
									   sin_constants03);

		const __m128 sin_constants02 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(sin_coeff_0, sin_coeff_0, _MM_SHUFFLE(2, 2, 2, 2));
		result =
			VMATH_FMADD_PS(result, selected_angles_squared, sin_constants02);

		const __m128 sin_constants01 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(sin_coeff_0, sin_coeff_0, _MM_SHUFFLE(1, 1, 1, 1));
		result =
			VMATH_FMADD_PS(result, selected_angles_squared, sin_constants01);

		const __m128 sin_constants00 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(sin_coeff_0, sin_coeff_0, _MM_SHUFFLE(0, 0, 0, 0));
		result =
			VMATH_FMADD_PS(result, selected_angles_squared, sin_constants00);

		result = VMATH_FMADD_PS(result, selected_angles_squared,
								vm_v4_one.vector_rep);
		result = _mm_mul_ps(result, merged_selected);
		*out_sin = result;
	}

	// cos
	{
		const __m128 cos_coeff_1 = vm_v4_coscoeff_1.vector_rep;
		const __m128 cos_constants10 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(cos_coeff_1, cos_coeff_1, _MM_SHUFFLE(0, 0, 0, 0));
		const __m128 cos_coeff_0 = vm_v4_coscoeff_0.vector_rep;
		const __m128 cos_constants03 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(cos_coeff_0, cos_coeff_0, _MM_SHUFFLE(3, 3, 3, 3));
		__m128 result = VMATH_FMADD_PS(cos_constants10, selected_angles_squared,
									   cos_constants03);

		const __m128 cos_constants02 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(cos_coeff_0, cos_coeff_0, _MM_SHUFFLE(2, 2, 2, 2));
		result =
			VMATH_FMADD_PS(result, selected_angles_squared, cos_constants02);

		const __m128 cos_constants01 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(cos_coeff_0, cos_coeff_0, _MM_SHUFFLE(1, 1, 1, 1));
		result =
			VMATH_FMADD_PS(result, selected_angles_squared, cos_constants01);

		const __m128 cos_constants00 =
			// NOLINTNEXTLINE
			_mm_shuffle_ps(cos_coeff_1, cos_coeff_1, _MM_SHUFFLE(0, 0, 0, 0));
		result =
			VMATH_FMADD_PS(result, selected_angles_squared, cos_constants00);

		result = VMATH_FMADD_PS(result, selected_angles_squared,
								vm_v4_one.vector_rep);
		result = _mm_mul_ps(result, sign_lessthan_halfpi);
		*out_cos = result;
	}
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_sin_cos(&out_sin->_inner.x, &out_cos->_inner.x, angles._inner.x);
	vm_sin_cos(&out_sin->_inner.y, &out_cos->_inner.y, angles._inner.y);
	vm_sin_cos(&out_sin->_inner.z, &out_cos->_inner.z, angles._inner.z);
#endif
}

#include "vmath/generated/v3f/v3f_componentwise_add.h"
#include "vmath/generated/v3f/v3f_componentwise_div.h"
#include "vmath/generated/v3f/v3f_componentwise_mul.h"
#include "vmath/generated/v3f/v3f_componentwise_sub.h"

#include "vmath/generated/v3f/v3f_componentwise_constant_add.h"
#include "vmath/generated/v3f/v3f_componentwise_constant_div.h"
#include "vmath/generated/v3f/v3f_componentwise_constant_mul.h"
#include "vmath/generated/v3f/v3f_componentwise_constant_sub.h"

#endif
