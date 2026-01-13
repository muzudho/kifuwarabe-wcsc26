#pragma once
#include "../n080_100_sysWorld/n080_072_unreachable.hpp"


//────────────────────────────────────────────────────────────────────────────────
// FORCE_INLINE
//────────────────────────────────────────────────────────────────────────────────
//
//      - インライン展開。関数を呼び出す替わりに、その内容をハードコーディングするよう強制するもの

#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#define FORCE_INLINE __forceinline
#elif defined(__INTEL_COMPILER)
#define FORCE_INLINE inline
#elif defined(__GNUC__)
#define FORCE_INLINE __attribute__((always_inline)) inline
#else
#define FORCE_INLINE inline
#endif
