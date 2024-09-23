/*
 * Implementation file for vec2 operations. See vmath/decl/vec2_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC4_F32_H
#define __VMATH_VEC4_F32_H

#include "vmath/decl/vec4_f32.h"
#include "vmath/internal/memutil.h"
#include <assert.h>

VMATH_INLINE vm_v4f_t vm_load_v4f(const vm_v4fs_t* const vec)
{
	assert(vm_mem_is_aligned(vec, 16));
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&vec->x == (void*)vec); // assert x is first in struct
	return _mm_load_ps(&vec->x);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v4f_t result;
	result.buffer[0] = vec->x;
	result.buffer[1] = vec->y;
	result.buffer[2] = vec->z;
	result.buffer[3] = vec->w;
	return result;
#endif
}

VMATH_INLINE vm_v4f_t vm_loadb_v4f(const vm_float32_t vec[4])
{
	assert(sizeof(vm_float32_t[4]) == sizeof(vm_v4fs_t));
	return vm_load_v4f((const vm_v4fs_t*)vec);
}

VMATH_INLINE void vm_store_v4f(vm_v4fs_t* output, vm_v4f_t vec)
{
	assert(vm_mem_is_aligned(output, 16));
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&output->x == (void*)output); // assert x is first in struct
	_mm_store_ps(&output->x, vec);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	output->x = vec.buffer[0];
	output->y = vec.buffer[1];
	output->z = vec.buffer[2];
	output->w = vec.buffer[3];
#endif
}

VMATH_INLINE void vm_storeb_v4f(vm_float32_t output[4], vm_v4f_t vec)
{
	assert(sizeof(vm_float32_t[4]) == sizeof(vm_v4fs_t));
	vm_store_v4f((vm_v4fs_t*)output, vec);
}

VMATH_INLINE vm_v4f_t vm_splat_v4f(vm_float32_t fill)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_set1_ps(fill);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v4f_t out;
	out.buffer[0] = fill;
	out.buffer[1] = fill;
	out.buffer[2] = fill;
	out.buffer[3] = fill;
	return out;
#endif
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
