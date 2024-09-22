/*
 * This whole file is pretty much ripped from https://github.com/ermig1979/Simd
 * See https://github.com/ermig1979/Simd/blob/master/src/Simd/SimdDefs.h
 *
 * The main difference is that I have removed C++ related stuff
 */
#ifndef __VMATH_INTERNAL_INTRINSICS_H
#define __VMATH_INTERNAL_INTRINSICS_H

#if defined(_MSC_VER) || defined(__CODEGEARC__)
#define VMATH_INLINE inline __forceinline
#elif defined(__GNUC__)
#define VMATH_INLINE inline __attribute__((always_inline))
#else
#error This platform is unsupported!
#endif

// internal flag used when including decls from c impl file
#ifdef VMATH_USE_EXTERN_INLINE
#undef VMATH_INLINE
#define VMATH_INLINE extern inline
#endif

#if defined(VMATH_SSE41_DISABLE) && !defined(VMATH_AVX2_DISABLE)
#define VMATH_AVX2_DISABLE
#endif

#if defined(VMATH_AVX2_DISABLE) && !defined(VMATH_AVX512BW_DISABLE)
#define VMATH_AVX512BW_DISABLE
#endif

#if defined(VMATH_AVX512BW_DISABLE) && !defined(VMATH_AVX512VNNI_DISABLE)
#define VMATH_AVX512VNNI_DISABLE
#endif

#if defined(VMATH_AVX512VNNI_DISABLE) && !defined(VMATH_AMXBF16_DISABLE)
#define VMATH_AMXBF16_DISABLE
#endif

/*
#if !defined(VMATH_SYNET_DISABLE)
#define VMATH_SYNET_ENABLE
#endif
*/

#if !defined(VMATH_INT8_DEBUG_DISABLE)
#define VMATH_INT8_DEBUG_ENABLE
#endif

#if defined(_MSC_VER) && defined(_MSC_FULL_VER)

#define VMATH_ALIGNED(x) __declspec(align(x))

#define VMATH_NOINLINE __declspec(noinline)

#ifdef _M_IX86
#define VMATH_X86_ENABLE
#endif

#if defined(_M_X64) || defined(_M_AMD64)
#define VMATH_X64_ENABLE
#endif

#if defined(_M_ARM)
#define VMATH_ARM_ENABLE
#endif

#if defined(_M_ARM64)
#define VMATH_ARM64_ENABLE
#endif

#if defined(__riscv) && defined(__riscv_v_intrinsic)
#if __riscv_v_intrinsic >= 1000000
#define VMATH_RISCV_V1_ENABLE
#endif
#endif // defined(__riscv) && defined(__riscv_v_intrinsic)

#if defined(VMATH_X64_ENABLE) || defined(VMATH_X86_ENABLE)

#if !defined(VMATH_SSE41_DISABLE) && _MSC_VER >= 1500
#define VMATH_SSE41_ENABLE
#endif

#if !defined(VMATH_AVX2_DISABLE) && _MSC_VER >= 1700
#define VMATH_AVX2_ENABLE
#endif

#if defined(NDEBUG) && _MSC_VER >= 1700 && _MSC_VER < 1900
#define VMATH_MADDUBS_ERROR // Visual Studio 2012/2013 release mode compiler bug
							// in function _mm256_maddubs_epi16.
#endif

#if !defined(VMATH_AVX512BW_DISABLE) && _MSC_VER >= 1920
#define VMATH_AVX512BW_ENABLE
#endif

#if !defined(VMATH_AVX512VNNI_DISABLE) && _MSC_VER >= 1924
#define VMATH_AVX512VNNI_ENABLE
#endif

#if !defined(VMATH_AMXBF16_DISABLE) && _MSC_VER >= 1933 && defined(_M_X64)
#define VMATH_AMXBF16_ENABLE
#endif

#if defined(NDEBUG) && _MSC_VER <= 1920
#define VMATH_MASKZ_LOAD_ERROR
#endif

#if _MSC_VER < 1924
#define VMATH_AVX512_FLOOR_CEIL_ABSENT
#endif

#endif // defined(VMATH_X64_ENABLE) || defined(VMATH_X86_ENABLE)

#if defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)

#if !defined(VMATH_NEON_DISABLE) && _MSC_VER >= 1700
#define VMATH_NEON_ENABLE
#endif

#endif

#elif defined(__GNUC__)

#define VMATH_ALIGNED(x) __attribute__((aligned(x)))

#define VMATH_NOINLINE __attribute__((noinline))

#ifdef __i386__
#define VMATH_X86_ENABLE
#endif

#if defined(__x86_64__) || defined(__amd64__)
#define VMATH_X64_ENABLE
#endif

#if (defined(_BIG_ENDIAN) && !defined(_LITTLE_ENDIAN)) ||                      \
	(defined(__BIG_ENDIAN__) && !defined(__LITTLE_ENDIAN__))
#define VMATH_BIG_ENDIAN
#elif defined(__GLIBC__) ||                                                    \
	(defined(__GNUC__) && !defined(__llvm__) && !defined(__MINGW32__) &&       \
	 !defined(__FreeBSD__) && defined(__BYTE_ORDER__))
#include <endian.h>
#if defined(__BYTE_ORDER) && (__BYTE_ORDER == __BIG_ENDIAN)
#define VMATH_BIG_ENDIAN
#endif
#elif defined(__sparc) || defined(__sparc__) || defined(_POWER) ||             \
	defined(__powerpc__) || defined(__ppc__) || defined(__hpux) ||             \
	defined(_MIPSEB) || defined(_POWER) || defined(__s390__)
