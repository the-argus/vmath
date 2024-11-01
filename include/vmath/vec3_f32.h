/*
 * Implementation file for vec3 operations. See vmath/decl/vec3_f32.h for type
 * and function declarations.
 */
#ifndef __VMATH_VEC3_F32_H
#define __VMATH_VEC3_F32_H

#include "vmath/decl/vec3_f32.h"
#include "vmath/scalar.h"
#include <assert.h>

VMATH_INLINE vm_v3f_t vm_load_v3f(const vm_v3fs_t* vec)
{
	assert(vec);
#if defined(VMATH_SSE41_ENABLE)
	__m128 xy = _mm_castpd_ps(_mm_load_sd((const double*)vec));
	__m128 z = _mm_load_ss(&vec->z);
	return _mm_insert_ps(xy, z, 0x20);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3f_t output;
	output._inner.x = vec->x;
	output._inner.y = vec->y;
	output._inner.z = vec->z;
	return output;
#endif
}

VMATH_INLINE vm_v3f_t vm_loadb_v3f(const vm_float32_t vec[3])
{
	assert(vec);
	assert(sizeof(vm_float32_t[3]) == sizeof(vm_v3fs_t));
	return vm_load_v3f((const vm_v3fs_t*)vec);
}

VMATH_INLINE void vm_store_v3f(vm_v3fs_t* output, vm_v3f_t vector)
{
	assert(output);
#if defined(VMATH_SSE41_ENABLE)
	*(int*)&output->x = _mm_extract_ps(vector, 0);
	*(int*)&output->y = _mm_extract_ps(vector, 1);
	*(int*)&output->z = _mm_extract_ps(vector, 2);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	output->x = vector._inner.x;
	output->y = vector._inner.y;
	output->z = vector._inner.z;
#endif
}

VMATH_INLINE void vm_storeb_v3f(vm_float32_t output[3], vm_v3f_t vector)
{
	assert(output);
	assert(sizeof(vm_float32_t[3]) == sizeof(vm_v3fs_t));
	vm_store_v3f((vm_v3fs_t*)output, vector);
}

VMATH_INLINE vm_v3f_t vm_splat_v3f(vm_float32_t fill)
{
#if defined(VMATH_SSE41_ENABLE)
	return _mm_set_ps(0, fill, fill, fill);
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3f_t output;
	output._inner.x = fill;
	output._inner.y = fill;
	output._inner.z = fill;
	return output;
#endif
}

VMATH_INLINE vm_v3f_t vm_shave4_v3f(vm_v4f_t vec)
{
#if defined(VMATH_SSE41_ENABLE)
	return vec;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3f_t output;
	output._inner.x = vec._inner.x;
	output._inner.y = vec._inner.y;
	output._inner.z = vec._inner.z;
	return output;
#endif
}

VMATH_INLINE_DECL vm_v3f_t vm_mod_pi_v3f(vm_v3f_t angles)
{
#if defined(VMATH_SSE41_ENABLE)
    vm_v4f_t mod = _mm_mul_ps(angles, vm_v4_2pi_inverse.vector_rep);
    mod = XMVectorRound(vResult);
    return VMATH_FNMADD_PS(mod, vm_v4_2pi.vector_rep, angles);
	return vec;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_v3f_t output;
	output._inner.x = vec._inner.x;
	output._inner.y = vec._inner.y;
	output._inner.z = vec._inner.z;
	return output;
#endif

#if defined(_XM_NO_INTRINSICS_)

    XMVECTOR V;
    XMVECTOR Result;

    // Modulo the range of the given angles such that -XM_PI <= Angles < XM_PI
    V = XMVectorMultiply(Angles, g_XMReciprocalTwoPi.v);
    V = XMVectorRound(V);
    Result = XMVectorNegativeMultiplySubtract(g_XMTwoPi.v, V, Angles);
    return Result;

#elif defined(_XM_ARM_NEON_INTRINSICS_)
    // Modulo the range of the given angles such that -XM_PI <= Angles < XM_PI
    XMVECTOR vResult = vmulq_f32(Angles, g_XMReciprocalTwoPi);
    // Use the inline function due to complexity for rounding
    vResult = XMVectorRound(vResult);
    return vmlsq_f32(Angles, vResult, g_XMTwoPi);
#elif defined(_XM_SSE_INTRINSICS_)
#endif
}

