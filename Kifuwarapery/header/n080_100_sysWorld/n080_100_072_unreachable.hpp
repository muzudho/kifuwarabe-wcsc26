#pragma once
#include "../n080_100_sysWorld/n080_100_076_int.hpp"


//────────────────────────────────────────────────────────────────────────────────
// UNREACHABLE
//────────────────────────────────────────────────────────────────────────────────
//
//		- 通ってはいけないコントロール・パスを通った時に、プログラムを止めるためのもの

#if !defined(NDEBUG)
	// デバッグ時は、ここへ到達してはいけないので、assert でプログラムを止める。
#define UNREACHABLE assert(false)
#elif defined(_MSC_VER) && !defined(__INTEL_COMPILER)
#define UNREACHABLE __assume(false)
#elif defined(__INTEL_COMPILER)
	// todo: icc も __assume(false) で良いのか？ 一応ビルド出来るけど。
#define UNREACHABLE __assume(false)
#elif defined(__GNUC__) && (4 < __GNUC__ || (__GNUC__ == 4 && 4 < __GNUC_MINOR__))
#define UNREACHABLE __builtin_unreachable()
#else
#define UNREACHABLE assert(false)
#endif
