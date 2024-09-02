/*
 * Implementation file for vec2 operations. See vmath/decl/vec2_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC2_F32_H
#define __VMATH_VEC2_F32_H

#include "vmath/decl/vec2_f32.h"
#include <assert.h>
#include <math.h>

/*
 * Load / store to and from main memory into SIMD registers (or at least the
 * stack)
 */

VMATH_INLINE vm_v2f_t vm_load_v2f(const vm_v2fs_t vector[1])
{
#define VMATH_LOAD_V2_SCALAR() return vector[0];
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&vector[0].x == (void*)vector);
	// HACK: loading both 32 bit floats as a double. this intrinsic returns
	// __m128d but it is being returned into a __m128. I believe this is safe
	// according to
	// https://stackoverflow.com/questions/67121478/load-or-shuffle-a-pair-of-floats-with-simd-intrinsics-for-doubles
	// but this does not bring me much confidence - Ian
	return _mm_load_sd((double*)&vector->x);
#else
	VMATH_LOAD_V2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LOAD_V2_SCALAR()
#endif
#undef VMATH_LOAD_V2_SCALAR
}

VMATH_INLINE void vm_store_v2f(vm_v2fs_t output[1], const vm_v2f_t vector)
{
#define VMATH_STORE_V2_SCALAR() return vector[0];
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&output[0].x == (void*)output);
	// make sure that output is aligned to double - last 3 bits, or 0b111(7),
	// are all zero
	assert(((size_t)output ^ 7UL) == (size_t)output);
	// HACK: storing both 32 bit floats as a double. see vm_load_v2f
	_mm_store_sd((double*)&output->x, vector);
#else
	VMATH_STORE_V2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_STORE_V2_SCALAR()
#endif
#undef VMATH_STORE_V2_SCALAR
}

VMATH_INLINE vm_8batch_v2f_t vm_load_8xv2f(const vm_v2fs_t batch[8])
{
#define VMATH_LOAD_8XV2_SCALAR()                                               \
	vm_8batch_v2f_t result;                                                    \
	memcpy(&result, batch, sizeof(vm_8batch_v2f_t));                           \
	return result;

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
#if defined(VMATH_AVX2_ENABLE)
	return _mm512_load_ps(batch);
#else
	assert((void*)&batch->x == (void*)batch);
	vm_8batch_v2f_t result;
#pragma unroll
	for (int8_t i = 0; i < 4; ++i) {
		result.buffer[i] = _mm_load_ps(&batch->x);
	}
	return result;
#endif // defined(VMATH_AVX2_ENABLE)
#else
	VMATH_LOAD_8XV2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LOAD_8XV2_SCALAR()
#endif
#undef VMATH_LOAD_8XV2_SCALAR
}

VMATH_INLINE void vm_store_8xv2f(vm_v2fs_t output[8],
								 const vm_8batch_v2f_t* batch)
{
#define VMATH_STORE_8XV2_SCALAR() memcpy(output, batch, sizeof(*batch));

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
#if defined(VMATH_AVX2_ENABLE)
	_mm512_store_ps(output, *batch);
#else
	assert((void*)&output->x == (void*)output);
#pragma unroll
	for (int8_t i = 0; i < 4; ++i) {
		_mm_store_ps(&output[(int8_t)(i * 2)].x, batch->buffer[i]);
	}
#endif // defined(VMATH_AVX2_ENABLE)
#else
	VMATH_STORE_8XV2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_STORE_8XV2_SCALAR()
#endif
#undef VMATH_STORE_8XV2_SCALAR
}

VMATH_INLINE vm_2batch_v2f_t vm_load_2xv2f(const vm_v2fs_t batch[2])
{
#define VMATH_LOAD_2XV2_SCALAR()                                               \
	vm_2batch_v2f_t result;                                                    \
	memcpy(&result, batch, sizeof(vm_2batch_v2f_t));                           \
	return result;

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&batch->x == (void*)batch);
	return _mm_load_ps(&batch->x);
#else
	VMATH_LOAD_2XV2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LOAD_2XV2_SCALAR()
#endif
#undef VMATH_LOAD_2XV2_SCALAR
}

/// Store 2 contiguous vec2s to memory
VMATH_INLINE void vm_store_2xv2f(vm_v2fs_t output[2],
								 const vm_2batch_v2f_t* batch)
{
#define VMATH_STORE_2XV2_SCALAR() memcpy(output, batch, sizeof(*batch));
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&output->x == (void*)output);
	_mm_store_ps(&output->x, *batch);
#else
	VMATH_STORE_2XV2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_STORE_2XV2_SCALAR()
#endif
#undef VMATH_STORE_2XV2_SCALAR
}

VMATH_INLINE vm_v2f_t vm_splat_v2f(vm_float32_t fill)
{
#define VMATH_SPLAT_V2_SCALAR() return (vm_v2f_t){.x = fill, .y = fill};
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	return _mm_set_ps(fill, fill, 0, 0);
#else
	VMATH_SPLAT_V2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_SPLAT_V2_SCALAR()
#endif
#undef VMATH_SPLAT_V2_SCALAR
}

