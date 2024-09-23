#ifndef __VMATH_VEC16_F32_H
#define __VMATH_VEC16_F32_H

#include "vmath/decl/vec16_f32.h"
#include "vmath/internal/memutil.h"
#include <assert.h>

VMATH_INLINE vm_v16f_t vm_load_v16f(const vm_v16fs_t* vec)
{
	assert(vm_mem_is_aligned(vec, 64));

#if defined(VMATH_AVX512_GENERIC_ENABLE)

	return _mm512_load_ps(vec->buffer);

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

	vm_v16f_t out;
	out.buffer[0] = _mm256_load_ps(vec->buffer);
	out.buffer[1] = _mm256_load_ps(vec->buffer + 8);
	return out;

#elif defined(VMATH_SSE41_ENABLE)

	vm_v16f_t out;
	out.buffer[0] = _mm_load_ps(vec->buffer);
	out.buffer[1] = _mm_load_ps(vec->buffer + 4);
	out.buffer[2] = _mm_load_ps(vec->buffer + 8);
	out.buffer[3] = _mm_load_ps(vec->buffer + 12);
	return out;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	// TODO: maybe memcpy better here?
	vm_v16f_t out;
#pragma unroll
	for (int i = 0; i < 16; ++i) {
		out.buffer[i] = vec->buffer[i];
	}
	return out;

#endif
}

VMATH_INLINE vm_v16f_t vm_loadb_v16f(const vm_float32_t vec[16])
{
	assert(sizeof(vm_float32_t[16]) == sizeof(vm_v16fs_t));
	return vm_load_v16f((const vm_v16fs_t*)vec);
}

VMATH_INLINE void vm_store_v16f(vm_v16fs_t* output, vm_v16f_t vec)
{
	assert(vm_mem_is_aligned(output, 64));

#if defined(VMATH_AVX512_GENERIC_ENABLE)

	_mm512_store_ps(output, vec);

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

	_mm256_store_ps(output->buffer, vec.buffer[0]);
	_mm256_store_ps(output->buffer + 8, vec.buffer[1]);

#elif defined(VMATH_SSE41_ENABLE)

	_mm_store_ps(output->buffer, vec.buffer[0]);
	_mm_store_ps(output->buffer + 4, vec.buffer[1]);
	_mm_store_ps(output->buffer + 8, vec.buffer[2]);
	_mm_store_ps(output->buffer + 12, vec.buffer[3]);

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	// TODO: maybe memcpy better here?
#pragma unroll
	for (int i = 0; i < 16; ++i) {
		output->buffer[i] = vec.buffer[i];
	}

#endif
}

VMATH_INLINE void vm_storeb_v16f(vm_float32_t output[16], vm_v16f_t vec)
{
	assert(sizeof(vm_float32_t[16]) == sizeof(vm_v16fs_t));
	vm_store_v16f((vm_v16fs_t*)output, vec);
}

VMATH_INLINE vm_v16f_t vm_splat_v16f(vm_float32_t fill)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)

	return _mm512_set1_ps(fill);

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

	vm_v16f_t out;
	out.buffer[0] = _mm256_set1_ps(fill);
	out.buffer[1] = _mm256_set1_ps(fill);
	return out;

#elif defined(VMATH_SSE41_ENABLE)

	vm_v16f_t out;
	out.buffer[0] = _mm_set1_ps(fill);
	out.buffer[1] = _mm_set1_ps(fill);
	out.buffer[2] = _mm_set1_ps(fill);
	out.buffer[3] = _mm_set1_ps(fill);
	return out;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	vm_v16f_t out;
#pragma unroll
	for (int i = 0; i < 16; ++i) {
		out.buffer[i] = fill;
	}
	return out;

#endif
}

#include "vmath/generated/v16f/v16f_componentwise_add.h"
#include "vmath/generated/v16f/v16f_componentwise_div.h"
#include "vmath/generated/v16f/v16f_componentwise_mul.h"
#include "vmath/generated/v16f/v16f_componentwise_sub.h"

#include "vmath/generated/v16f/v16f_componentwise_constant_add.h"
#include "vmath/generated/v16f/v16f_componentwise_constant_div.h"
#include "vmath/generated/v16f/v16f_componentwise_constant_mul.h"
#include "vmath/generated/v16f/v16f_componentwise_constant_sub.h"

#endif
