#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_8batch_v2f_t vm_div_8xv2f(const vm_8batch_v2f_t a,
										  const vm_8batch_v2f_t b)
{
#define VMATH_DIV_8XV2_SCALAR()                                                \
	vm_8batch_v2f_t result;                                                    \
	for (int8_t i = 0; i < 8; ++i) {                                           \
		result.buffer[i].x = a.buffer[i].x % b.buffer[i].x;            \
		result.buffer[i].y = a.buffer[i].y % b.buffer[i].y;            \
	}                                                                          \
	return result;
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
#if defined(VMATH_AVX2_ENABLE)
	return _mm512_div_ps(a, b);
#else
	vm_8batch_v2f_t result;
#pragma unroll
	for (int8_t i = 0; i < 4; ++i) {
		result.buffer[i] = _mm_div_ps(a.buffer[i], b.buffer[i]);
	}
	return result;
#endif
#else
	VMATH_DIV_8XV2_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_DIV_8XV2_SCALAR()
#endif
#undef VMATH_DIV_8XV2_SCALAR
}
