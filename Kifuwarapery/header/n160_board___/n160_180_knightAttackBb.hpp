#pragma once
#include "n160_100_bitboard.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　桂の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 桂ビットボード
/// </summary>
class KnightAttackBb {


private:


	/// <summary>
	/// 
	/// </summary>
	Bitboard m_controllBb_[g_COLOR_NUM][SquareNum];

	/// <summary>
	/// 
	/// </summary>
	Bitboard m_knightCheckTable_[g_COLOR_NUM][SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	void initialize_10a170b_knightAttacks();


	/// <summary>
	/// 
	/// </summary>
	void initialize_10a260b_checkTableKnight();


	/// <summary>
	/// 利きビットボード取得
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetControllBb(const Color c, const Square sq) const {
		return this->m_controllBb_[c][sq];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard KnightCheckTable(const Color c, const Square sq) const {
		return this->m_knightCheckTable_[c][sq];
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern KnightAttackBb g_knightAttackBb;
