#ifndef __VMATH_DECL_VEC2_F32_H
#define __VMATH_DECL_VEC2_F32_H

#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"
#include "vmath/internal/stdint.h"

/// Vector of 2 floats for storage in main memory
/// (v -> vector, 2f -> two single-precision floats, s -> storage)
typedef struct VMATH_ALIGNED(16)
{
	vm_float32_t x;
	vm_float32_t y;
} vm_v2fs_t;

#define VMATH_V2_SCALAR_FALLBACK()                                             \
	typedef struct                                                             \
	{                                                                          \
		vm_float32_t buffer[2];                                                \
	} vm_v2f_t;

// clang-format off
#if defined(VMATH_X64_ENABLE)

    #if defined(VMATH_SSE41_ENABLE)
        // not using __m64 because it seems to lack floating point capability?
        typedef __m128 vm_v2f_t;
    #else
        VMATH_V2_SCALAR_FALLBACK()
    #endif

#elif defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)
    #error ARM SIMD not implemented
#elif defined(VMATH_RISCV_V1_ENABLE)
    #error RISCV vector extensions not implemented
#else
    /*
     * Scalar fallback. 32 bit machine or something
     */
    VMATH_V2_SCALAR_FALLBACK()
#endif
#undef VMATH_V2_SCALAR_FALLBACK
// clang-format on

/// Load a vec2 from memory. Memory must be 16-byte aligned
VMATH_INLINE vm_v2f_t vm_load_v2f(const vm_v2fs_t* vec);
/// Load a vec2 from memory as a float buffer. Memory must be 16-byte aligned
VMATH_INLINE vm_v2f_t vm_loadb_v2f(const vm_float32_t vec[2]);
/// Store a vec2 into memory. Memory must be 16 byte aligned.
VMATH_INLINE void vm_store_v2f(vm_v2fs_t* output, vm_v2f_t vector);
/// Store a vec2 into memory as a float buffer. Memory must be 16 byte aligned.
VMATH_INLINE void vm_storeb_v2f(vm_float32_t output[2], vm_v2f_t vector);

/// Load a float32 into both elements of a vec2
VMATH_INLINE vm_v2f_t vm_splat_v2f(vm_float32_t fill);

/// Add two vec2s together, componentwise
VMATH_INLINE vm_v2f_t vm_add_v2f(vm_v2f_t a, vm_v2f_t b);
/// Subtract two vec2s together, componentwise
VMATH_INLINE vm_v2f_t vm_sub_v2f(vm_v2f_t a, vm_v2f_t b);
/// Multiply two vec2s together, componentwise
VMATH_INLINE vm_v2f_t vm_mul_v2f(vm_v2f_t a, vm_v2f_t b);
/// Divide two vec2s together, componentwise
VMATH_INLINE vm_v2f_t vm_div_v2f(vm_v2f_t a, vm_v2f_t b);

/// Add a constant float32 to all the components of a vec2
VMATH_INLINE vm_v2f_t vm_addc_v2f(vm_v2f_t a, vm_float32_t b);
/// Subtract a constant float32 from all the components of a vec2
VMATH_INLINE vm_v2f_t vm_subc_v2f(vm_v2f_t a, vm_float32_t b);
/// Multiply all components of a vec2 by a float32
VMATH_INLINE vm_v2f_t vm_mulc_v2f(vm_v2f_t a, vm_float32_t b);
/// Divide all components of a vec2 by a float32
VMATH_INLINE vm_v2f_t vm_divc_v2f(vm_v2f_t a, vm_float32_t b);

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
