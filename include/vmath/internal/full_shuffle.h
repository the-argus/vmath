#ifndef __VMATH_SSE_FULL_SHUFFLE_H__
#define __VMATH_SSE_FULL_SHUFFLE_H__

#include "vmath/decl/constants.h"

/// Generates a block of code which shuffles both "a" and "b" by "shuffle", and
/// then selects elements from either "a" or "b" by the boolean values "use_b_*"
/// and then writes the result to a variable "outname"
#define VMATH_SSE_FULL_SHUFFLE(outname, a, b, shuffle, mask)                   \
	{                                                                          \
		const __m128 shuffled_a = _mm_shuffle_ps((a), (a), shuffle);           \
		const __m128 shuffled_b = _mm_shuffle_ps((b), (b), shuffle);           \
		const __m128 masked_a = _mm_andnot_ps((mask).vector_rep, shuffled_a);  \
		const __m128 masked_b = _mm_and_ps((mask).vector_rep, shuffled_b);     \
		(outname) = _mm_or_ps(masked_a, masked_b);                             \
	}

#endif
