#ifndef __VMATH_DECL_VEC8_F32_H
#define __VMATH_DECL_VEC8_F32_H

#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"

typedef struct
{
	vm_float32_t buffer[8];
} vm_v8fs_t;

#if defined(VMATH_AVX256_GENERIC_ENABLE)

typedef __m256 vm_v8f_t;

#elif defined(VMATH_SSE41_ENABLE)

typedef struct
{
	__m128 buffer[2];
} vm_v8f_t;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

typedef struct
{
	vm_float32_t buffer[8];
} vm_v8f_t;

#endif

/// Load 8 contiguous float32s from memory.
VMATH_INLINE_DECL vm_v8f_t vm_load_v8f(const vm_v8fs_t* vec);
/// Load 8 contiguous float32s from memory, float buffer instead of vector type.
VMATH_INLINE_DECL vm_v8f_t vm_loadb_v8f(const vm_float32_t vec[8]);
/// Store 8 contiguous float32s to memory.
VMATH_INLINE_DECL void vm_store_v8f(vm_v8fs_t* output, vm_v8f_t vec);
/// Store 8 contiguous float32s to memory, directly to a float buffer.
VMATH_INLINE_DECL void vm_storeb_v8f(vm_float32_t output[8], vm_v8f_t vec);

/// Load a float32 into all elements of a vec8
VMATH_INLINE_DECL vm_v8f_t vm_splat_v8f(vm_float32_t fill);

/// Add two four-element vectors together, componentwise
VMATH_INLINE_DECL vm_v8f_t vm_add_v8f(vm_v8f_t a, vm_v8f_t b);
/// Subtract a four-element vectors from another, componentwise
VMATH_INLINE_DECL vm_v8f_t vm_sub_v8f(vm_v8f_t a, vm_v8f_t b);
/// Multiply two four-element vectors together, componentwise
VMATH_INLINE_DECL vm_v8f_t vm_mul_v8f(vm_v8f_t a, vm_v8f_t b);
/// Divide a four-element vectors by another, componentwise
VMATH_INLINE_DECL vm_v8f_t vm_div_v8f(vm_v8f_t a, vm_v8f_t b);

/// Add a constant float32 value to all the elements of an 8 element vector
VMATH_INLINE_DECL vm_v8f_t vm_addc_v8f(vm_v8f_t a, vm_float32_t b);
/// Subtract a constant float32 value from all the elements of an 8 element
/// vector
VMATH_INLINE_DECL vm_v8f_t vm_subc_v8f(vm_v8f_t a, vm_float32_t b);
/// Multiply all the elements of an 8 element vector by a constant float32 value
VMATH_INLINE_DECL vm_v8f_t vm_mulc_v8f(vm_v8f_t a, vm_float32_t b);
/// Divide all the elements of an 8 element vector by a constant float32 value
VMATH_INLINE_DECL vm_v8f_t vm_divc_v8f(vm_v8f_t a, vm_float32_t b);

#endif
