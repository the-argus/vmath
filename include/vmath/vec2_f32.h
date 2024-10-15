/*
 * Implementation file for vec2 operations. See vmath/decl/vec2_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC2_F32_H
#define __VMATH_VEC2_F32_H

#include "vmath/decl/constants.h"
#include "vmath/decl/vec2_f32.h"
#include <assert.h>
#include <math.h>

VMATH_INLINE vm_v2f_t vm_load_v2f(const vm_v2fs_t* vec)
{
	assert(vec);

#if defined(VMATH_SSE41_ENABLE)
	// assert that x is at the beginning of the struct
	assert((void*)&vec->x == (void*)vec);
	return _mm_castpd_ps(_mm_load_sd((const double*)&vec->x));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v2f_t out;
	out._inner = *vec;
	return out;
#endif
}

VMATH_INLINE vm_v2f_t vm_loadb_v2f(const vm_float32_t vec[2])
{
	assert(vec);
	assert(sizeof(vm_float32_t[2]) == sizeof(vm_v2fs_t));
	// regular load includes alignment assert
	return vm_load_v2f((const vm_v2fs_t*)vec);
}

VMATH_INLINE void vm_store_v2f(vm_v2fs_t* const output, const vm_v2f_t vector)
{
	assert(output);
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&output[0].x == (void*)output);
	// HACK: storing both 32 bit floats as a double. see vm_load_v2f
	_mm_store_sd((double*)&output->x, _mm_castps_pd(vector));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	*output = vector._inner;
#endif
}

VMATH_INLINE void vm_storeb_v2f(vm_float32_t output[2], vm_v2f_t vector)
{
	assert(output);
	assert(sizeof(vm_float32_t[2]) == sizeof(vm_v2fs_t));
	vm_store_v2f((vm_v2fs_t*)output, vector);
}

VMATH_INLINE vm_v2f_t vm_splat_v2f(vm_float32_t fill)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_set_ps(0, 0, fill, fill);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v2f_t output;
	output._inner.x = fill;
	output._inner.y = fill;
	return output;
#endif
}

VMATH_INLINE vm_v2f_t vm_load_ones_v2f(void)
{
	return vm_shave4_v2f(vm_v4_ones.vector_rep);
}

VMATH_INLINE vm_v2f_t vm_load_zeroes_v2f(void)
{
	return vm_shave4_v2f(vm_v4_zeroes.vector_rep);
}

/*
 * Add / subtract / multiply / divide vec2s, componentwise
 */

#include "vmath/generated/v2f/v2f_componentwise_add.h"
#include "vmath/generated/v2f/v2f_componentwise_div.h"
#include "vmath/generated/v2f/v2f_componentwise_mul.h"
#include "vmath/generated/v2f/v2f_componentwise_sub.h"

#include "vmath/generated/v2f/v2f_componentwise_constant_add.h"
#include "vmath/generated/v2f/v2f_componentwise_constant_div.h"
#include "vmath/generated/v2f/v2f_componentwise_constant_mul.h"
#include "vmath/generated/v2f/v2f_componentwise_constant_sub.h"

/*
 * Special operations
 */

VMATH_INLINE vm_v2f_t vm_length_v2f(vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_sqrt_ps(vm_length_sqr_v2f(vec));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_float32_t value = vm_lengthx_v2f(vec);
	vm_v2f_t out;
	out._inner.x = value;
	out._inner.y = value;
	return out;
#endif
}

VMATH_INLINE vm_v2f_t vm_length_inv_v2f(const vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_div_ps(vm_load_ones_v2f(), _mm_sqrt_ps(vm_length_sqr_v2f(vec)));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_float32_t value = vm_length_invx_v2f(vec);
	vm_v2f_t out;
	out._inner.x = value;
	out._inner.y = value;
	return out;
#endif
}

VMATH_INLINE vm_v2f_t vm_length_inv_est_v2f(const vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_rsqrt_ps(vm_length_sqr_v2f(vec));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_float32_t value = vm_length_invx_v2f(vec);
	vm_v2f_t out;
	out._inner.x = value;
	out._inner.y = value;
	return out;
#endif
}

VMATH_INLINE vm_v2f_t vm_length_sqr_v2f(vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return vm_dot_v2f(vec, vec);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_float32_t value = vm_length_sqrx_v2f(vec);
	vm_v2f_t out;
	out._inner.x = value;
	out._inner.y = value;
	return out;
#endif
}

// vm_length_v2f, except it reads out the value to a float in memory
VMATH_INLINE vm_float32_t vm_lengthx_v2f(vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	// dot product with self -> sqrt -> extract x component
	return _mm_cvtss_f32(_mm_sqrt_ps(vm_length_sqr_v2f(vec)));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	const float x = vec._inner.x;
	const float y = vec._inner.y;
	return sqrt((x * x) + (y * y));
#endif
}

VMATH_INLINE vm_float32_t vm_length_inv_estx_v2f(vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_cvtss_f32(_mm_rsqrt_ps(vm_length_sqr_v2f(vec)));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	const float x = vec._inner.x;
	const float y = vec._inner.y;
	return 1.0 / sqrt((x * x) + (y * y));
#endif
}

