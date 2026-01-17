#pragma once
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　銀の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
///		<pre>
/// 銀の利きビットボード
///		</pre>
/// </summary>
class SilverAttackBb {


private:


	/// <summary>
	/// 利き？
	/// </summary>
	Bitboard m_controllBb_[g_COLOR_NUM][SquareNum];

	/// <summary>
	/// 王手？
	/// </summary>
	Bitboard m_silverCheckTable_[g_COLOR_NUM][SquareNum];


public:


	/// <summary>
	/// 初期化
	/// </summary>
	void initialize_app10();


	/// <summary>
	/// 銀で王手ビットボード初期化
	/// </summary>
	void initCheckTableSilver_app10();


	/// <summary>
	/// 利き
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetControllBb(const Color c, const Square sq) const
	{
		return this->m_controllBb_[c][sq];
	}


	/// <summary>
	/// 王手
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard SilverCheckTable(const Color c, const Square sq) const
	{
		return this->m_silverCheckTable_[c][sq];
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern SilverAttackBb g_silverAttackBb;
