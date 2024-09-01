#ifndef __VMATH_VEC2_F32_H
#define __VMATH_VEC2_F32_H

#include "vmath/internal/intrinsics.h"
#include "vmath/internal/stdfloat.h"
#include "vmath/internal/stdint.h"
#include <math.h>

typedef struct VMATH_ALIGNED(8)
{
	float x;
	float y;
} vmath_vec2_f32_t;

/*
 * Add / subtract / multiply / divide two vec2, componentwise
 */

VMATH_INLINE vmath_vec2_f32_t vmath_vec2_f32_add(const vmath_vec2_f32_t a,
												 const vmath_vec2_f32_t b)
{
	return (vmath_vec2_f32_t){a.x + b.x, a.y + b.y};
}

VMATH_INLINE vmath_vec2_f32_t vmath_vec2_f32_sub(const vmath_vec2_f32_t a,
												 const vmath_vec2_f32_t b)
{
	return (vmath_vec2_f32_t){a.x - b.x, a.y - b.y};
}

VMATH_INLINE vmath_vec2_f32_t vmath_vec2_f32_mul(const vmath_vec2_f32_t a,
												 const vmath_vec2_f32_t b)
{
	return (vmath_vec2_f32_t){a.x * b.x, a.y * b.y};
}

VMATH_INLINE vmath_vec2_f32_t vmath_vec2_f32_div(const vmath_vec2_f32_t a,
												 const vmath_vec2_f32_t b)
{
	return (vmath_vec2_f32_t){a.x / b.x, a.y / b.y};
}

/*
 * Add / subtract / multiply / divide with constant
 */

VMATH_INLINE vmath_vec2_f32_t
vmath_vec2_f32_add_constant(const vmath_vec2_f32_t vec, float constant)
{
	return (vmath_vec2_f32_t){vec.x + constant, vec.y + constant};
}

VMATH_INLINE vmath_vec2_f32_t
vmath_vec2_f32_sub_constant(const vmath_vec2_f32_t vec, float constant)
{
	return (vmath_vec2_f32_t){vec.x - constant, vec.y - constant};
}

VMATH_INLINE vmath_vec2_f32_t
vmath_vec2_f32_mul_constant(const vmath_vec2_f32_t vec, float constant)
{
	return (vmath_vec2_f32_t){vec.x * constant, vec.y * constant};
}

VMATH_INLINE vmath_vec2_f32_t
vmath_vec2_f32_div_constant(const vmath_vec2_f32_t vec, float constant)
{
	return (vmath_vec2_f32_t){vec.x / constant, vec.y / constant};
}

/*
 * Special operations
 */

VMATH_INLINE float vmath_vec2_f32_length(const vmath_vec2_f32_t vec)
{
	return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

VMATH_INLINE float vmath_vec2_f32_length_sqr(const vmath_vec2_f32_t vec)
{
	return (vec.x * vec.x) + (vec.y * vec.y);
}

VMATH_INLINE vmath_float32_t vmath_vec2_f32_dot(const vmath_vec2_f32_t a,
												const vmath_vec2_f32_t b)
{
	return (a.x * b.x) + (a.y * b.y);
}

VMATH_INLINE int8_t vmath_vec2_f32_eql(const vmath_vec2_f32_t a,
									   const vmath_vec2_f32_t b)
{
	return (int8_t)(a.x == b.x && a.y == b.y);
}

VMATH_INLINE float vmath_vec2_f32_distance(const vmath_vec2_f32_t a,
										   const vmath_vec2_f32_t b)
{
	return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

VMATH_INLINE float vmath_vec2_f32_distance_sqr(const vmath_vec2_f32_t a,
											   const vmath_vec2_f32_t b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

VMATH_INLINE vmath_vec2_f32_t
vmath_vec2_f32_normalize(const vmath_vec2_f32_t vec)
{
	const float length = sqrtf((vec.x * vec.x) + (vec.y * vec.y));

	if (length > 0) {
		const float ilength = 1.0F / length;
		return (vmath_vec2_f32_t){vec.x * ilength, vec.y * ilength};
	}

	return (vmath_vec2_f32_t){0};
}

VMATH_INLINE vmath_vec2_f32_t vmath_vec2_f32_lerp(const vmath_vec2_f32_t a,
												  const vmath_vec2_f32_t b,
												  const float amount)
{
	return (vmath_vec2_f32_t){
		.x = a.x + amount * (b.x - a.x),
		.y = a.y + amount * (b.y - a.y),
	};
}

VMATH_INLINE vmath_vec2_f32_t vmath_vec2_f32_reflect(
	const vmath_vec2_f32_t vec, const vmath_vec2_f32_t normal)
{
	const float dotProduct = (vec.x * normal.x + vec.y * normal.y);

	return (vmath_vec2_f32_t){
		.x = vec.x - (2.0F * normal.x) * dotProduct,
		.y = vec.y - (2.0F * normal.y) * dotProduct,
	};
}

VMATH_INLINE vmath_vec2_f32_t vmath_vec2_f32_min(const vmath_vec2_f32_t v1,
												 const vmath_vec2_f32_t v2)
{
	return (vmath_vec2_f32_t){
		.x = fminf(v1.x, v2.x),
		.y = fminf(v1.y, v2.y),
	};
}

// Get max value for each pair of components
VMATH_INLINE vmath_vec2_f32_t vmath_vec2_f32_max(const vmath_vec2_f32_t v1,
												 const vmath_vec2_f32_t v2)
{
	return (vmath_vec2_f32_t){
		.x = fmaxf(v1.x, v2.x),
		.y = fmaxf(v1.y, v2.y),
	};
}

#endif
