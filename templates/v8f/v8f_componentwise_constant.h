#include "vmath/decl/vec8_f32.h"

VMATH_INLINE vm_v8f_t vm_addc_v8f(const vm_v8f_t a, const vm_float32_t b)
{
#if defined(VMATH_AVX256_GENERIC_ENABLE)

	return _mm256_add_ps(a, vm_splat_v8f(b));

#elif defined(VMATH_SSE41_ENABLE)

	vm_v8f_t out;
	vm_v4f_t temp = vm_splat_v4f(b);
	out.buffer[0] = _mm_add_ps(a.buffer[0], temp);
	out.buffer[1] = _mm_add_ps(a.buffer[1], temp);
	return out;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

	vm_v8f_t out;

#pragma unroll
	for (int i = 0; i < 8; ++i) {
		out.buffer[i] = a.buffer[i] SCALAR_OP b;
	}

	return out;

#endif
}
