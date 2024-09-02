#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_v2f_t vm_sub_v2f(const vm_v2f_t a, const vm_v2f_t b)
{
#define VMATH_SUB_V2_SCALAR()                                                  \
	return (vm_v2f_t){.x = a.x - b.x, .y = a.y - b.y};
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	return _mm_sub_ps(a, b);
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
