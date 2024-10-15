/*
 * Implementation of the vmath library. The lib is entirely inline, so these are
 * just extern inline definitions to prevent ODR violation
 */
#define VMATH_USE_EXTERN_INLINE
#include "vmath/decl/mat3x3_f32.h"
#include "vmath/decl/mat4x4_f32.h"
#include "vmath/decl/transform2d_f32.h"
#include "vmath/decl/vec16_f32.h"
#include "vmath/decl/vec2_f32.h"
#include "vmath/decl/vec3_f32.h"
#include "vmath/decl/vec4_f32.h"
#include "vmath/decl/vec8_f32.h"

#include "vmath/decl/constants.h"

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

const vm_floatinit_v4f vm_v4_zeroes = {{0.F, 0.F, 0.F, 0.F}};
const vm_floatinit_v4f vm_v4_ones = {{1.F, 1.F, 1.F, 1.F}};

const vm_floatinit_v4f vm_mat4x4_iden_row0 = {{1.0F, 0.0F, 0.0F, 0.0F}};
const vm_floatinit_v4f vm_mat4x4_iden_row1 = {{0.0F, 1.0F, 0.0F, 0.0F}};
const vm_floatinit_v4f vm_mat4x4_iden_row2 = {{0.0F, 0.0F, 1.0F, 0.0F}};
const vm_floatinit_v4f vm_mat4x4_iden_row3 = {{0.0F, 0.0F, 0.0F, 1.0F}};

const vm_floatinit_v4f vm_negate_x = {{-1.F, 1.F, 1.F, 1.F}};
const vm_floatinit_v4f vm_negate_y = {{1.F, -1.F, 1.F, 1.F}};
const vm_floatinit_v4f vm_negate_z = {{1.F, 1.F, -1.F, 1.F}};
const vm_floatinit_v4f vm_negate_w = {{1.F, 1.F, 1.F, -1.F}};

const vm_floatinit_v8f vm_mat4x4_iden_rows_0_and_1 = {
	{1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F}};
const vm_floatinit_v8f vm_mat4x4_iden_rows_2_and_3 = {
	{0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F}};

// clang-format off
const vm_floatinit_v16f vm_mat4x4_iden = {{
    1.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 1.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 1.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 1.0F
}};
// clang-format on
