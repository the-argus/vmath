/*
 * Some float values in simd registers describing rotation, scale, and
 * translation of a 2D object.
 */
#ifndef __VMATH_DECL_TRANSFORM2D_F32_H
#define __VMATH_DECL_TRANSFORM2D_F32_H

#include "vmath/decl/vec2_f32.h"
#include "vmath/decl/vec4_f32.h"
#include "vmath/internal/intrinsics.h"

typedef struct
{
	vm_v4fs_t basis;
	vm_v2fs_t offset;
} vm_transform2dfs_t;

typedef struct // NOLINT
{
	vm_v4f_t basis;
	vm_v2f_t offset;
} vm_transform2df_t;

/// Load a transform2D from memory
VMATH_INLINE_DECL vm_transform2df_t
vm_load_transform2df(const vm_transform2dfs_t* transform);

/// Store a transform2D to memory
VMATH_INLINE_DECL void vm_store_transform2df(vm_transform2dfs_t* output,
											 vm_transform2df_t transform);

/// Load the identity transform into registers
VMATH_INLINE_DECL vm_transform2df_t vm_load_identity_transform2df(void);

/// Create a transform describing a rotation in radians
VMATH_INLINE_DECL vm_transform2df_t
vm_load_rotation_transform2df(vm_float32_t theta);

/// Create a transform describing a translation along local X and Y axes
VMATH_INLINE_DECL vm_transform2df_t
vm_load_translation_transform2df(vm_float32_t x, vm_float32_t y);
/// Create a transform describing a translation along local X and Y axes, vector
/// variant
VMATH_INLINE_DECL vm_transform2df_t
vm_load_translationv_transform2df(vm_v2f_t offset);

/// Create a transform describing a scaling along local X and Y axes
VMATH_INLINE_DECL vm_transform2df_t vm_load_scale_transform2df(vm_float32_t x,
															   vm_float32_t y);
/// Create a transform describing a scaling along local X and Y axes, vector
/// variant
VMATH_INLINE_DECL vm_transform2df_t
vm_load_scalev_transform2df(vm_v2f_t offset);

/// Compose two transforms, resulting in a transform which describes performing
/// transform A, and then B
VMATH_INLINE_DECL vm_transform2df_t vm_mul_transform2df(vm_transform2df_t a,
														vm_transform2df_t b);

/*
 * Extension to Vector2 api
 */

VMATH_INLINE_DECL vm_v2f_t vm_transform_v2f(vm_v2f_t vec,
											vm_transform2df_t transform);

#endif
