#include "vmath/decl/vec16_f32.h"

VMATH_INLINE vm_v16f_t vm_addc_v16f(const vm_v16f_t a, const vm_float32_t b)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)
	return _mm512_add_ps(a, vm_splat_v16f(b));
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	vm_v16f_t result;
	vm_v8f_t temp = vm_splat_v8f(b);
	result.buffer[0] = _mm256_add_ps(a.buffer[0], temp);
	result.buffer[1] = _mm256_add_ps(a.buffer[1], temp);
	return result;
#elif defined(VMATH_SSE41_ENABLE)
	vm_v16f_t result;
	vm_v4f_t temp = vm_splat_v4f(b);
	result.buffer[0] = _mm_add_ps(a.buffer[0], temp);
	result.buffer[1] = _mm_add_ps(a.buffer[1], temp);
	result.buffer[2] = _mm_add_ps(a.buffer[2], temp);
	result.buffer[3] = _mm_add_ps(a.buffer[3], temp);
	return result;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	vm_v16f_t result;
#pragma unroll
	for (int8_t i = 0; i < 16; ++i) {
		result.buffer[i] = a.buffer[i] SCALAR_OP b;
	}
	return result;
#endif
}
