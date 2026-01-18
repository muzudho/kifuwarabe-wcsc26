#pragma once
#include "n160_100_bitboard.hpp"
#include "n160_150_rookAttackBb.hpp"
#include "n160_160_kingAttackBb.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　竜の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 竜
/// </summary>
class DragonAttackBb
{


public:


	/// <summary>
	/// 利きビットボード取得
	/// </summary>
	/// <param name="thisBitboard"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetControllBb(const Bitboard& thisBitboard, const Square sq) const
	{
		return g_rookAttackBb.GetControllBb(thisBitboard, sq) | g_kingAttackBb.GetControllBb(sq);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetControllBbToEdge(const Square sq) const
	{
		return g_rookAttackBb.GetControllBbToEdge(sq) | g_kingAttackBb.GetControllBb(sq);
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern const DragonAttackBb g_dragonAttackBb;
