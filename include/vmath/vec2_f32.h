/*
 * Implementation file for vec2 operations. See vmath/decl/vec2_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC2_F32_H
#define __VMATH_VEC2_F32_H

#include "vmath/decl/vec2_f32.h"
#include "vmath/internal/memutil.h"
#include "vmath/vec4_f32.h"
#include <assert.h>
#include <math.h>

VMATH_INLINE vm_v2f_t vm_load_v2f(const vm_v2fs_t* vec)
{
	assert(vec);
	assert(vm_mem_is_aligned(vec, 8));

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
	assert(vm_mem_is_aligned(output, 8));

#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&output[0].x == (void*)output);
	// HACK: storing both 32 bit floats as a double. see vm_load_v2f
	_mm_store_sd((double*)&output->x, vector);
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

VMATH_INLINE vm_v2f_t vm_load4_v2f(const vm_v4fs_t* vec)
{
	assert(vec);
	assert(vm_mem_is_aligned(vec, 16));
#ifdef VMATH_SIMD_ENABLED // when using simd, vec4 and vec2 are not distinct
	return vm_load_v4f(vec);
#else
	vm_v2f_t out;
	out._inner.x = vec->x;
	out._inner.y = vec->y;
	return out;
#endif
}

VMATH_INLINE vm_v2f_t vm_loadb4_v2f(const vm_float32_t vec[4])
{
	assert(vec);
	assert(vm_mem_is_aligned(vec, 16));
#ifdef VMATH_SIMD_ENABLED // when using simd, vec4 and vec2 are not distinct
	return vm_loadb_v4f(vec);
#else
	vm_v2f_t out;
	out._inner.x = vec[0];
	out._inner.y = vec[1];
	return out;
#endif
}

VMATH_INLINE void vm_store4_v2f(vm_v4fs_t* output, vm_v2f_t vector)
{
	assert(output);
	assert(vm_mem_is_aligned(output, 16));
#ifdef VMATH_SIMD_ENABLED // when using simd, vec4 and vec2 are not distinct
	vm_store_v4f(output, vector);
#else
	output->x = vector._inner.x;
	output->y = vector._inner.y;
#endif
}

VMATH_INLINE void vm_storeb4_v2f(vm_float32_t output[4], vm_v2f_t vector)
{
	assert(output);
	assert(vm_mem_is_aligned(output, 16));
#ifdef VMATH_SIMD_ENABLED // when using simd, vec4 and vec2 are not distinct
	vm_storeb_v4f(output, vector);
#else
	output[0] = vector._inner.x;
	output[1] = vector._inner.y;
#endif
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

/*
 * Load constants
 * TODO: global constants + regular loads, no splat
 */

VMATH_INLINE vm_v2f_t vm_load_ones_v2f(void) { return vm_splat_v2f(1.F); }
VMATH_INLINE vm_v2f_t vm_load_zeroes_v2f(void) { return vm_splat_v2f(0.F); }

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
	// 0x3f == 0011 1111, AKA "multiply + add bottom two floats, store all the
	// result to all four outputs
	return _mm_dp_ps(vec, vec, 0x3f);
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
	return _mm_cvtss_f32(_mm_dp_ps(vec, vec, 0x3f));
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