VMATH_INLINE vm_2batch_v2f_t vm_splat_2xv2f(const vm_float32_t fill)
{
#define VMATH_SPLAT_2XV2_SCALAR()                                              \
	return (vm_2batch_v2f_t){.buffer = {(vm_v2fs_t){.x = fill, .y = fill},     \
										(vm_v2fs_t){.x = fill, .y = fill}}};

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	return _mm_set1_ps(fill);
#else
	VMATH_SPLAT_2XV2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_SPLAT_2XV2_SCALAR()
#endif
#undef VMATH_SPLAT_2XV2_SCALAR
}

VMATH_INLINE vm_8batch_v2f_t vm_splat_8xv2f(const vm_float32_t fill)
{
#define VMATH_SPLAT_8XV2_SCALAR()                                              \
	return (vm_8batch_v2f_t){.buffer = {                                       \
								 (vm_v2fs_t){.x = fill, .y = fill},            \
								 (vm_v2fs_t){.x = fill, .y = fill},            \
								 (vm_v2fs_t){.x = fill, .y = fill},            \
								 (vm_v2fs_t){.x = fill, .y = fill},            \
								 (vm_v2fs_t){.x = fill, .y = fill},            \
								 (vm_v2fs_t){.x = fill, .y = fill},            \
								 (vm_v2fs_t){.x = fill, .y = fill},            \
								 (vm_v2fs_t){.x = fill, .y = fill},            \
							 }};

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
#if defined(VMATH_AVX2_ENABLE)
	return _mm512_set1_ps(fill);
#else
	vm_8batch_v2f_t result;
#pragma unroll
	for (int8_t i = 0; i < 4; ++i) {
		result.buffer[i] = _mm_set1_ps(fill);
	}
	return result;
#endif // defined(VMATH_AVX2_ENABLE)
#else
	VMATH_SPLAT_8XV2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_SPLAT_8XV2_SCALAR()
#endif
#undef VMATH_SPLAT_8XV2_SCALAR
}

/*
 * Add / subtract / multiply / divide vec2s, componentwise
 */

#include "vmath/generated/v2f/v2f_componentwise_add.h"
#include "vmath/generated/v2f/v2f_componentwise_div.h"
#include "vmath/generated/v2f/v2f_componentwise_mul.h"
#include "vmath/generated/v2f/v2f_componentwise_sub.h"

#include "vmath/generated/v2f/8xv2f_componentwise_add.h"
#include "vmath/generated/v2f/8xv2f_componentwise_div.h"
#include "vmath/generated/v2f/8xv2f_componentwise_mul.h"
#include "vmath/generated/v2f/8xv2f_componentwise_sub.h"

#include "vmath/generated/v2f/2xv2f_componentwise_add.h"
#include "vmath/generated/v2f/2xv2f_componentwise_div.h"
#include "vmath/generated/v2f/2xv2f_componentwise_mul.h"
#include "vmath/generated/v2f/2xv2f_componentwise_sub.h"

#include "vmath/generated/v2f/v2f_componentwise_constant_add.h"
#include "vmath/generated/v2f/v2f_componentwise_constant_div.h"
#include "vmath/generated/v2f/v2f_componentwise_constant_mul.h"
#include "vmath/generated/v2f/v2f_componentwise_constant_sub.h"

#include "vmath/generated/v2f/8xv2f_componentwise_constant_add.h"
#include "vmath/generated/v2f/8xv2f_componentwise_constant_div.h"
#include "vmath/generated/v2f/8xv2f_componentwise_constant_mul.h"
#include "vmath/generated/v2f/8xv2f_componentwise_constant_sub.h"

#include "vmath/generated/v2f/2xv2f_componentwise_constant_add.h"
#include "vmath/generated/v2f/2xv2f_componentwise_constant_div.h"
#include "vmath/generated/v2f/2xv2f_componentwise_constant_mul.h"
#include "vmath/generated/v2f/2xv2f_componentwise_constant_sub.h"

/*
 * Special operations
 */

VMATH_INLINE float vm_length_v2f(const vm_v2f_t vec)
{
#define VMATH_LENGTH_V2_SCALAR(argname)                                        \
	return sqrtf(((argname).x * (argname).x) + ((argname).y * (argname).y));
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	// multiply all components
	__m128 powd = _mm_mul_ps(vec, vec);
	// horizontal add, x + y is stored in output x and z
	powd = _mm_hadd_ps(powd, powd);
	// sqrt
	powd = _mm_sqrt_ps(powd);
	// read out first component
	vm_float32_t readable;
	_mm_mask_store_ps(&readable, 1, powd);
	return readable;
#else
	VMATH_LENGTH_V2_SCALAR(vec)
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LENGTH_V2_SCALAR(vec)
#endif
#undef VMATH_LENGTH_V2_SCALAR
}

