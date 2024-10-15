#ifndef __VMATH_GLOBAL_CONSTANTS_H
#define __VMATH_GLOBAL_CONSTANTS_H

#include "vmath/decl/vec16_f32.h"
#include "vmath/decl/vec4_f32.h"
#include "vmath/decl/vec8_f32.h"
#include "vmath/internal/stdint.h"

/// Union with simd vector type to enable array initialization.
union vm_floatinit_v4f
{
	vm_float32_t float_rep[4];
	vm_v4f_t vector_rep;
};
typedef union vm_floatinit_v4f vm_floatinit_v4f;

union vm_floatinit_v8f
{
	vm_float32_t float_rep[8];
	vm_v8f_t vector_rep;
};
typedef union vm_floatinit_v8f vm_floatinit_v8f;

union vm_floatinit_v16f
{
	vm_float32_t float_rep[16];
	vm_v16f_t vector_rep;
};
typedef union vm_floatinit_v16f vm_floatinit_v16f;

union vm_intinit_v4f
{
	int32_t int_rep[4];
	vm_v4f_t vector_rep;
};
typedef union vm_intinit_v4f vm_intinit_v4f;

union vm_uintinit_v4f
{
	uint32_t uint_rep[4];
	vm_v4f_t vector_rep;
};
typedef union vm_uintinit_v4f vm_uintinit_v4f;

#define VMATH_PI (3.141592654F)
#define VMATH_2PI (6.283185307F)
#define VMATH_1DIVPI (0.318309886F)
#define VMATH_1DIV2PI (0.159154943F)
#define VMATH_PIDIV2 (1.570796327F)
#define VMATH_PIDIV4 (0.785398163F)

#define VMATH_EXTERN_CONST extern const

VMATH_EXTERN_CONST vm_floatinit_v4f vm_v4_zeroes;
VMATH_EXTERN_CONST vm_floatinit_v4f vm_v4_ones;

VMATH_EXTERN_CONST vm_floatinit_v4f vm_mat4x4_iden_row1;
VMATH_EXTERN_CONST vm_floatinit_v4f vm_mat4x4_iden_row2;
VMATH_EXTERN_CONST vm_floatinit_v4f vm_mat4x4_iden_row3;
VMATH_EXTERN_CONST vm_floatinit_v4f vm_mat4x4_iden_row4;

VMATH_EXTERN_CONST vm_floatinit_v8f vm_mat4x4_iden_rows_1_and_2;
VMATH_EXTERN_CONST vm_floatinit_v8f vm_mat4x4_iden_rows_3_and_4;

VMATH_EXTERN_CONST vm_floatinit_v16f vm_mat4x4_iden;

#undef VMATH_EXTERN_CONST

#endif
