#pragma once
#include "../n080_100_sysWorld/n080_088_mutex.hpp"


//────────────────────────────────────────────────────────────────────────────────
// エンディアン
//────────────────────────────────────────────────────────────────────────────────


#if 0
#include <boost/detail/endian.hpp>


/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="r"></param>
template <typename T>
inline void reverseEndian(T& r)
{
	u8* begin = reinterpret_cast<u8*>(&r);
	u8* IsEnd = reinterpret_cast<u8*>(&r) + sizeof(T);
	for (; begin < IsEnd; ++begin, --IsEnd)
	{
		std::swap(*begin, *(IsEnd - 1));
	}
}
#endif
