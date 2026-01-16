#pragma once
#include "../n080_100_sysWorld/n080_100_073_forceInline.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ASMCOMMENT
//────────────────────────────────────────────────────────────────────────────────
//
//		- インラインアセンブリのコメントを使用することで、
//		  C++ コードのどの部分がアセンブラのどの部分に対応するかを
//		  分り易くする。
//		- GnuC 以外は無視するのかだぜ（＾～＾）？
#if defined(_MSC_VER) && !defined(__INTEL_COMPILER)
    #define ASMCOMMENT(s)
#elif defined(__INTEL_COMPILER)
    #define ASMCOMMENT(s)
#elif defined(__clang__)
    #define ASMCOMMENT(s)
#elif defined(__GNUC__)
    #define ASMCOMMENT(s) __asm__("#"s)
#else
    #define ASMCOMMENT(s)
#endif
