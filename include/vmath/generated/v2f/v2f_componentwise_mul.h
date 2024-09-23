#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_v2f_t vm_mul_v2f(const vm_v2f_t a, const vm_v2f_t b)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_mul_ps(a, b);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v2f_t output;
	output._inner.x = a._inner.x * b._inner.x;
	output._inner.y = a._inner.y * b._inner.y;
	return output;
#endif
}
