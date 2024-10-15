/*
 * Scalar implementations of some math functions, namely trig ones.
 * Implementations are ripped straight from DirectX math
 */
#ifndef __VMATH_SCALAR_MATH_H
#define __VMATH_SCALAR_MATH_H

#include "vmath/decl/constants.h"
#include "vmath/decl/scalar.h"

VMATH_INLINE_DECL vm_float32_t vm_sin(vm_float32_t theta)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	vm_float32_t quotient = VMATH_1DIV2PI * theta;
	if (theta >= 0.0F) {
		quotient = (vm_float32_t)((int32_t)(quotient + 0.5F));
	} else {
		quotient = (vm_float32_t)((int32_t)(quotient - 0.5F));
	}

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	vm_float32_t y = theta - VMATH_2PI * quotient;
	if (y > VMATH_PIDIV2) {
		y = VMATH_PI - y;
	} else if (y < -VMATH_PIDIV2) {
		y = -VMATH_PI - y;
	}

	// 11-degree minimax approximation
	const vm_float32_t y2 = y * y;
	// clang-format off
    return (((((-2.3889859e-08F * y2 + 2.7525562e-06F) * y2 - 0.00019840874F) * y2 + 0.0083333310F) * y2 - 0.16666667F) * y2 + 1.0F) * y;
	// clang-format on
}

VMATH_INLINE_DECL vm_float32_t vm_cos(vm_float32_t theta)
{
	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	vm_float32_t quotient = VMATH_1DIV2PI * theta;
	if (theta >= 0.0F) {
		quotient = (float)((int)(quotient + 0.5F));
	} else {
		quotient = (float)((int)(quotient - 0.5F));
	}
	vm_float32_t y = theta - VMATH_2PI * quotient;

	// Map y to [-pi/2,pi/2] with cos(y) = sign*cos(x).
	vm_float32_t sign;
	if (y > VMATH_PIDIV2) {
		y = VMATH_PI - y;
		sign = -1.0F;
	} else if (y < -VMATH_PIDIV2) {
		y = -VMATH_PI - y;
		sign = -1.0F;
	} else {
		sign = +1.0F;
	}

	// 10-degree minimax approximation
	vm_float32_t y2 = y * y;
	// clang-format off
    vm_float32_t p = ((((-2.6051615e-07F * y2 + 2.4760495e-05F) * y2 - 0.0013888378F) * y2 + 0.041666638F) * y2 - 0.5F) * y2 + 1.0F;
	// clang-format on
	return sign * p;
}

VMATH_INLINE_DECL vm_float32_t vm_sin_est(vm_float32_t theta);

VMATH_INLINE_DECL vm_float32_t vm_cos_est(vm_float32_t theta);

VMATH_INLINE_DECL vm_float32_t vm_arcsin(vm_float32_t theta);

VMATH_INLINE_DECL vm_float32_t vm_arccos(vm_float32_t theta);

VMATH_INLINE_DECL vm_float32_t vm_arcsin_est(vm_float32_t theta);

VMATH_INLINE_DECL vm_float32_t vm_arccos_est(vm_float32_t theta);

VMATH_INLINE_DECL void vm_sin_cos(float* out_sin, float* out_cos, float theta);

VMATH_INLINE_DECL void vm_sin_cos_est(float* out_sin, float* out_cos,
									  float theta);

#endif
