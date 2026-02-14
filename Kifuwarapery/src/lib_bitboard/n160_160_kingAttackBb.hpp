#pragma once
#include "n160_100_bitboard.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　玉の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 玉の利きビットボード
/// </summary>
const class KingAttackBb  {


private:


	/// <summary>
	/// メモリ節約の為、1次元配列にして無駄が無いようにしている。
	/// TODO: const にしたい。
	/// </summary>
	Bitboard m_controllBb_[SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	void initialize_10a130b_kingAttacks();


	/// <summary>
	/// Bitboard で直接利きを返す関数。
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetControllBb(const Square sq) const {
		return this->m_controllBb_[sq];
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern KingAttackBb g_kingAttackBb;
