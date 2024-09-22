#include "vmath/decl/vec4_f32.h"

VMATH_INLINE vm_v4f_t vm_add_v4f(const vm_v4f_t a, const vm_v4f_t b)
{
#define VMATH_ADD_V4_SCALAR()                                                  \
	vm_v4f_t result;                                                           \
	result.buffer[0] = a.buffer[0] SCALAR_OP b.buffer[0];                      \
	result.buffer[1] = a.buffer[1] SCALAR_OP b.buffer[1];                      \
	result.buffer[2] = a.buffer[2] SCALAR_OP b.buffer[2];                      \
	result.buffer[3] = a.buffer[3] SCALAR_OP b.buffer[3];                      \
	return result;

#if defined(VMATH_X64_ENABLE)

#if defined(VMATH_SSE41_ENABLE)
	return _mm_add_ps(a, b);
#else
	VMATH_ADD_V4_SCALAR()
#endif

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	VMATH_ADD_V4_SCALAR()
#endif
#undef VMATH_ADD_V4_SCALAR
}
