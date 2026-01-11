#pragma once

#include "../n110_square__/n110_100_square.hpp"


/// <summary>
/// 
/// </summary>
class SquareDistance {


private:


	/// <summary>
	/// 何かの駒で一手で行ける位置関係についての距離のテーブル。桂馬の位置は距離1とする。
	/// </summary>
	int m_squareDistance_[SquareNum][SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq1"></param>
	/// <param name="sq2"></param>
	/// <param name="value"></param>
	inline void SetValue(const Square sq1, const Square sq2, int value) {
		this->m_squareDistance_[sq1][sq2] = value;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq1"></param>
	/// <param name="sq2"></param>
	/// <returns></returns>
	inline int GetSquareDistance(const Square sq1, const Square sq2) const {
		return this->m_squareDistance_[sq1][sq2];
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern SquareDistance g_squareDistance;