VMATH_INLINE float vm_length_inv_v2f(const vm_v2f_t vec)
{
#define VMATH_LENGTH_INV_V2_SCALAR(argname)                                    \
	return 1.0f /                                                              \
		   sqrtf(((argname).x * (argname).x) + ((argname).y * (argname).y));
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	// multiply all components
	__m128 powd = _mm_mul_ps(vec, vec);
	// horizontal add, x + y is stored in output x and z
	powd = _mm_hadd_ps(powd, powd);
	// 1 / sqrt
	powd = _mm_rsqrt_ps(powd);
	// read out first component
	vm_float32_t readable;
	_mm_mask_store_ps(&readable, 1, powd);
	return readable;
#else
	VMATH_LENGTH_INV_V2_SCALAR(vec)
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LENGTH_INV_V2_SCALAR(vec)
#endif
#undef VMATH_LENGTH_INV_V2_SCALAR
}

VMATH_INLINE float vm_length_sqr_v2f(const vm_v2f_t vec)
{
#define VMATH_LENGTH_SQR_V2_SCALAR(argname)                                    \
	return ((argname).x * (argname).x) + ((argname).y * (argname).y);
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	// TODO: benchmark and actually read the asm- is the mask store better than
	// full store? maybe do the add w/o SIMD since its only two floats?

	// multiply all components
	__m128 powd = _mm_mul_ps(vec, vec);
	// horizontal add, x + y is stored in output x and z
	powd = _mm_hadd_ps(powd, powd);
	// read out first component
	vm_float32_t readable;
	_mm_mask_store_ps(&readable, 1, powd);
	return readable;
#else
	VMATH_LENGTH_SQR_V2_SCALAR(vec)
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LENGTH_SQR_V2_SCALAR(vec)
#endif
#undef VMATH_LENGTH_SQR_V2_SCALAR
}

VMATH_INLINE vm_v2f_t vm_length_v2f_splat(const vm_v2f_t vec)
{
#define VMATH_LENGTH_V2_SPLAT_SCALAR(argname)                                  \
	vm_float32_t value =                                                       \
		sqrtf(((argname).x * (argname).x) + ((argname).y * (argname).y));      \
	return (vm_v2f_t){.x = value, .y = value};
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	// multiply all components
	__m128 powd = _mm_mul_ps(vec, vec);
	// horizontal add, x + y is stored in output x and z
	powd = _mm_hadd_ps(powd, powd);
	// sqrt everything, we only care about sqrt(powd[0]) though
	powd = _mm_sqrt_ps(powd);
	// splat 0
	return _mm_shuffle_ps(powd, powd, _MM_SHUFFLE(0, 0, 0, 0)); // NOLINT
#else
	VMATH_LENGTH_V2_SPLAT_SCALAR(vec)
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LENGTH_V2_SPLAT_SCALAR(vec)
#endif
#undef VMATH_LENGTH_V2_SPLAT_SCALAR
}

VMATH_INLINE vm_v2f_t vm_length_inv_v2f_splat(const vm_v2f_t vec)
{
#define VMATH_LENGTH_INV_V2_SPLAT_SCALAR(argname)                              \
	vm_float32_t value = 1.0 / sqrtf(((argname).x * (argname).x) +             \
									 ((argname).y * (argname).y));             \
	return (vm_v2f_t){.x = value, .y = value};
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	// multiply all components
	__m128 powd = _mm_mul_ps(vec, vec);
	// horizontal add, x + y is stored in output x and z
	powd = _mm_hadd_ps(powd, powd);
	// rsqrt everything, we only care about rsqrt(powd[0]) though
	powd = _mm_rsqrt_ps(powd);
	// splat 0
	return _mm_shuffle_ps(powd, powd, _MM_SHUFFLE(0, 0, 0, 0)); // NOLINT
#else
	VMATH_LENGTH_INV_V2_SPLAT_SCALAR(vec)
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LENGTH_INV_V2_SPLAT_SCALAR(vec)
#endif
#undef VMATH_LENGTH_V2_SPLAT_SCALAR
}

VMATH_INLINE vm_v2f_t vm_length_sqr_v2f_splat(const vm_v2f_t vec)
{
#define VMATH_LENGTH_SQR_V2_SPLAT_SCALAR(argname)                              \
	return ((argname).x * (argname).x) + ((argname).y * (argname).y);
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	// multiply all components
	__m128 powd = _mm_mul_ps(vec, vec);
	// horizontal add, x + y is stored in output x and z
	powd = _mm_hadd_ps(powd, powd);
	// splat len sqred (in x) to all components
	return _mm_shuffle_ps(powd, powd, _MM_SHUFFLE(0, 0, 0, 0)); // NOLINT
#else
	VMATH_LENGTH_SQR_V2_SPLAT_SCALAR(vec)
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_LENGTH_SQR_V2_SPLAT_SCALAR(vec)
#endif
#undef VMATH_LENGTH_SQR_V2_SPLAT_SCALAR
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
