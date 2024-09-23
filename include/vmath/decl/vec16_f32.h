#ifndef __VMATH_DECL_VEC16_F32_H
#define __VMATH_DECL_VEC16_F32_H

#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"

typedef struct VMATH_ALIGNED(64)
{
	vm_float32_t buffer[16];
} vm_v16fs_t;

#if defined(VMATH_AVX512_GENERIC_ENABLE)

typedef __m512 vm_v16f_t;

#elif defined(VMATH_AVX256_GENERIC_ENABLE)

// emulate 512 bits with 2x256
typedef struct VMATH_ALIGNED(64)
{
	__m256 buffer[2];
} vm_v16f_t;

#elif defined(VMATH_SSE41_ENABLE)

// emulate 512 bits with 4x128
typedef struct VMATH_ALIGNED(64)
{
	__m128 buffer[4];
} vm_v16f_t;

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
#error RISCV vector extensions not implemented
#else

typedef struct
{
	vm_float32_t buffer[16];
} vm_v16f_t;

#endif

/// Load 16 contiguous floats from memory. Memory must be 64 byte aligned.
VMATH_INLINE_DECL vm_v16f_t vm_load_v16f(const vm_v16fs_t* vec);
/// Load 16 contiguous floats from memory as a buffer of floats. Memory must be
/// 64 byte aligned.
VMATH_INLINE_DECL vm_v16f_t vm_loadb_v16f(const vm_float32_t vec[16]);
/// Store 8 contiguous vec2s to memory. Memory must be 64 byte aligned.
VMATH_INLINE_DECL void vm_store_v16f(vm_v16fs_t* output, vm_v16f_t vec);
/// Store 8 contiguous vec2s to memory as a buffer of floats. Memory must be 64
/// byte aligned.
VMATH_INLINE_DECL void vm_storeb_v16f(vm_float32_t output[16], vm_v16f_t vec);

/// Load a float32 into all elements of a 16 element vector
VMATH_INLINE_DECL vm_v16f_t vm_splat_v16f(vm_float32_t fill);

/// Add two 16 element float32 vectors together, componentwise
VMATH_INLINE_DECL vm_v16f_t vm_add_v16f(vm_v16f_t a, vm_v16f_t b);
/// Subtract a 16 element float32 vector from another, componentwise
VMATH_INLINE_DECL vm_v16f_t vm_sub_v16f(vm_v16f_t a, vm_v16f_t b);
/// Multiply two 16 element float32 vectors together, componentwise
VMATH_INLINE_DECL vm_v16f_t vm_mul_v16f(vm_v16f_t a, vm_v16f_t b);
/// Divide a 16 element float32 vector by another, componentwise
VMATH_INLINE_DECL vm_v16f_t vm_div_v16f(vm_v16f_t a, vm_v16f_t b);

/// Add a constant float32 value to all the elements of a 16 element vector
VMATH_INLINE_DECL vm_v16f_t vm_addc_v16f(vm_v16f_t a, vm_float32_t b);
/// Subtract a constant float32 value from all the elements of a 16 element
/// vector
VMATH_INLINE_DECL vm_v16f_t vm_subc_v16f(vm_v16f_t a, vm_float32_t b);
/// Multiply all the elements of a 16 element vector by a constant float32 value
VMATH_INLINE_DECL vm_v16f_t vm_mulc_v16f(vm_v16f_t a, vm_float32_t b);
/// Divide all the elements of a 16 element vector by a constant float32 value
VMATH_INLINE_DECL vm_v16f_t vm_divc_v16f(vm_v16f_t a, vm_float32_t b);

#endif // ifndef __VMATH_DECL_VEC16_F32_H
