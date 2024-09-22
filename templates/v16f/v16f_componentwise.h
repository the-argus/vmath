#include "vmath/decl/vec16_f32.h"
#include "vmath/internal/stdint.h" // used in scalar mode

VMATH_INLINE vm_v16f_t vm_add_v16f(const vm_v16f_t a, const vm_v16f_t b)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)
	return _mm512_add_ps(a, b);
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	vm_v16f_t result;
	result.buffer[0] = _mm256_add_ps(a.buffer[0], b.buffer[0]);
	result.buffer[1] = _mm256_add_ps(a.buffer[1], b.buffer[1]);
	return result;
#elif defined(VMATH_SSE41_ENABLE)
	vm_v16f_t result;
	result.buffer[0] = _mm_add_ps(a.buffer[0], b.buffer[0]);
	result.buffer[1] = _mm_add_ps(a.buffer[1], b.buffer[1]);
	result.buffer[2] = _mm_add_ps(a.buffer[2], b.buffer[2]);
	result.buffer[3] = _mm_add_ps(a.buffer[3], b.buffer[3]);
	return result;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	vm_v16f_t result;
#pragma unroll
	for (int8_t i = 0; i < 16; ++i) {
		result.buffer[i] = a.buffer[i] SCALAR_OP b.buffer[i];
	}
	return result;
#endif
}
