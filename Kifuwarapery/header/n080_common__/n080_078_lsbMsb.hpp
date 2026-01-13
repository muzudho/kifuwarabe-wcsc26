#pragma once
#include "../n080_common__/n080_077_binary.hpp"


//────────────────────────────────────────────────────────────────────────────────
// firstOneFromLSB, firstOneFromMSB
//────────────────────────────────────────────────────────────────────────────────


#if defined(_MSC_VER) && !defined(__INTEL_COMPILER) && defined(_WIN64)
#include <intrin.h>
/// <summary>
/// 
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
FORCE_INLINE int firstOneFromLSB(const u64 b)
{
	unsigned long index;
	_BitScanForward64(&index, b);
	return index;
}


/// <summary>
/// 
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
FORCE_INLINE int firstOneFromMSB(const u64 b)
{
	unsigned long index;
	_BitScanReverse64(&index, b);
	return 63 - index;
}


#elif defined(__GNUC__) && ( defined(__i386__) || defined(__x86_64__) )
	/// <summary>
	/// 
	/// </summary>
	/// <param name="b"></param>
	/// <returns></returns>
FORCE_INLINE int firstOneFromLSB(const u64 b)
{
	return __builtin_ctzll(b);
}


/// <summary>
/// 
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
FORCE_INLINE int firstOneFromMSB(const u64 b)
{
	return __builtin_clzll(b);
}
#else


	/// <summary>
	/// firstOneFromLSB() で使用する table
	/// </summary>
const int BitTable[64] =
{
	63, 30, 3, 32, 25, 41, 22, 33, 15, 50, 42, 13, 11, 53, 19, 34, 61, 29, 2,
	51, 21, 43, 45, 10, 18, 47, 1, 54, 9, 57, 0, 35, 62, 31, 40, 4, 49, 5, 52,
	26, 60, 6, 23, 44, 46, 27, 56, 16, 7, 39, 48, 24, 59, 14, 12, 55, 38, 28,
	58, 20, 37, 17, 36, 8
};


/// <summary>
/// LSB から数えて初めに bit が 1 になるのは何番目の bit かを返す。
/// b = 8 だったら 3 を返す。
/// b = 0 のとき、63 を返す。
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
FORCE_INLINE int firstOneFromLSB(const u64 b)
{
	const u64 tmp = b ^ (b - 1);
	const u32 old = static_cast<u32>((tmp & 0xffffffff) ^ (tmp >> 32));
	return BitTable[(old * 0x783a9b23) >> 26];
}


/// <summary>
/// 超絶遅いコードなので後で書き換えること。
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
FORCE_INLINE int firstOneFromMSB(const u64 b)
{
	for (int i = 63; 0 <= i; --i)
	{
		if (b >> i) { return 63 - i; }
	}

	return 0;
}
#endif
