#ifndef __VMATH_DECL_VEC2_F32_H
#define __VMATH_DECL_VEC2_F32_H

#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"
#include "vmath/internal/stdint.h"

/// Vector of 2 floats for storage in main memory
/// (v -> vector, 2f -> two single-precision floats, s -> storage)
typedef struct VMATH_ALIGNED(8)
{
	vm_float32_t x;
	vm_float32_t y;
} vm_v2fs_t;

#define SCALAR_8BATCH_FALLBACK()                                               \
	typedef struct VMATH_ALIGNED(64)                                           \
	{                                                                          \
		vm_v2fs_t buffer[8];                                                   \
	} vm_8batch_v2f_t;
#define SCALAR_2BATCH_FALLBACK()                                               \
	typedef struct VMATH_ALIGNED(16)                                           \
	{                                                                          \
		vm_v2fs_t buffer[2];                                                   \
	} vm_2batch_v2f_t;

/// define vm_8batch_v2f_t -> batch of 8 vec2s, each with 2 single-precision
/// floating point values
/// also vm_2batch_v2f_t -> batch of 2 vec2s, each with 2 single-precision
/// floating point values
#if defined(VMATH_X64_ENABLE)
#if defined(VMATH_SSE41_ENABLE)
// not using __m64 because it seems to lack floating point capability?
typedef __m128 vm_v2f_t;
// always use SSE types and instructions for smaller batches
typedef __m128 vm_2batch_v2f_t;
// with avx, use native 8batch
// for SSE, 8batch needs to be emulated with smaller batches
#if defined(VMATH_AVX512BW_ENABLE)
typedef __m512 vm_8batch_v2f_t;
#else
typedef struct VMATH_ALIGNED(64)
{
	__m128 buffer[4];
} vm_8batch_v2f_t;
#endif // defined(VMATH_AVX512BW_ENABLE)
#else
// in this case, there is no sse 4.1, emulate it with scalar
SCALAR_8BATCH_FALLBACK()
SCALAR_2BATCH_FALLBACK()
typedef vm_v2fs_t vm_v2f_t;
#endif // defined(VMATH_SSE41_ENABLE)

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
#error ARM SIMD not implemented
#else
/*
 * Scalar fallback. 32 bit machine or something
 */
SCALAR_8BATCH_FALLBACK()
SCALAR_2BATCH_FALLBACK()
typedef vm_v2fs_t vm_v2f_t;
#endif
#undef SCALAR_2BATCH_FALLBACK
#undef SCALAR_8BATCH_FALLBACK

/// Load a vec2 from memory
VMATH_INLINE vm_v2f_t vm_load_v2f(const vm_v2fs_t vector[1]);
/// Store a vec2 into memory
VMATH_INLINE void vm_store_v2f(vm_v2fs_t output[1], vm_v2f_t vector);
/// Load 8 contiguous vec2s from memory
VMATH_INLINE vm_8batch_v2f_t vm_load_8xv2f(const vm_v2fs_t batch[8]);
/// Store 8 contiguous vec2s to memory
VMATH_INLINE void vm_store_8xv2f(vm_v2fs_t output[8], vm_8batch_v2f_t batch);
/// Load 2 contiguous vec2s from memory
VMATH_INLINE vm_2batch_v2f_t vm_load_2xv2f(const vm_v2fs_t batch[2]);
/// Store 2 contiguous vec2s to memory
VMATH_INLINE void vm_store_2xv2f(vm_v2fs_t output[2], vm_2batch_v2f_t batch);

/// Load a float32 into both elements of a vec2
VMATH_INLINE vm_v2f_t vm_splat_v2f(vm_float32_t fill);
/// Load a float32 into all elements of a batch of 2 vec2s
VMATH_INLINE vm_2batch_v2f_t vm_splat_2xv2f(vm_float32_t fill);
/// Load a float32 into all elements of a batch of 8 vec2s
VMATH_INLINE vm_8batch_v2f_t vm_splat_8xv2f(vm_float32_t fill);

/// Add two vec2s together, componentwise
VMATH_INLINE vm_v2f_t vm_add_v2f(vm_v2f_t a, vm_v2f_t b);
/// Subtract two vec2s together, componentwise
VMATH_INLINE vm_v2f_t vm_sub_v2f(vm_v2f_t a, vm_v2f_t b);
/// Multiply two vec2s together, componentwise
VMATH_INLINE vm_v2f_t vm_mul_v2f(vm_v2f_t a, vm_v2f_t b);
/// Divide two vec2s together, componentwise
VMATH_INLINE vm_v2f_t vm_div_v2f(vm_v2f_t a, vm_v2f_t b);

/// Add two sets of 8 contiguous vec2s together, componentwise
VMATH_INLINE vm_8batch_v2f_t vm_add_8xv2f(vm_8batch_v2f_t a, vm_8batch_v2f_t b);
/// Subtract two sets of 8 contiguous vec2s together, componentwise
VMATH_INLINE vm_8batch_v2f_t vm_sub_8xv2f(vm_8batch_v2f_t a, vm_8batch_v2f_t b);
/// Multiply two sets of 8 contiguous vec2s together, componentwise
VMATH_INLINE vm_8batch_v2f_t vm_mul_8xv2f(vm_8batch_v2f_t a, vm_8batch_v2f_t b);
/// Divide two sets of 8 contiguous vec2s together, componentwise
VMATH_INLINE vm_8batch_v2f_t vm_div_8xv2f(vm_8batch_v2f_t a, vm_8batch_v2f_t b);

