/*
 * Scalar implementations of some math functions, namely trig ones.
 * Implementations are ripped straight from DirectX math
 */
#ifndef __VMATH_SCALAR_MATH_H
#define __VMATH_SCALAR_MATH_H

#include "vmath/decl/constants.h"
#include "vmath/decl/scalar.h"
#include <assert.h>
#include <math.h>

VMATH_INLINE vm_float32_t vm_sin(const vm_float32_t theta)
{
	// Map theta to y in [-pi,pi], x = 2*pi*quotient + remainder.
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

VMATH_INLINE vm_float32_t vm_cos(const vm_float32_t theta)
{
	// Map theta to y in [-pi,pi], x = 2*pi*quotient + remainder.
	vm_float32_t quotient = VMATH_1DIV2PI * theta;
	if (theta >= 0.0F) {
		quotient = (vm_float32_t)((int32_t)(quotient + 0.5F));
	} else {
		quotient = (vm_float32_t)((int32_t)(quotient - 0.5F));
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
	const vm_float32_t y2 = y * y;
	// clang-format off
    const vm_float32_t p = ((((-2.6051615e-07F * y2 + 2.4760495e-05F) * y2 - 0.0013888378F) * y2 + 0.041666638F) * y2 - 0.5F) * y2 + 1.0F;
	// clang-format on
	return sign * p;
}

VMATH_INLINE vm_float32_t vm_sin_est(const vm_float32_t theta)
{
	// Map theta to y in [-pi,pi], x = 2*pi*quotient + remainder.
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

	// 7-degree minimax approximation
	const vm_float32_t y2 = y * y;
	// clang-format off
    return (((-0.00018524670F * y2 + 0.0083139502F) * y2 - 0.16665852F) * y2 + 1.0F) * y;
	// clang-format on
}

VMATH_INLINE vm_float32_t vm_cos_est(const vm_float32_t theta)
{
	// Map theta to y in [-pi,pi], x = 2*pi*quotient + remainder.
	vm_float32_t quotient = VMATH_1DIV2PI * theta;
	if (theta >= 0.0F) {
		quotient = (vm_float32_t)((int32_t)(quotient + 0.5F));
	} else {
		quotient = (vm_float32_t)((int32_t)(quotient - 0.5F));
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

	// 6-degree minimax approximation
	const vm_float32_t y2 = y * y;
	// clang-format off
    const vm_float32_t p = ((-0.0012712436F * y2 + 0.041493919F) * y2 - 0.49992746F) * y2 + 1.0F;
	// clang-format on
	return sign * p;
}

VMATH_INLINE vm_float32_t vm_arcsin(const vm_float32_t value)
{
	// Clamp input to [-1,1].
	const vm_float32_t x = fabsf(value);
	vm_float32_t omx = 1.0F - x;
	if (omx < 0.0F) {
		omx = 0.0F;
	}
	const vm_float32_t root = sqrtf(omx);

	// 7-degree minimax approximation
	// clang-format off
    vm_float32_t result = ((((((-0.0012624911F * x + 0.0066700901F) * x - 0.0170881256F) * x + 0.0308918810F) * x - 0.0501743046F) * x + 0.0889789874F) * x - 0.2145988016F) * x + 1.5707963050F;
	// clang-format on
	result *= root; // acos(|x|)

	// acos(x) = pi - acos(-x) when x < 0, asin(x) = pi/2 - acos(x)
	return (value >= 0.0F ? VMATH_PIDIV2 - result : result - VMATH_PIDIV2);
}

VMATH_INLINE vm_float32_t vm_arccos(vm_float32_t value)
{
	// Clamp input to [-1,1].
	const vm_float32_t x = fabsf(value);
	vm_float32_t omx = 1.0F - x;
	if (omx < 0.0F) {
		omx = 0.0F;
	}
	const vm_float32_t root = sqrtf(omx);

	// 7-degree minimax approximation
	// clang-format off
    float result = ((((((-0.0012624911F * x + 0.0066700901F) * x - 0.0170881256F) * x + 0.0308918810F) * x - 0.0501743046F) * x + 0.0889789874F) * x - 0.2145988016F) * x + 1.5707963050F;
	// clang-format on
	result *= root;

	// acos(x) = pi - acos(-x) when x < 0
	return (value >= 0.0F ? result : VMATH_PI - result);
}

VMATH_INLINE vm_float32_t vm_arcsin_est(vm_float32_t value)
{
	// Clamp input to [-1,1].
	const vm_float32_t x = fabsf(value);
	vm_float32_t omx = 1.0F - x;
	if (omx < 0.0F) {
		omx = 0.0F;
	}
	const vm_float32_t root = sqrtf(omx);

	// 3-degree minimax approximation
	// clang-format off
    vm_float32_t result = ((-0.0187293F * x + 0.0742610F) * x - 0.2121144F) * x + 1.5707288F;
	// clang-format on
	result *= root; // acos(|x|)

	// acos(x) = pi - acos(-x) when x < 0, asin(x) = pi/2 - acos(x)
	return (value >= 0.0F ? VMATH_PIDIV2 - result : result - VMATH_PIDIV2);
}

VMATH_INLINE vm_float32_t vm_arccos_est(vm_float32_t value)
{
	// Clamp input to [-1,1].
	const vm_float32_t x = fabsf(value);
	vm_float32_t omx = 1.0F - x;
	if (omx < 0.0F) {
		omx = 0.0F;
	}
	const vm_float32_t root = sqrtf(omx);

	// 3-degree minimax approximation
	// clang-format off
    vm_float32_t result = ((-0.0187293F * x + 0.0742610F) * x - 0.2121144F) * x + 1.5707288F;
	// clang-format on
	result *= root;

	// acos(x) = pi - acos(-x) when x < 0
	return (value >= 0.0F ? result : VMATH_PI - result);
}

VMATH_INLINE void vm_sin_cos(vm_float32_t* const out_sin,
							 vm_float32_t* const out_cos,
							 const vm_float32_t theta)
{
	assert(out_sin);
	assert(out_cos);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	vm_float32_t quotient = VMATH_1DIV2PI * theta;
	if (theta >= 0.0F) {
		quotient = (vm_float32_t)((int32_t)(quotient + 0.5F));
	} else {
		quotient = (vm_float32_t)((int32_t)(quotient - 0.5F));
	}
	vm_float32_t y = theta - VMATH_2PI * quotient;

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
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

	const vm_float32_t y2 = y * y;

	// 11-degree minimax approximation
	// clang-format off
    *out_sin = (((((-2.3889859e-08F * y2 + 2.7525562e-06F) * y2 - 0.00019840874F) * y2 + 0.0083333310F) * y2 - 0.16666667F) * y2 + 1.0F) * y;
	// clang-format on

	// 10-degree minimax approximation
	// clang-format off
    const vm_float32_t p = ((((-2.6051615e-07F * y2 + 2.4760495e-05F) * y2 - 0.0013888378F) * y2 + 0.041666638F) * y2 - 0.5F) * y2 + 1.0F;
	// clang-format on
	*out_cos = sign * p;
}

VMATH_INLINE void vm_sin_cos_est(vm_float32_t* const out_sin,
								 vm_float32_t* const out_cos,
								 vm_float32_t theta)
{
	assert(out_sin);
	assert(out_cos);

	// Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
	vm_float32_t quotient = VMATH_1DIV2PI * theta;
	if (theta >= 0.0F) {
		quotient = (vm_float32_t)((int32_t)(quotient + 0.5F));
	} else {
		quotient = (vm_float32_t)((int32_t)(quotient - 0.5F));
	}

	// Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
	vm_float32_t y = theta - VMATH_2PI * quotient;
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

	vm_float32_t y2 = y * y;

	// 7-degree minimax approximation
	// clang-format off
    *out_sin = (((-0.00018524670F * y2 + 0.0083139502F) * y2 - 0.16665852F) * y2 + 1.0F) * y;
	// clang-format on

	// 6-degree minimax approximation
	// clang-format off
    const vm_float32_t p = ((-0.0012712436F * y2 + 0.041493919F) * y2 - 0.49992746F) * y2 + 1.0F;
	// clang-format on
	*out_cos = sign * p;
}

#endif
