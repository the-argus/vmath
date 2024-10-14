#include "vmath/decl/vec4_f32.h"

VMATH_INLINE vm_v4f_t vm_add_v4f(const vm_v4f_t a, const vm_v4f_t b)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_add_ps(a, b);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v4f_t result;
	result._inner.x = a._inner.x SCALAR_OP b._inner.x;
	result._inner.y = a._inner.y SCALAR_OP b._inner.y;
	result._inner.z = a._inner.z SCALAR_OP b._inner.z;
	result._inner.w = a._inner.w SCALAR_OP b._inner.w;
	return result;
#endif
}
