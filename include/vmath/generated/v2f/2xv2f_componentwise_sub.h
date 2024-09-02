#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_2batch_v2f_t vm_sub_2xv2f(const vm_2batch_v2f_t a,
										  const vm_2batch_v2f_t b)
{
#define VMATH_SUB_2XV2_SCALAR()                                                \
	vm_2batch_v2f_t result;                                                    \
	result.buffer[0].x = a.buffer[0].x - b.buffer[0].x;                \
	result.buffer[0].y = a.buffer[0].y - b.buffer[0].y;                \
	result.buffer[1].x = a.buffer[1].x - b.buffer[1].x;                \
	result.buffer[1].y = a.buffer[1].y - b.buffer[1].y;                \
	return result;
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
	return _mm_sub_ps(a, b);
#else
	VMATH_SUB_2XV2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_SUB_2XV2_SCALAR()
#endif
#undef VMATH_SUB_2XV2_SCALAR
}
