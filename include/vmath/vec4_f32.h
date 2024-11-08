/*
 * Implementation file for vec2 operations. See vmath/decl/vec2_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC4_F32_H
#define __VMATH_VEC4_F32_H

#include "vmath/decl/vec4_f32.h"
#include "vmath/scalar.h"
#include <assert.h>

VMATH_INLINE vm_v4f_t vm_load_v4f(const vm_v4fs_t* const vec)
{
	assert(vec);
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&vec->x == (void*)vec); // assert x is first in struct
	return _mm_loadu_ps(&vec->x);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v4f_t result;
	result._inner.x = vec->x;
	result._inner.y = vec->y;
	result._inner.z = vec->z;
	result._inner.w = vec->w;
	return result;
#endif
}

VMATH_INLINE vm_v4f_t vm_loadb_v4f(const vm_float32_t vec[4])
{
	assert(vec);
	assert(sizeof(vm_float32_t[4]) == sizeof(vm_v4fs_t));
	return vm_load_v4f((const vm_v4fs_t*)vec);
}

VMATH_INLINE void vm_store_v4f(vm_v4fs_t* output, vm_v4f_t vec)
{
	assert(output);
#if defined(VMATH_SSE41_ENABLE)
	assert((void*)&output->x == (void*)output); // assert x is first in struct
	_mm_storeu_ps(&output->x, vec);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	output->x = vec._inner.x;
	output->y = vec._inner.y;
	output->z = vec._inner.z;
	output->w = vec._inner.w;
#endif
}

VMATH_INLINE void vm_storeb_v4f(vm_float32_t output[4], vm_v4f_t vec)
{
	assert(output);
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
	out._inner.x = fill;
	out._inner.y = fill;
	out._inner.z = fill;
	out._inner.w = fill;
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

VMATH_INLINE vm_v4f_t vm_nearest_int_round_v4f(vm_v4f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	// NOLINTNEXTLINE
	return _mm_round_ps(vec, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v4f_t out;
	out._inner.x = vm_nearest_int_round(vec._inner.x);
	out._inner.y = vm_nearest_int_round(vec._inner.y);
	out._inner.z = vm_nearest_int_round(vec._inner.z);
	out._inner.w = vm_nearest_int_round(vec._inner.w);
	return out;
#endif
}

VMATH_INLINE vm_v4f_t vm_negative_multiply_subtract_v4f(vm_v4f_t mul1,
														vm_v4f_t mul2,
														vm_v4f_t base)
{
#if defined(VMATH_SSE41_ENABLE)
	return VMATH_FNMADD_PS(mul1, mul2, base);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v4f_t out;
	out._inner.x = base._inner.x - (mul1._inner.x * mul2._inner.x);
	out._inner.y = base._inner.y - (mul1._inner.y * mul2._inner.y);
	out._inner.z = base._inner.z - (mul1._inner.z * mul2._inner.z);
	out._inner.w = base._inner.w - (mul1._inner.w * mul2._inner.w);
	return out;
#endif
}

#endif
