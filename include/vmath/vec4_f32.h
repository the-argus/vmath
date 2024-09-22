/*
 * Implementation file for vec2 operations. See vmath/decl/vec2_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC4_F32_H
#define __VMATH_VEC4_F32_H

#include "vmath/decl/vec4_f32.h"
#include <assert.h>

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
								 const vm_2batch_v2f_t batch)
{
#define VMATH_STORE_2XV2_SCALAR() memcpy(output, &batch, sizeof(batch));
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&output->x == (void*)output);
	_mm_store_ps(&output->x, batch);
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

#include "vmath/generated/v4f/v4f_componentwise_add.h"
#include "vmath/generated/v4f/v4f_componentwise_div.h"
#include "vmath/generated/v4f/v4f_componentwise_mul.h"
#include "vmath/generated/v4f/v4f_componentwise_sub.h"

#include "vmath/generated/v4f/v4f_componentwise_constant_add.h"
#include "vmath/generated/v4f/v4f_componentwise_constant_div.h"
#include "vmath/generated/v4f/v4f_componentwise_constant_mul.h"
#include "vmath/generated/v4f/v4f_componentwise_constant_sub.h"

#endif