/// Add two sets of 2 contiguous vec2s together, componentwise
VMATH_INLINE vm_2batch_v2f_t vm_add_2xv2f(vm_2batch_v2f_t a, vm_2batch_v2f_t b);
/// Subtract two sets of 2 contiguous vec2s together, componentwise
VMATH_INLINE vm_2batch_v2f_t vm_sub_2xv2f(vm_2batch_v2f_t a, vm_2batch_v2f_t b);
/// Multiply two sets of 2 contiguous vec2s together, componentwise
VMATH_INLINE vm_2batch_v2f_t vm_mul_2xv2f(vm_2batch_v2f_t a, vm_2batch_v2f_t b);
/// Divide two sets of 2 contiguous vec2s together, componentwise
VMATH_INLINE vm_2batch_v2f_t vm_div_2xv2f(vm_2batch_v2f_t a, vm_2batch_v2f_t b);

/// Add a constant float32 to all the components of a vec2
VMATH_INLINE vm_v2f_t vm_add_v2f_constant(vm_v2f_t a, vm_float32_t b);
/// Subtract a constant float32 from all the components of a vec2
VMATH_INLINE vm_v2f_t vm_sub_v2f_constant(vm_v2f_t a, vm_float32_t b);
/// Multiply all components of a vec2 by a float32
VMATH_INLINE vm_v2f_t vm_mul_v2f_constant(vm_v2f_t a, vm_float32_t b);
/// Divide all components of a vec2 by a float32
VMATH_INLINE vm_v2f_t vm_div_v2f_constant(vm_v2f_t a, vm_float32_t b);

/// Add a constant float32 to all the components of all the vec2s in a batch of
/// 8
VMATH_INLINE vm_8batch_v2f_t vm_add_8xv2f_constant(vm_8batch_v2f_t a,
												   vm_float32_t b);
/// Subtract a constant float32 to all the components of all the vec2s in a
/// batch of 8
VMATH_INLINE vm_8batch_v2f_t vm_sub_8xv2f_constant(vm_8batch_v2f_t a,
												   vm_float32_t b);
/// Multiply a constant float32 to all the components of all the vec2s in a
/// batch of 8
VMATH_INLINE vm_8batch_v2f_t vm_mul_8xv2f_constant(vm_8batch_v2f_t a,
												   vm_float32_t b);
/// Divide a constant float32 to all the components of all the vec2s in a
/// batch of 8
VMATH_INLINE vm_8batch_v2f_t vm_div_8xv2f_constant(vm_8batch_v2f_t a,
												   vm_float32_t b);

/// Add a constant float32 to all the components of all the vec2s in a batch of
/// 2
VMATH_INLINE vm_2batch_v2f_t vm_add_2xv2f_constant(vm_2batch_v2f_t a,
												   vm_float32_t b);
/// Subtract a constant float32 to all the components of all the vec2s in a
/// batch of 2
VMATH_INLINE vm_2batch_v2f_t vm_sub_2xv2f_constant(vm_2batch_v2f_t a,
												   vm_float32_t b);
/// Multiply a constant float32 to all the components of all the vec2s in a
/// batch of 2
VMATH_INLINE vm_2batch_v2f_t vm_mul_2xv2f_constant(vm_2batch_v2f_t a,
												   vm_float32_t b);
/// Divide a constant float32 to all the components of all the vec2s in a
/// batch of 2
VMATH_INLINE vm_2batch_v2f_t vm_div_2xv2f_constant(vm_2batch_v2f_t a,
												   vm_float32_t b);

/// Compute the length of a vec2
VMATH_INLINE float vm_length_v2f(vm_v2f_t vec);
/// Compute 1 over the length of a vec2
VMATH_INLINE float vm_length_inv_v2f(vm_v2f_t vec);
/// Compute the length of a vec2, squared. Faster than finding the length
VMATH_INLINE float vm_length_sqr_v2f(vm_v2f_t vec);
/// Compute the length of a vec2, sending it into all components of an output
/// vec2. Can keep values inside SIMD registers, which may be advantageous
VMATH_INLINE vm_v2f_t vm_length_v2f_splat(vm_v2f_t vec);
/// Compute 1 over the length of a vec2, sending it into all components of an
/// output vec2. Can keep values inside SIMD registers, which may be
/// advantageous
VMATH_INLINE vm_v2f_t vm_length_inv_v2f_splat(vm_v2f_t vec);
/// Compute the length of a vec2, sending it into all components of an output
/// vec2. Can keep values inside SIMD registers, which may be advantageous
VMATH_INLINE vm_v2f_t vm_length_sqr_v2f_splat(vm_v2f_t vec);

#endif
