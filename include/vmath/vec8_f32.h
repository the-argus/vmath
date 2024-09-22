#ifndef __VMATH_VEC4_F32_H
#define __VMATH_VEC4_F32_H

#include "vmath/decl/vec8_f32.h"
#include "vmath/internal/memutil.h"
#include <assert.h>

VMATH_INLINE vm_v8f_t vm_load_v8f(const vm_v8fs_t* vec)
{
	assert(vm_mem_is_aligned(vec, 32));
#if defined(VMATH_AVX256_GENERIC_ENABLE)
	return _mm256_load_ps(vec->buffer);
#elif defined(VMATH_SSE41_ENABLE)
	vm_v8f_t out;
	out.buffer[0] = _mm_load_ps(vec->buffer);
	out.buffer[1] = _mm_load_ps(vec->buffer + 4);
	return out;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	vm_v8f_t out;
#pragma unroll
	for (int i = 0; i < 8; ++i) {
		out.buffer[i] = vec->buffer[i];
	}
	return out;

#endif
}

VMATH_INLINE vm_v8f_t vm_loadb_v8f(const vm_float32_t vec[8])
{
	assert(sizeof(vm_float32_t[8]) == sizeof(vm_v8fs_t));
	return vm_load_v8f((const vm_v8fs_t*)vec);
}

VMATH_INLINE void vm_store_v8f(vm_v8fs_t* output, vm_v8f_t vec)
{
	assert(vm_mem_is_aligned(output, 32));
#if defined(VMATH_AVX256_GENERIC_ENABLE)
	_mm256_store_ps(output->buffer, vec);
#elif defined(VMATH_SSE41_ENABLE)
	_mm_store_ps(output->buffer, vec.buffer[0]);
	_mm_store_ps(output->buffer + 4, vec.buffer[1]);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	// TODO: maybe faster with memcpy? check disasm
#pragma unroll
	for (int i = 0; i < 8; ++i) {
		output->buffer[i] = vec->buffer[i];
	}

#endif
}

VMATH_INLINE void vm_storeb_v8f(vm_float32_t output[8], vm_v8f_t vec)
{
	assert(sizeof(vm_float32_t[8]) == sizeof(vm_v8fs_t));
	vm_store_v8f((vm_v8fs_t*)output, vec);
}

VMATH_INLINE vm_v8f_t vm_splat_v8f(vm_float32_t fill)
{
#if defined(VMATH_AVX256_GENERIC_ENABLE)
	return _mm256_set1_ps(fill);
#elif defined(VMATH_SSE41_ENABLE)
	vm_v8f_t out;
	out.buffer[0] = _mm_set1_ps(fill);
	out.buffer[1] = _mm_set1_ps(fill);
	return out;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	vm_v8f_t out;
#pragma unroll
	for (int i = 0; i < 8; ++i) {
		out->buffer[i] = fill;
	}
	return out;

#endif
}

#include "vmath/generated/v8f/v8f_componentwise_add.h"
#include "vmath/generated/v8f/v8f_componentwise_div.h"
#include "vmath/generated/v8f/v8f_componentwise_mul.h"
#include "vmath/generated/v8f/v8f_componentwise_sub.h"

#include "vmath/generated/v8f/v8f_componentwise_constant_add.h"
#include "vmath/generated/v8f/v8f_componentwise_constant_div.h"
#include "vmath/generated/v8f/v8f_componentwise_constant_mul.h"
#include "vmath/generated/v8f/v8f_componentwise_constant_sub.h"

#endif
