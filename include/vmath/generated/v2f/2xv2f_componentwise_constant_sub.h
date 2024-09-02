#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_2batch_v2f_t vm_sub_2xv2f_constant(const vm_2batch_v2f_t a,
												   const float b)
{
#define VMATH_SUB_2XV2_CONSTANT_SCALAR()                                       \
	vm_2batch_v2f_t result;                                                    \
	result.buffer[0].x = a.buffer[0].x - b;                                    \
	result.buffer[0].y = a.buffer[0].y - b;                                    \
	result.buffer[1].x = a.buffer[1].x - b;                                    \
	result.buffer[1].y = a.buffer[1].y - b;                                    \
	return result;
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	return _mm_sub_ps(a, vm_splat_2xv2f(b));
#else
	VMATH_SUB_2XV2_CONSTANT_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_SUB_2XV2_CONSTANT_SCALAR()
#endif
#undef VMATH_SUB_2XV2_CONSTANT_SCALAR
}
