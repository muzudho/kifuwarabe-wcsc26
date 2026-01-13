#pragma once
#include "../n080_100_sysWorld/n080_079_count1s.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 2進数出力
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// (デバッグ用)2進表示
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="value"></param>
/// <param name="msb"></param>
/// <param name="lsb"></param>
/// <returns></returns>
template <typename T>
inline std::string putb(const T value, const int msb = sizeof(T) * 8 - 1, const int lsb = 0)
{
	std::string str;
	u64 tempValue = (static_cast<u64>(value) >> lsb);

	for (int length = msb - lsb + 1; length; --length)
	{
		str += ((tempValue & (UINT64_C(1) << (length - 1))) ? "1" : "0");
	}

	return str;
}
