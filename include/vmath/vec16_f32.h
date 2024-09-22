#ifndef __VMATH_VEC16_F32_H
#define __VMATH_VEC16_F32_H

#include "vmath/decl/vec16_f32.h"
#include "vmath/internal/memutil.h"
#include <assert.h>

VMATH_INLINE vm_8batch_v2f_t vm_load_8xv2f(const vm_v2fs_t batch[8])
{
#define VMATH_LOAD_8XV2_SCALAR()                                               \
	vm_8batch_v2f_t result;                                                    \
	memcpy(&result, batch, sizeof(vm_8batch_v2f_t));                           \
	return result;

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
#if defined(VMATH_AVX512_GENERIC_ENABLE)
	return _mm512_load_ps(batch);
#else
	assert((void*)&batch->x == (void*)batch);
	vm_8batch_v2f_t result;
#pragma unroll
	for (int8_t i = 0; i < 4; ++i) {
		result.buffer[i] = _mm_load_ps(&batch[i * 2UL].x);
	}
	return result;
#endif // defined(VMATH_AVX512_GENERIC_ENABLE)
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
								 const vm_8batch_v2f_t batch)
{
#define VMATH_STORE_8XV2_SCALAR() memcpy(output, &batch, sizeof(batch));

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
#if defined(VMATH_AVX512_GENERIC_ENABLE)
	_mm512_store_ps(output, batch);
#else
	assert((void*)&output->x == (void*)output);
#pragma unroll
	for (int8_t i = 0; i < 4; ++i) {
		_mm_store_ps(&output[(int8_t)(i * 2)].x, batch.buffer[i]);
	}
#endif // defined(VMATH_AVX512_GENERIC_ENABLE)
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
#if defined(VMATH_AVX512_GENERIC_ENABLE)
	return _mm512_set1_ps(fill);
#else
	vm_8batch_v2f_t result;
#pragma unroll
	for (int8_t i = 0; i < 4; ++i) {
		result.buffer[i] = _mm_set1_ps(fill);
	}
	return result;
#endif // defined(VMATH_AVX512_GENERIC_ENABLE)
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

#include "vmath/generated/v2f/8xv2f_componentwise_add.h"
#include "vmath/generated/v2f/8xv2f_componentwise_div.h"
#include "vmath/generated/v2f/8xv2f_componentwise_mul.h"
#include "vmath/generated/v2f/8xv2f_componentwise_sub.h"

#include "vmath/generated/v2f/8xv2f_componentwise_constant_add.h"
#include "vmath/generated/v2f/8xv2f_componentwise_constant_div.h"
#include "vmath/generated/v2f/8xv2f_componentwise_constant_mul.h"
#include "vmath/generated/v2f/8xv2f_componentwise_constant_sub.h"

#endif
