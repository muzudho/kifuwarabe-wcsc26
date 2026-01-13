#pragma once
#include "../n110_square__/n110_200_rank.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 段の操作
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 段の操作
/// </summary>
class ConvRank {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="r"></param>
	/// <returns></returns>
	static inline bool CONTAINS_OF10(const Rank r) { return (0 <= r) && (r < RankNum); }


	/// <summary>
	/// 上下変換
	/// </summary>
	/// <param name="r"></param>
	/// <returns></returns>
	static inline constexpr Rank INVERSE10(const Rank r) { return RankNum - 1 - r; }


	/// <summary>
	/// todo: アルファベットが辞書順に並んでいない処理系があるなら対応すること。
	/// rank は 0～8という想定☆
	/// </summary>
	/// <param name="r"></param>
	/// <returns></returns>
	static inline char TO_CHAR_USI10(const Rank r) {
		// 処理系をコンパイル時に確認だぜ☆（＾ｑ＾）
		static_assert('a' + 1 == 'b', "");
		static_assert('a' + 2 == 'c', "");
		static_assert('a' + 3 == 'd', "");
		static_assert('a' + 4 == 'e', "");
		static_assert('a' + 5 == 'f', "");
		static_assert('a' + 6 == 'g', "");
		static_assert('a' + 7 == 'h', "");
		static_assert('a' + 8 == 'i', "");
		return 'a' + r;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="r"></param>
	/// <returns></returns>
	static inline char TO_CHAR_CSA10(const Rank r) { return '1' + r; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	static inline Rank FROM_CHAR_CSA10(const char c) { return static_cast<Rank>(c - '1'); }

	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	static inline Rank FROM_CHAR_USI10(const char c) { return static_cast<Rank>(c - 'a'); }
};