#define VMATH_BIG_ENDIAN
#endif

#if defined __arm__
#define VMATH_ARM_ENABLE
#endif

#if defined __aarch64__
#define VMATH_ARM64_ENABLE
#endif

#if defined(VMATH_X86_ENABLE) || defined(VMATH_X64_ENABLE)

#if !defined(VMATH_SSE41_DISABLE) && defined(__SSE__) && defined(__SSE2__) &&  \
	defined(__SSE3__) && defined(__SSSE3__) && defined(__SSE4_1__) &&          \
	defined(__SSE4_2__)
#define VMATH_SSE41_ENABLE
#endif

#if !defined(VMATH_AVX2_DISABLE) && defined(__AVX__) && defined(__AVX2__)
#define VMATH_AVX2_ENABLE
#endif

#if !defined(__clang__) || (defined(__clang__) && __clang_major__ >= 4)
#if !defined(VMATH_AVX512BW_DISABLE) && defined(__AVX512BW__)
#define VMATH_AVX512BW_ENABLE
#endif

#if !defined(VMATH_AVX512VNNI_DISABLE) && defined(__AVX512VNNI__)
#define VMATH_AVX512VNNI_ENABLE
#endif

#if !defined(VMATH_AMXBF16_DISABLE) && defined(__AMX_TILE__) &&                \
	defined(__AMX_INT8__) && defined(__AMX_BF16__) && defined(__AVX512BF16__)
#define VMATH_AMXBF16_ENABLE
#endif
#endif

#endif // defined(VMATH_X86_ENABLE) || defined(VMATH_X64_ENABLE)

#if defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)

#if !defined(VMATH_NEON_DISABLE) &&                                            \
	(defined(__ARM_NEON) || defined(VMATH_ARM64_ENABLE))
#define VMATH_NEON_ENABLE
#endif

#if !defined(VMATH_NEON_ASM_DISABLE) && defined(__GNUC__)
#define VMATH_NEON_ASM_ENABLE
#endif

#if !defined(VMATH_NEON_FP16_DISABLE) &&                                       \
	(defined(__ARM_FP16_FORMAT_IEEE) ||                                        \
	 defined(__ARM_FP16_FORMAT_ALTERNATIVE))
#define VMATH_NEON_FP16_ENABLE
#endif

#endif // defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE)

#if defined(__riscv) && defined(__riscv_v_intrinsic)
#if __riscv_v_intrinsic >= 1000000
#define VMATH_RISCV_V1_ENABLE
#endif
#endif // defined(__riscv) && defined(__riscv_v_intrinsic)

#if defined(__clang__)
#define VMATH_CLANG_AVX2_BGR_TO_BGRA_ERROR
#endif

#else

#error This platform is unsupported!

#endif

#ifdef VMATH_X64_ENABLE
#include <emmintrin.h>
#include <mmintrin.h>
#endif

#ifdef VMATH_SSE41_ENABLE
#include <nmmintrin.h>
#endif

#if defined(VMATH_AVX2_ENABLE) || defined(VMATH_AVX512BW_ENABLE) ||            \
	defined(VMATH_AVX512VNNI_ENABLE) || defined(VMATH_AMXBF16_ENABLE)
#include <immintrin.h>
#endif

#if defined(VMATH_NEON_ENABLE)
#include <arm_neon.h>
#endif

#if defined(VMATH_AVX512BW_ENABLE) || defined(VMATH_AVX512VNNI_ENABLE) ||      \
	defined(VMATH_AMXBF16_ENABLE)
#define VMATH_ALIGN 64
#elif defined(VMATH_AVX2_ENABLE)
#define VMATH_ALIGN 32
#elif defined(VMATH_SSE41_ENABLE) || defined(VMATH_NEON_ENABLE)
#define VMATH_ALIGN 16
#elif defined(VMATH_X64_ENABLE) || defined(VMATH_ARM64_ENABLE)
#define VMATH_ALIGN 8
#else
#define VMATH_ALIGN 4
#endif

#if (defined(VMATH_AVX512BW_ENABLE) || defined(VMATH_AVX512VNNI_ENABLE) ||     \
	 defined(VMATH_AMXBF16_ENABLE))
#ifdef VMATH_X64_ENABLE
#if defined(__GNUC__) || (defined(_MSC_VER) && _MSC_VER >= 1915)
#define VMATH_ZMM_COUNT 32
#else
#define VMATH_ZMM_COUNT 16
#endif
#else
#define VMATH_ZMM_COUNT 8
#endif
#endif

/// generic AVX512 enable macro, determines if we can use __m512 and other
/// avx512 intrinsics
#if defined(VMATH_AVX512BW_ENABLE) || defined(VMATH_AVX512VNNI_ENABLE)
#define VMATH_AVX512_GENERIC_ENABLE
#endif

/// generic macro which determines if we can use __m256
/// TODO: fix avx256 and 512 conditions for all platforms- these are not always
/// accurate
#if defined(VMATH_AVX2_ENABLE)
#define VMATH_AVX256_GENERIC_ENABLE
#endif

#if defined(VMATH_ARM_ENABLE) || defined(VMATH_ARM64_ENABLE) ||                \
	defined(VMATH_RISCV_V1_ENABLE) || defined(VMATH_X64_ENABLE)
#define VMATH_SIMD_ENABLED
#endif

#endif
