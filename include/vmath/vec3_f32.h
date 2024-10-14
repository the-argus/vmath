/*
 * Implementation file for vec3 operations. See vmath/decl/vec3_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC3_F32_H
#define __VMATH_VEC3_F32_H

#include "vmath/decl/vec3_f32.h"
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
	output._inner.x = vec->x;
	output._inner.y = vec->y;
	output._inner.z = vec->z;
	return output;
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
