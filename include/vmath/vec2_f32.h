#ifndef __VMATH_VEC2_F32_H
#define __VMATH_VEC2_F32_H

#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"
#include "vmath/internal/stdint.h"
#include <math.h>
#include <stddef.h>
#include <string.h>

/// Vector of 2 floats for storage in main memory
/// (v -> vector, 2f -> two single-precision floats, s -> storage)
typedef struct VMATH_ALIGNED(8)
{
	vm_float32_t x;
	vm_float32_t y;
} vm_v2fs_t;

#define SCALAR_8BATCH_FALLBACK()                                               \
	typedef struct VMATH_ALIGNED(64)                                           \
	{                                                                          \
		vm_v2fs_t buffer[8];                                                   \
	} vm_8batch_v2f_t;
#define SCALAR_2BATCH_FALLBACK()                                               \
	typedef struct VMATH_ALIGNED(16)                                           \
	{                                                                          \
		vm_v2fs_t buffer[2];                                                   \
	} vm_8batch_v2f_t;

/// define vm_8batch_v2f_t -> batch of 8 vec2s, each with 2 single-precision
/// floating point values
/// also vm_2batch_v2f_t -> batch of 2 vec2s, each with 2 single-precision
/// floating point values
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
// always use SSE types and instructions for smaller batches
typedef __m128 vm_2batch_v2f_t;
// with avx, use native 8batch
// for SSE, 8batch needs to be emulated with smaller batches
#if defined(VMATH_AVX2_ENABLE)
typedef __m512 vm_8batch_v2f_t;
#else
typedef struct VMATH_ALIGNED(64)
{
	__m128 buffer[4];
} vm_8batch_v2f_t;
#endif // defined(VMATH_AVX2_ENABLE)
#else
// in this case, there is no sse 4.1, emulate it with scalar
SCALAR_8BATCH_FALLBACK()
SCALAR_2BATCH_FALLBACK()
#endif // defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
/*
 * Scalar fallback. 32 bit machine or something
 */
SCALAR_8BATCH_FALLBACK()
SCALAR_2BATCH_FALLBACK()
#endif

/*
 * Load / store to and from main memory into SIMD registers (or at least the
 * stack)
 */

/// Load 8 contiguous vec2s from memory
VMATH_INLINE vm_8batch_v2f_t vm_load_8xv2(const vm_v2fs_t batch[8])
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
	vm_8batch_v2f_t result;
#pragma unroll
	for (uint8_t i = 0; i < 4; ++i) {
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

/// Store 8 contiguous vec2s to memory
VMATH_INLINE void vm_store_8xv2(vm_v2fs_t output[8],
								const vm_8batch_v2f_t* batch)
{
#define VMATH_STORE_8XV2_SCALAR()                                              \
	memcpy(output, batch, sizeof(vm_8batch_v2f_t));

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
#if defined(VMATH_AVX2_ENABLE)
	_mm512_store_ps(output, *batch);
#else
#pragma unroll
	for (uint8_t i = 0; i < 4; ++i) {
		_mm_store_ps(&output[(uint8_t)(i * 2)].x, batch->buffer[i]);
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

/*
 * Add / subtract / multiply / divide two vec2, componentwise
 */

VMATH_INLINE vm_v2fs_t vm_vec2_f32_add(const vm_v2fs_t a, const vm_v2fs_t b)
{
	return (vm_v2fs_t){a.x + b.x, a.y + b.y};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_sub(const vm_v2fs_t a, const vm_v2fs_t b)
{
	return (vm_v2fs_t){a.x - b.x, a.y - b.y};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_mul(const vm_v2fs_t a, const vm_v2fs_t b)
{
	return (vm_v2fs_t){a.x * b.x, a.y * b.y};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_div(const vm_v2fs_t a, const vm_v2fs_t b)
{
	return (vm_v2fs_t){a.x / b.x, a.y / b.y};
}

/*
 * Add / subtract / multiply / divide with constant
 */

VMATH_INLINE vm_v2fs_t vm_vec2_f32_add_constant(const vm_v2fs_t vec,
												float constant)
{
	return (vm_v2fs_t){vec.x + constant, vec.y + constant};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_sub_constant(const vm_v2fs_t vec,
												float constant)
{
	return (vm_v2fs_t){vec.x - constant, vec.y - constant};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_mul_constant(const vm_v2fs_t vec,
												float constant)
{
	return (vm_v2fs_t){vec.x * constant, vec.y * constant};
}

VMATH_INLINE vm_v2fs_t vm_vec2_f32_div_constant(const vm_v2fs_t vec,
												float constant)
{
	return (vm_v2fs_t){vec.x / constant, vec.y / constant};
}

/*
 * Special operations
 */

VMATH_INLINE float vm_vec2_f32_length(const vm_v2fs_t vec)
{
	return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

VMATH_INLINE float vm_vec2_f32_length_sqr(const vm_v2fs_t vec)
{
	return (vec.x * vec.x) + (vec.y * vec.y);
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
