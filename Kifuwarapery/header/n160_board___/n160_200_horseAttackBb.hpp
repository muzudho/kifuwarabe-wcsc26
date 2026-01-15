#pragma once
#include "n160_100_bitboard.hpp"
#include "n160_120_bishopAttackBb.hpp"
#include "n160_160_kingAttackBb.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　馬の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 馬
/// </summary>
class HorseAttackBb
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
		return g_bishopAttackBb.BishopAttack(thisBitboard, sq) | g_kingAttackBb.GetControllBb(sq);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetControllBbToEdge(const Square sq) const
	{
		return g_bishopAttackBb.GetControllBbToEdge(sq) | g_kingAttackBb.GetControllBb(sq);
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern const HorseAttackBb g_horseAttackBb;
