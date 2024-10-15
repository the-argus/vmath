#ifndef __VMATH_DECL_SCALAR_MATH_H
#define __VMATH_DECL_SCALAR_MATH_H

#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"

VMATH_INLINE_DECL vm_float32_t vm_sin(vm_float32_t theta);
VMATH_INLINE_DECL vm_float32_t vm_cos(vm_float32_t theta);
VMATH_INLINE_DECL vm_float32_t vm_sin_est(vm_float32_t theta);
VMATH_INLINE_DECL vm_float32_t vm_cos_est(vm_float32_t theta);
VMATH_INLINE_DECL vm_float32_t vm_arcsin(vm_float32_t value);
VMATH_INLINE_DECL vm_float32_t vm_arccos(vm_float32_t value);
VMATH_INLINE_DECL vm_float32_t vm_arcsin_est(vm_float32_t value);
VMATH_INLINE_DECL vm_float32_t vm_arccos_est(vm_float32_t value);

VMATH_INLINE_DECL void vm_sin_cos(float* out_sin, float* out_cos, float theta);
VMATH_INLINE_DECL void vm_sin_cos_est(float* out_sin, float* out_cos,
									  float theta);

#endif
