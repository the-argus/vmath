/*
 * A wrapper around vec4. It is only a distinct type from vec2 when using scalar
 * fallback.
 * Most vec2 functions just call the vec4 counterparts, with the exception of
 * special operations like length etc.
 *
 * An additional consideration for vec2 is that the storage type is two floats
 * and is 8 byte aligned, meaning that the default load is a type of unaligned
 * load, and may be slower than storing vec4s and doing vec2 operations on them.
 */
#ifndef __VMATH_DECL_VEC2_F32_H
#define __VMATH_DECL_VEC2_F32_H

#include "vmath/decl/vec4_f32.h"
#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"

/// vec2 storage type
typedef struct VMATH_ALIGNED(8)
{
	vm_float32_t x;
	vm_float32_t y;
} vm_v2fs_t;

#ifdef VMATH_SIMD_ENABLED
typedef vm_v4f_t vm_v2f_t;
#else
typedef struct
{
	/// Non-simd implementation detail
	vm_v2fs_t _inner;
} vm_v2f_t;
#endif

/// Load a vec2 from memory. Memory must be 8-byte aligned.
VMATH_INLINE vm_v2f_t vm_load_v2f(const vm_v2fs_t* vec);
/// Load a vec2 from memory as a float buffer. Memory must be 8-byte aligned.
VMATH_INLINE vm_v2f_t vm_loadb_v2f(const vm_float32_t vec[2]);
/// Store a vec2 into memory. Memory must be 8 byte aligned.
VMATH_INLINE void vm_store_v2f(vm_v2fs_t* output, vm_v2f_t vector);
/// Store a vec2 into memory as a float buffer. Memory must be 8 byte aligned.
VMATH_INLINE void vm_storeb_v2f(vm_float32_t output[2], vm_v2f_t vector);

/// Load a vec2 from a vec4 storage type. Because vec4 storage must be 16 byte
/// aligned, this load may be faster than vm_load_v2f/vm_loadb_v2f. Note that
/// this operation may perform a memory read from all the elements of the vec4
/// storage. Whether the upper two elements are present in the output
/// register(s) is undefined.
VMATH_INLINE vm_v2f_t vm_load4_v2f(const vm_v4fs_t* vec);
/// Load a vec2 from vec4 storage, a 16 byte aligned buffer of 4 single
/// precision floats. Because vec4 storage must be 16 byte aligned, this load
/// may be faster than vm_load_v2f/vm_loadb_v2f. Note that this operation may
/// perform a memory read from all the elements of the vec4 storage. Whether the
/// upper two elements are present in the output register(s) is undefined.
VMATH_INLINE vm_v2f_t vm_loadb4_v2f(const vm_float32_t vec[4]);
/// Store a vec2 into a vec4 storage type. The memory must be 16 byte aligned.
/// The contents of the upper two values of the vec4 after this operation is
/// undefined.
/// This store may be faster than vm_store_v2f/vm_storeb_v2f due to higher
/// alignment, but you must provide 2x the memory.
VMATH_INLINE void vm_store4_v2f(vm_v4fs_t* output, vm_v2f_t vector);
/// Store a vec2 into a vec4 storage, a 16 byte aligned buffer of 4 single
/// precision floats. The memory must be 16 byte aligned. The contents of the
/// upper two values of the vec4 after this operation is undefined. This store
/// may be faster than vm_store_v2f/vm_storeb_v2f due to higher alignment, but
/// you must provide 2x the memory.
VMATH_INLINE void vm_storeb4_v2f(vm_float32_t output[4], vm_v2f_t vector);

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

/// Compute the length of a vec2, sending it into all components of an output
/// vec2. Can keep values inside SIMD registers, which may be advantageous
VMATH_INLINE vm_v2f_t vm_length_v2f(vm_v2f_t vec);
/// Compute 1 over the length of a vec2, sending it into all components of an
/// output vec2. Can keep values inside SIMD registers, which may be
/// advantageous
VMATH_INLINE vm_v2f_t vm_length_inv_v2f(vm_v2f_t vec);
/// Compute the length of a vec2, sending it into all components of an output
/// vec2. Can keep values inside SIMD registers, which may be advantageous
VMATH_INLINE vm_v2f_t vm_length_sqr_v2f(vm_v2f_t vec);

/// Compute the length of a vec2, and then read the resulting vector out into
/// memory, and return the X component.
VMATH_INLINE float vm_lengthx_v2f(vm_v2f_t vec);
/// Compute 1 over the length of a vec2, and then read the resulting vector out
/// into memory, and return the X component.
VMATH_INLINE float vm_length_invx_v2f(vm_v2f_t vec);
/// Compute the length of a vec2, squared, and then read the resulting vector
/// out into memory, and return the X component. Faster than finding the length
VMATH_INLINE float vm_length_sqrx_v2f(vm_v2f_t vec);

#endif
