/*
 * Implementation of the vmath library. The lib is entirely inline, so these are
 * just extern inline definitions to prevent ODR violation
 */
#define VMATH_USE_EXTERN_INLINE
#include "vmath/decl/vec16_f32.h"
#include "vmath/decl/vec2_f32.h"
#include "vmath/decl/vec4_f32.h"
#include "vmath/decl/vec8_f32.h"

#include "vmath/client_query.h"

vm_feature_flags vm_get_features(void)
{
	vm_feature_flags out = VM_FEATURE_SCALAR;
#if defined(VMATH_AVX512_GENERIC_ENABLE)
	out &= (unsigned long)VM_FEATURE_AVX512;
#endif
#if defined(VMATH_AVX256_GENERIC_ENABLE)
	out &= (unsigned long)VM_FEATURE_AVX;
#endif
#if defined(VMATH_SSE41_ENABLE)
	out &= (unsigned long)VM_FEATURE_SSE41;
#endif
#if defined(VMATH_RISCV_V1_ENABLE)
	out &= (unsigned long)VM_FEATURE_RISCV_V1;
#endif
#if defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
	out &= (unsigned long)VM_FEATURE_ARM_NEON;
#endif
	return out;
}

const char* vm_get_feature_string(void)
{
#if defined(VMATH_AVX512_GENERIC_ENABLE)
	return "x86 AVX512";
#elif defined(VMATH_AVX256_GENERIC_ENABLE)
	return "x86 AVX2";
#elif defined(VMATH_SSE41_ENABLE)
	return "x86 SSE41";
#elif defined(VMATH_RISCV_V1_ENABLE)
	return "RISCV-V V1";
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
	return "Arm Neon";
#else
	return "None / Scalar Fallback";
#endif
}
