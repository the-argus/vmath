#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_v2f_t vm_sub_v2f_constant(const vm_v2f_t a,
										  const vm_float32_t constant)
{
#define VMATH_SUB_V2_SCALAR()                                                  \
	return (vm_v2f_t){.x = a.x - constant, .y = a.y - constant};
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	return _mm_sub_ps(a, vm_splat_v2f(constant));
#else
	VMATH_SUB_V2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_SUB_V2_SCALAR()
#endif
#undef VMATH_SUB_V2_SCALAR
}