VMATH_INLINE void vm_sin_cos_v3f(vm_v3f_t* out_sin, vm_v3f_t* out_cos,
								 vm_v3f_t angles)
{
	assert(out_sin != NULL);
	assert(out_cos != NULL);

#if defined(VMATH_SSE41_ENABLE)
	// Force the value within the bounds of pi
	XMVECTOR x = XMVectorModAngles(V);

	// Map in [-pi/2,pi/2] with sin(y) = sin(x), cos(y) = sign*cos(x).
	XMVECTOR sign = _mm_and_ps(x, g_XMNegativeZero);
	__m128 c = _mm_or_ps(g_XMPi, sign);	  // pi when x >= 0, -pi when x < 0
	__m128 absx = _mm_andnot_ps(sign, x); // |x|
	__m128 rflx = _mm_sub_ps(c, x);
	__m128 comp = _mm_cmple_ps(absx, g_XMHalfPi);
	__m128 select0 = _mm_and_ps(comp, x);
	__m128 select1 = _mm_andnot_ps(comp, rflx);
	x = _mm_or_ps(select0, select1);
	select0 = _mm_and_ps(comp, g_XMOne);
	select1 = _mm_andnot_ps(comp, g_XMNegativeOne);
	sign = _mm_or_ps(select0, select1);

	__m128 x2 = _mm_mul_ps(x, x);

	// Compute polynomial approximation of sine
	const XMVECTOR SC1 = g_XMSinCoefficients1;
	__m128 vConstantsB = XM_PERMUTE_PS(SC1, _MM_SHUFFLE(0, 0, 0, 0));
	const XMVECTOR SC0 = g_XMSinCoefficients0;
	__m128 vConstants = XM_PERMUTE_PS(SC0, _MM_SHUFFLE(3, 3, 3, 3));
	__m128 Result = XM_FMADD_PS(vConstantsB, x2, vConstants);

	vConstants = XM_PERMUTE_PS(SC0, _MM_SHUFFLE(2, 2, 2, 2));
	Result = XM_FMADD_PS(Result, x2, vConstants);

	vConstants = XM_PERMUTE_PS(SC0, _MM_SHUFFLE(1, 1, 1, 1));
	Result = XM_FMADD_PS(Result, x2, vConstants);

	vConstants = XM_PERMUTE_PS(SC0, _MM_SHUFFLE(0, 0, 0, 0));
	Result = XM_FMADD_PS(Result, x2, vConstants);

	Result = XM_FMADD_PS(Result, x2, g_XMOne);
	Result = _mm_mul_ps(Result, x);
	*pSin = Result;

	// Compute polynomial approximation of cosine
	const XMVECTOR CC1 = g_XMCosCoefficients1;
	vConstantsB = XM_PERMUTE_PS(CC1, _MM_SHUFFLE(0, 0, 0, 0));
	const XMVECTOR CC0 = g_XMCosCoefficients0;
	vConstants = XM_PERMUTE_PS(CC0, _MM_SHUFFLE(3, 3, 3, 3));
	Result = XM_FMADD_PS(vConstantsB, x2, vConstants);

	vConstants = XM_PERMUTE_PS(CC0, _MM_SHUFFLE(2, 2, 2, 2));
	Result = XM_FMADD_PS(Result, x2, vConstants);

	vConstants = XM_PERMUTE_PS(CC0, _MM_SHUFFLE(1, 1, 1, 1));
	Result = XM_FMADD_PS(Result, x2, vConstants);

	vConstants = XM_PERMUTE_PS(CC0, _MM_SHUFFLE(0, 0, 0, 0));
	Result = XM_FMADD_PS(Result, x2, vConstants);

	Result = XM_FMADD_PS(Result, x2, g_XMOne);
	Result = _mm_mul_ps(Result, sign);
	*pCos = Result;
#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else
	vm_sin_cos(&out_sin->_inner.x, &out_cos->_inner.x, angles._inner.x);
	vm_sin_cos(&out_sin->_inner.y, &out_cos->_inner.y, angles._inner.y);
	vm_sin_cos(&out_sin->_inner.z, &out_cos->_inner.z, angles._inner.z);
#endif
}

#include "vmath/generated/v3f/v3f_componentwise_add.h"
#include "vmath/generated/v3f/v3f_componentwise_div.h"
#include "vmath/generated/v3f/v3f_componentwise_mul.h"
#include "vmath/generated/v3f/v3f_componentwise_sub.h"

#include "vmath/generated/v3f/v3f_componentwise_constant_add.h"
#include "vmath/generated/v3f/v3f_componentwise_constant_div.h"
#include "vmath/generated/v3f/v3f_componentwise_constant_mul.h"
#include "vmath/generated/v3f/v3f_componentwise_constant_sub.h"

#endif
