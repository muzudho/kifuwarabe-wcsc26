#pragma once
#include "../n080_100_sysWorld/n080_100_078_lsbMsb.hpp"


//────────────────────────────────────────────────────────────────────────────────
// count1s
//────────────────────────────────────────────────────────────────────────────────



#if defined(HAVE_SSE42)


	#include <nmmintrin.h>
	/// <summary>
	/// 
	/// </summary>
	/// <param name="x"></param>
	/// <returns></returns>
	inline int count1s(u64 x)
	{
		return _mm_popcnt_u64(x);
	}


#else


	/// <summary>
	/// 任意の値の1のビットの数を数える。( x is not a const value.)
	/// </summary>
	/// <param name="x"></param>
	/// <returns></returns>
	inline int count1s(u64 x)
	{
		x = x - ((x >> 1) & UINT64_C(0x5555555555555555));
		x = (x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333));
		x = (x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f);
		x = x + (x >> 8);
		x = x + (x >> 16);
		x = x + (x >> 32);
		return (static_cast<int>(x)) & 0x0000007f;
	}


#endif