VMATH_INLINE vm_float32_t vm_length_invx_v2f(vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_cvtss_f32(
		_mm_div_ps(vm_load_ones_v2f(), _mm_sqrt_ps(vm_length_sqr_v2f(vec))));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	const float x = vec._inner.x;
	const float y = vec._inner.y;
	return 1.0 / sqrt((x * x) + (y * y));
#endif
}

VMATH_INLINE vm_float32_t vm_length_sqrx_v2f(vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_cvtss_f32(vm_dot_v2f(vec, vec));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	const float x = vec._inner.x;
	const float y = vec._inner.y;
	return (x * x) + (y * y);
#endif
}

VMATH_INLINE vm_v2f_t vm_shave4_v2f(vm_v4f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	// top elements contents are undefined, we dont need to zero them
	return vec;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v2f_t out;
	out._inner.x = vec._inner.x;
	out._inner.y = vec._inner.y;
	return out;
#endif
}

VMATH_INLINE vm_float32_t vm_extract_x_v2f(vm_v2f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_cvtss_f32(vec);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	return vec._inner.x;
#endif
}

VMATH_INLINE vm_v2f_t vm_dot_v2f(vm_v2f_t vec1, vm_v2f_t vec2)
{
#if defined(VMATH_SSE41_ENABLE)
	// 0x3f == 0011 1111, AKA "multiply + add bottom two floats, store all the
	// result to all four outputs
	return _mm_dp_ps(vec1, vec2, 0x3f);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_float32_t value =
		(vec1._inner.x * vec2._inner.x) + (vec1._inner.y * vec2._inner.y);
	vm_v2f_t out;
	out._inner.x = value;
	out._inner.y = value;
	return out;
#endif
}

VMATH_INLINE vm_v2f_t vm_distance_v2f(vm_v2f_t vec1, vm_v2f_t vec2)
{
	return vm_length_v2f(vm_sub_v2f(vec2, vec1));
}

VMATH_INLINE vm_v2f_t vm_distance_sqr_v2f(vm_v2f_t vec1, vm_v2f_t vec2)
{
	return vm_length_sqr_v2f(vm_sub_v2f(vec2, vec1));
}

VMATH_INLINE vm_v2f_t vm_angle_v2f(vm_v2f_t vec1, vm_v2f_t vec2)
{
	// TODO: vector atan2... polynomial approximation :(
	assert(0);
}

VMATH_INLINE vm_v2f_t vm_normalize_v2f(vm_v2f_t vec) {}

VMATH_INLINE vm_v2f_t vm_lerp_v2f(vm_v2f_t vec1, vm_v2f_t vec2,
								  vm_v2f_t amount);
VMATH_INLINE vm_v2f_t vm_reflect_v2f(vm_v2f_t vec, vm_v2f_t normal);
VMATH_INLINE vm_v2f_t vm_move_towards_v2f(vm_v2f_t vec, vm_v2f_t target,
										  vm_v2f_t max_distance);
VMATH_INLINE vm_v2f_t vm_clamp_axes_v2f(vm_v2f_t vec, vm_v2f_t min,
										vm_v2f_t max);
VMATH_INLINE vm_v2f_t vm_clamp_magnitude_v2f(vm_v2f_t vec, vm_v2f_t range);

VMATH_INLINE vm_float32_t vm_vec2_f32_dot(const vm_v2fs_t a, const vm_v2fs_t b)
{
	return (a.x * b.x) + (a.y * b.y);
}

VMATH_INLINE int8_t vm_vec2_f32_eql(const vm_v2fs_t a, const vm_v2fs_t b)
{
	return (int8_t)(a.x == b.x && a.y == b.y);
}

VMATH_INLINE float vm_vec2_f32_distance(const vm_v2fs_t a, const vm_v2fs_t b)
{
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

VMATH_INLINE float vm_vec2_f32_distance_sqr(const vm_v2fs_t a,
											const vm_v2fs_t b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_normalize(const vm_v2fs_t vec)
{
	const float length = sqrtf((vec.x * vec.x) + (vec.y * vec.y));

	if (length > 0) {
		const float ilength = 1.0F / length;
		return (vm_v2fs_t){vec.x * ilength, vec.y * ilength};
	}

	return (vm_v2fs_t){0};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_lerp(const vm_v2fs_t a, const vm_v2fs_t b,
										const float amount)
{
	return (vm_v2fs_t){
		.x = a.x + amount * (b.x - a.x),
		.y = a.y + amount * (b.y - a.y),
	};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_reflect(const vm_v2fs_t vec,
										   const vm_v2fs_t normal)
{
	const float dotProduct = (vec.x * normal.x + vec.y * normal.y);

	return (vm_v2fs_t){
		.x = vec.x - (2.0F * normal.x) * dotProduct,
		.y = vec.y - (2.0F * normal.y) * dotProduct,
	};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_min(const vm_v2fs_t v1, const vm_v2fs_t v2)
{
	return (vm_v2fs_t){
		.x = fminf(v1.x, v2.x),
		.y = fminf(v1.y, v2.y),
	};
}

// Get max value for each pair of components
VMATH_INLINE vm_v2fs_t vm_vec2_f32_max(const vm_v2fs_t v1, const vm_v2fs_t v2)
{
	return (vm_v2fs_t){
		.x = fmaxf(v1.x, v2.x),
		.y = fmaxf(v1.y, v2.y),
	};
}

#endif
