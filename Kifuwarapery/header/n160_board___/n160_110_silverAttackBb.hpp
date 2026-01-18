#pragma once
#include "../n160_board___/n160_100_bitboard.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　銀の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 銀の利きビットボード
/// </summary>
class SilverAttackBb {


private:


	/// <summary>
	/// 
	/// </summary>
	Bitboard m_controllBb_[g_COLOR_NUM][SquareNum];

	/// <summary>
	/// 
	/// </summary>
	Bitboard m_silverCheckTable_[g_COLOR_NUM][SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	void initialize_10a150b_silverAttacks();


	/// <summary>
	/// 
	/// </summary>
	void initialize_10a250b_checkTableSilver();


	/// <summary>
	/// 
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
	inline Bitboard SilverCheckTable(const Color c, const Square sq) const {
		return this->m_silverCheckTable_[c][sq];
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern SilverAttackBb g_silverAttackBb;
