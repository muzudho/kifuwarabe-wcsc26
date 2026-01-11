#pragma once

#include "n160_100_bitboard.hpp"


/// <summary>
/// 金の利きビットボード
/// </summary>
class GoldAttackBb {


private:


	/// <summary>
	/// 
	/// </summary>
	Bitboard m_controllBb_[g_COLOR_NUM][SquareNum];

	/// <summary>
	/// 
	/// </summary>
	Bitboard m_goldCheckTable_[g_COLOR_NUM][SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	void Initialize();

	/// <summary>
	/// チェック・テーブル
	/// </summary>
	void InitCheckTableGold();

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
	/// チェック・テーブル・ビットボード取得
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GoldCheckTable(const Color c, const Square sq) const {
		return this->m_goldCheckTable_[c][sq];
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern GoldAttackBb g_goldAttackBb;
