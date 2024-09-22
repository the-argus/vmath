#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_v2f_t vm_subc_v2f(const vm_v2f_t a, const vm_float32_t constant)
{
#if defined(VMATH_SSE41_ENABLE)
	// clang-format off
    #ifdef VMATH_USE_DISTINCT_TYPE_V2
        vm_v2f_t out;
        out.inner = _mm_sub_ps(a.inner, vm_splat_v2f(constant).inner);
        return out;
    #else
        return _mm_sub_ps(a, vm_splat_v2f(constant));
    #endif
	// clang-format on
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v2f_t output;
#ifdef VMATH_USE_DISTINCT_TYPE_V2
	output.inner.buffer[0] = a.inner.buffer[0] - constant;
	output.inner.buffer[1] = a.inner.buffer[1] - constant;
#else
	output.buffer[0] = a.buffer[0] - constant;
	output.buffer[1] = a.buffer[1] - constant;
#endif
	return output;
#endif
}
