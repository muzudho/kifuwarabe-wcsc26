#pragma once
#include "../n080_common__/n080_084_cacheLineSize.hpp"


//────────────────────────────────────────────────────────────────────────────────
// プリフェッチ
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
///		<pre>
/// プリフェッチ
/// 
///		- Stockfish ほとんどそのまま
///		</pre>
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="addr"></param>
template <typename T>
inline void prefetch(T* addr)
{
#if defined HAVE_SSE2 || defined HAVE_SSE4
#if defined(__INTEL_COMPILER)
	// これでプリフェッチが最適化で消えるのを防げるらしい。
	__asm__("");
#endif

	// 最低でも sizeof(T) のバイト数分をプリフェッチする。
	// Stockfish は TTCluster が 64byte なのに、なぜか 128byte 分 prefetch しているが、
	// 必要無いと思う。
	char* charAddr = reinterpret_cast<char*>(addr);
#if defined(__INTEL_COMPILER) || defined(_MSC_VER)
	Unroller<(sizeof(T) + CacheLineSize - 1) / CacheLineSize>()([&](const int) {
		// 1キャッシュライン分(64byte)のプリフェッチ。
		_mm_prefetch(charAddr, _MM_HINT_T0);
		charAddr += CacheLineSize;
		});
#else
	Unroller<(sizeof(T) + CacheLineSize - 1) / CacheLineSize>()([&](const int) {
		// 1キャッシュライン分(64byte)のプリフェッチ。
		__builtin_prefetch(charAddr);
		charAddr += CacheLineSize;
		});
#endif
#else
	// SSE が使えない時は、_mm_prefetch() とかが使えないので、prefetch無しにする。
	addr = addr; // warning 対策
#endif
}
