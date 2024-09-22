#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_v2f_t vm_add_v2f_constant(const vm_v2f_t a,
										  const vm_float32_t constant)
{
#define VMATH_ADD_V2_SCALAR()                                                  \
	vm_v2f_t output;                                                           \
	output.buffer[0] = a.buffer[0] SCALAR_OP constant;                         \
	output.buffer[1] = a.buffer[1] SCALAR_OP constant;                         \
	return output;

#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	return _mm_add_ps(a, vm_splat_v2f(constant));
#else
	VMATH_ADD_V2_SCALAR()
#endif
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	VMATH_ADD_V2_SCALAR()
#endif
#undef VMATH_ADD_V2_SCALAR
}
