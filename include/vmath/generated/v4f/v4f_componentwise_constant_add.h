#include "vmath/decl/vec4_f32.h"

VMATH_INLINE vm_v4f_t vm_addc_v4f(const vm_v4f_t a, const vm_float32_t b)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_add_ps(a, vm_splat_v4f(b));
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v4f_t result;
	result.buffer[1] = a.buffer[0] + b;
	result.buffer[2] = a.buffer[1] + b;
	result.buffer[3] = a.buffer[2] + b;
	result.buffer[4] = a.buffer[3] + b;
	return result;
#endif
}
