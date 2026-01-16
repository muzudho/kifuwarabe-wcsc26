#pragma once
#include "n160_100_bitboard.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　［飛車、角の元位置］と、［その利き］の２点のビットボード（＾～＾）？
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// ［飛車、角の元位置］と、［その利き］の２点のビットボード（＾～＾）？
/// </summary>
class BetweenBb
{


private:


	/// <summary>
	/// 
	/// </summary>
	Bitboard m_betweenBB_[SquareNum][SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	void Initialize();


	/// <summary>
	/// sq1, sq2 の間(sq1, sq2 は含まない)のビットが立った Bitboard
	/// </summary>
	/// <param name="sq1"></param>
	/// <param name="sq2"></param>
	/// <returns></returns>
	inline Bitboard GetBetweenBB(const Square sq1, const Square sq2) const
	{
		return this->m_betweenBB_[sq1][sq2];
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern BetweenBb g_betweenBb;
