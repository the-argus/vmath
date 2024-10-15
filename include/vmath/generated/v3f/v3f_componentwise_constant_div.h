#include "vmath/decl/vec3_f32.h"

VMATH_INLINE vm_v3f_t vm_divc_v3f(const vm_v3f_t a, const vm_float32_t b)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_div_ps(a, vm_splat_v3f(b));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3f_t result;
	result._inner.x = a._inner.x / b;
	result._inner.y = a._inner.y / b;
	result._inner.z = a._inner.z / b;
	return result;
#endif
}
