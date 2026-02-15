#pragma once
#include "../../src/lib_toybox_base/square.hpp"
#include "../n105_120_square__/n105_120_300_direction.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ２つのマスの位置関係
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// ２つのマスの位置関係
/// </summary>
class SquareRelation {


private:


	/// <summary>
	/// 2つの位置関係のテーブル
	/// </summary>
	Direction m_squareRelation_[SquareNum][SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	void initialize_10a190b_squareRelations();


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq1"></param>
	/// <param name="sq2"></param>
	/// <returns></returns>
	inline Direction GetSquareRelation(const Square sq1, const Square sq2) const {
		return this->m_squareRelation_[sq1][sq2];
	}


	/// <summary>
	/// from, to, ksq が 縦横斜めの同一ライン上にあれば true を返す。
	/// </summary>
	/// <typeparam name="FROM_KSQ_NEVER_BE_DIRECMISC"></typeparam>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="ksq"></param>
	/// <returns></returns>
	template <bool FROM_KSQ_NEVER_BE_DIRECMISC>
	inline bool IsAligned(const Square from, const Square to, const Square ksq) const {

		const Direction direc = SquareRelation::GetSquareRelation(from, ksq);

		if (FROM_KSQ_NEVER_BE_DIRECMISC) {
			assert(direc != N00_DirecMisc);
			return (direc == SquareRelation::GetSquareRelation(from, to));
		}
		else {
			return (direc != N00_DirecMisc && direc == SquareRelation::GetSquareRelation(from, to));
		}
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern SquareRelation g_squareRelation;
