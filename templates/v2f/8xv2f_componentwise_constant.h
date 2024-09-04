#include "vmath/decl/vec2_f32.h"

VMATH_INLINE vm_8batch_v2f_t vm_add_8xv2f_constant(const vm_8batch_v2f_t a,
												   const float b)
{
#define VMATH_ADD_8XV2_CONSTANT_SCALAR()                                       \
	vm_8batch_v2f_t result;                                                    \
	result.buffer[0].x = a.buffer[0].x SCALAR_OP b;                            \
	result.buffer[0].y = a.buffer[0].y SCALAR_OP b;                            \
	result.buffer[1].x = a.buffer[1].x SCALAR_OP b;                            \
	result.buffer[1].y = a.buffer[1].y SCALAR_OP b;                            \
	result.buffer[2].x = a.buffer[2].x SCALAR_OP b;                            \
	result.buffer[2].y = a.buffer[2].y SCALAR_OP b;                            \
	result.buffer[3].x = a.buffer[3].x SCALAR_OP b;                            \
	result.buffer[3].y = a.buffer[3].y SCALAR_OP b;                            \
	result.buffer[4].x = a.buffer[4].x SCALAR_OP b;                            \
	result.buffer[4].y = a.buffer[4].y SCALAR_OP b;                            \
	result.buffer[5].x = a.buffer[5].x SCALAR_OP b;                            \
	result.buffer[5].y = a.buffer[5].y SCALAR_OP b;                            \
	result.buffer[6].x = a.buffer[6].x SCALAR_OP b;                            \
	result.buffer[6].y = a.buffer[6].y SCALAR_OP b;                            \
	result.buffer[7].x = a.buffer[7].x SCALAR_OP b;                            \
	result.buffer[7].y = a.buffer[7].y SCALAR_OP b;                            \
	return result;
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
#if defined(VMATH_AVX512_GENERIC_ENABLE)
	return _mm512_add_ps(a, vm_splat_8xv2f(b));
#else
	vm_8batch_v2f_t result;
	const vm_2batch_v2f_t constants = vm_splat_2xv2f(b);
#pragma unroll
	for (int8_t i = 0; i < 4; ++i) {
		result.buffer[i] = _mm_add_ps(a.buffer[i], constants);
	}
	return result;
#endif
#else
	VMATH_ADD_8XV2_CONSTANT_SCALAR()
#endif // defined(VMATH_SSE41_ENABLE)
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
	VMATH_ADD_8XV2_CONSTANT_SCALAR()
#endif
#undef VMATH_ADD_8XV2_CONSTANT_SCALAR
}
