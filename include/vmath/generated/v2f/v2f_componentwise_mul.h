#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_v2f_t vm_mul_v2f(const vm_v2f_t a, const vm_v2f_t b)
{
#if defined(VMATH_SSE41_ENABLE)
	// clang-format off
    #ifdef VMATH_USE_DISTINCT_TYPE_V2
        vm_v2f_t out;
        out.inner = _mm_mul_ps(a.inner, b.inner);
        return out;
    #else
        return _mm_mul_ps(a, b);
    #endif
	// clang-format on
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v2f_t output;
#ifdef VMATH_USE_DISTINCT_TYPE_V2
	output.inner.buffer[0] = a.inner.buffer[0] * b.inner.buffer[0];
	output.inner.buffer[1] = a.inner.buffer[1] * b.inner.buffer[1];
#else
	output.buffer[0] = a.buffer[0] * b.buffer[0];
	output.buffer[1] = a.buffer[1] * b.buffer[1];
#endif
	return output;
#endif
}
