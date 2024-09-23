/*
 * Header which defines functions related to querying information about the
 * running program: runtime known cpu features, compiled features, etc
 */
#ifndef __VMATH_CLIENT_QUERY_H
#define __VMATH_CLIENT_QUERY_H

typedef enum
{
	VM_FEATURE_SCALAR = 0x0,
	VM_FEATURE_SSE41 = 0x1,
	VM_FEATURE_AVX = 0x2,
	VM_FEATURE_AVX512 = 0x4,
	VM_FEATURE_ARM_NEON = 0x8,
	VM_FEATURE_RISCV_V1 = 0x10,
} vm_feature_flags;

vm_feature_flags vm_get_features(void);

/// Get a string describing the feature which grants the current largest
/// available simd register size. on arm, this is always "Arm Neon". On x86 with
/// AVX2 but not AVX512, this will return "x86 AVX2".
const char* vm_get_feature_string(void);

#endif
