#pragma once
#include "n160_100_bitboard.hpp"
#include "n160_120_bishopAttackBb.hpp"
#include "n160_150_rookAttackBb.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　飛車と角の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 
/// </summary>
class QueenAttackBb {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="thisBitboard"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetControllBb(const Bitboard& thisBitboard, const Square sq) const
	{
		return g_rookAttackBb.GetControllBb(thisBitboard, sq) | g_bishopAttackBb.BishopAttack(thisBitboard, sq);
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern const QueenAttackBb g_queenAttackBb;
