/*
 * 2-Element Vector
 * A wrapper around vec4. It is only a distinct type from vec4 when using scalar
 * fallback.
 * Most vec2 functions just call the vec4 counterparts, with the exception of
 * special operations like length etc.
 */
#ifndef __VMATH_DECL_VEC2_F32_H
#define __VMATH_DECL_VEC2_F32_H

#include "vmath/decl/vec4_f32.h"

/// vec2 storage type
typedef struct
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

/// Load a vec2 from memory.
VMATH_INLINE_DECL vm_v2f_t vm_load_v2f(const vm_v2fs_t* vec);
/// Load a vec2 from memory as a float buffer.
VMATH_INLINE_DECL vm_v2f_t vm_loadb_v2f(const vm_float32_t vec[2]);
/// Store a vec2 into memory.
VMATH_INLINE_DECL void vm_store_v2f(vm_v2fs_t* output, vm_v2f_t vector);
/// Store a vec2 into memory as a float buffer.
VMATH_INLINE_DECL void vm_storeb_v2f(vm_float32_t output[2], vm_v2f_t vector);

/// Load a constant { 1, 1 } into a vec2
VMATH_INLINE_DECL vm_v2f_t vm_load_ones_v2f(void);
/// Load a constant { 0, 0 } into a vec2
VMATH_INLINE_DECL vm_v2f_t vm_load_zeroes_v2f(void);

/// Load a float32 into both elements of a vec2
VMATH_INLINE_DECL vm_v2f_t vm_splat_v2f(vm_float32_t fill);

/// Convert a vector4 to a vector2 by removing the last two elements
VMATH_INLINE_DECL vm_v2f_t vm_shave4_v2f(vm_v4f_t vec);

// Extract the first element of a vector
VMATH_INLINE_DECL vm_float32_t vm_extract_x_v2f(vm_v2f_t vec);

/// Add two vec2s together, componentwise
VMATH_INLINE_DECL vm_v2f_t vm_add_v2f(vm_v2f_t a, vm_v2f_t b);
/// Subtract two vec2s together, componentwise
VMATH_INLINE_DECL vm_v2f_t vm_sub_v2f(vm_v2f_t a, vm_v2f_t b);
/// Multiply two vec2s together, componentwise
VMATH_INLINE_DECL vm_v2f_t vm_mul_v2f(vm_v2f_t a, vm_v2f_t b);
/// Divide two vec2s together, componentwise
VMATH_INLINE_DECL vm_v2f_t vm_div_v2f(vm_v2f_t a, vm_v2f_t b);

/// Add a constant float32 to all the components of a vec2
VMATH_INLINE_DECL vm_v2f_t vm_addc_v2f(vm_v2f_t a, vm_float32_t b);
/// Subtract a constant float32 from all the components of a vec2
VMATH_INLINE_DECL vm_v2f_t vm_subc_v2f(vm_v2f_t a, vm_float32_t b);
/// Multiply all components of a vec2 by a float32
VMATH_INLINE_DECL vm_v2f_t vm_mulc_v2f(vm_v2f_t a, vm_float32_t b);
/// Divide all components of a vec2 by a float32
VMATH_INLINE_DECL vm_v2f_t vm_divc_v2f(vm_v2f_t a, vm_float32_t b);

/// Compute the length of a vec2, sending it into all components of an output
/// vec2. Can keep values inside SIMD registers, which may be advantageous
VMATH_INLINE_DECL vm_v2f_t vm_length_v2f(vm_v2f_t vec);
/// Compute 1 over the length of a vec2, sending it into all components of an
/// output vec2. Can keep values inside SIMD registers, which may be
/// advantageous
VMATH_INLINE_DECL vm_v2f_t vm_length_inv_v2f(vm_v2f_t vec);
/// Less accurate but faster version of length_inv
VMATH_INLINE_DECL vm_v2f_t vm_length_inv_est_v2f(vm_v2f_t vec);
/// Compute the length of a vec2, sending it into all components of an output
/// vec2. Can keep values inside SIMD registers, which may be advantageous
VMATH_INLINE_DECL vm_v2f_t vm_length_sqr_v2f(vm_v2f_t vec);

/// Compute the length of a vec2, and then read the resulting vector out into
/// memory, and return the X component.
VMATH_INLINE_DECL vm_float32_t vm_lengthx_v2f(vm_v2f_t vec);
/// Compute 1 over the length of a vec2, and then read the resulting vector out
/// into memory, and return the X component.
VMATH_INLINE_DECL vm_float32_t vm_length_invx_v2f(vm_v2f_t vec);
/// Less accurate but faster version of length_invx
VMATH_INLINE_DECL vm_float32_t vm_length_inv_estx_v2f(vm_v2f_t vec);
/// Compute the length of a vec2, squared, and then read the resulting vector
/// out into memory, and return the X component. Faster than finding the length
VMATH_INLINE_DECL vm_float32_t vm_length_sqrx_v2f(vm_v2f_t vec);

VMATH_INLINE_DECL vm_v2f_t vm_dot_v2f(vm_v2f_t vec1, vm_v2f_t vec2);
VMATH_INLINE_DECL vm_v2f_t vm_distance_v2f(vm_v2f_t vec1, vm_v2f_t vec2);
VMATH_INLINE_DECL vm_v2f_t vm_distance_sqr_v2f(vm_v2f_t vec1, vm_v2f_t vec2);
VMATH_INLINE_DECL vm_v2f_t vm_angle_v2f(vm_v2f_t vec1, vm_v2f_t vec2);
VMATH_INLINE_DECL vm_v2f_t vm_normalize_v2f(vm_v2f_t vec);
VMATH_INLINE_DECL vm_v2f_t vm_lerp_v2f(vm_v2f_t vec1, vm_v2f_t vec2,
									   vm_v2f_t amount);
VMATH_INLINE_DECL vm_v2f_t vm_reflect_v2f(vm_v2f_t vec, vm_v2f_t normal);
VMATH_INLINE_DECL vm_v2f_t vm_move_towards_v2f(vm_v2f_t vec, vm_v2f_t target,
											   vm_v2f_t max_distance);
VMATH_INLINE_DECL vm_v2f_t vm_clamp_axes_v2f(vm_v2f_t vec, vm_v2f_t min,
											 vm_v2f_t max);
VMATH_INLINE_DECL vm_v2f_t vm_clamp_magnitude_v2f(vm_v2f_t vec, vm_v2f_t range);

#endif
