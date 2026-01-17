#pragma once
#include "n160_100_bitboard.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　歩の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 歩ビットボード
/// </summary>
class PawnAttackBb
{


private:


	/// <summary>
	/// 
	/// </summary>
	Bitboard m_controllBb_[g_COLOR_NUM][SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	void initialize_app10();


	/// <summary>
	/// 利きビットボード取得
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetControllBb(const Color c, const Square sq) const
	{
		return this->m_controllBb_[c][sq];
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern PawnAttackBb g_pawnAttackBb;
