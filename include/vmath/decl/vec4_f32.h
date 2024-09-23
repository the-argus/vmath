#ifndef __VMATH_DECL_VEC4_F32_H
#define __VMATH_DECL_VEC4_F32_H

#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"

typedef struct VMATH_ALIGNED(16)
{
	vm_float32_t x;
	vm_float32_t y;
	vm_float32_t z;
	vm_float32_t w;
} vm_v4fs_t;

#if defined(VMATH_SSE41_ENABLE)

typedef __m128 vm_v4f_t;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

/*
 * Scalar fallback. 32 bit machine or something
 */
typedef struct VMATH_ALIGNED(16)
{
	vm_float32_t buffer[4];
} vm_v4f_t;

#endif

/// Load 4 contiguous float32s from memory. Memory must be 16-byte aligned.
VMATH_INLINE_DECL vm_v4f_t vm_load_v4f(const vm_v4fs_t* vec);
/// Load 4 contiguous float32s from memory, float buffer instead of vector type.
/// Memory must be 16-byte aligned.
VMATH_INLINE_DECL vm_v4f_t vm_loadb_v4f(const vm_float32_t vec[4]);
/// Store 4 contiguous float32s to memory.
/// Memory must be 16-byte aligned.
VMATH_INLINE_DECL void vm_store_v4f(vm_v4fs_t* output, vm_v4f_t vec);
/// Store 4 contiguous float32s to memory, directly to a float buffer.
/// Memory must be 16-byte aligned.
VMATH_INLINE_DECL void vm_storeb_v4f(vm_float32_t output[4], vm_v4f_t vec);

/// Load a float32 into all elements of a vec4
VMATH_INLINE_DECL vm_v4f_t vm_splat_v4f(vm_float32_t fill);

/// Add two four-element vectors together, componentwise
VMATH_INLINE_DECL vm_v4f_t vm_add_v4f(vm_v4f_t a, vm_v4f_t b);
/// Subtract a four-element vectors from another, componentwise
VMATH_INLINE_DECL vm_v4f_t vm_sub_v4f(vm_v4f_t a, vm_v4f_t b);
/// Multiply two four-element vectors together, componentwise
VMATH_INLINE_DECL vm_v4f_t vm_mul_v4f(vm_v4f_t a, vm_v4f_t b);
/// Divide a four-element vectors by another, componentwise
VMATH_INLINE_DECL vm_v4f_t vm_div_v4f(vm_v4f_t a, vm_v4f_t b);

/// Add a constant float32 value to all the elements of a 4 element vector
VMATH_INLINE_DECL vm_v4f_t vm_addc_v4f(vm_v4f_t a, vm_float32_t b);
/// Subtract a constant float32 value from all the elements of a 4 element
/// vector
VMATH_INLINE_DECL vm_v4f_t vm_subc_v4f(vm_v4f_t a, vm_float32_t b);
/// Multiply all the elements of a 4 element vector by a constant float32 value
VMATH_INLINE_DECL vm_v4f_t vm_mulc_v4f(vm_v4f_t a, vm_float32_t b);
/// Divide all the elements of a 4 element vector by a constant float32 value
VMATH_INLINE_DECL vm_v4f_t vm_divc_v4f(vm_v4f_t a, vm_float32_t b);

#endif
