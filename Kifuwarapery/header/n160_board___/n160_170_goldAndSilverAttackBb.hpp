#pragma once
#include "n160_100_bitboard.hpp"
#include "n160_110_silverAttackBb.hpp"
#include "n160_140_goldAttackBb.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　金と銀の利き
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 金と銀
/// </summary>
class GoldAndSilverAttackBb {


public:


	/// <summary>
	/// 前方3方向の位置のBitboard
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GoldAndSilverAttacks(const Color c, const Square sq) const {
		return g_goldAttackBb.GetControllBb(c, sq) & g_silverAttackBb.GetControllBb(c, sq);
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern const GoldAndSilverAttackBb g_goldAndSilverAttackBb;
