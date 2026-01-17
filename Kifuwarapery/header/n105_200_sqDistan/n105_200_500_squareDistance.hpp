#pragma once
#include "../n105_120_square__/n105_120_100_square.hpp"


/// <summary>
///		<pre>
/// マス距離
/// 
///		- 評価関数で使う
///		</pre>
/// </summary>
class TwoSquaresDistanceKind {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq1"></param>
	/// <param name="sq2"></param>
	/// <param name="value"></param>
	inline void SetDistanceKind(const Square sq1, const Square sq2, int distanceKind) {
		this->m_twoSquaresDistance_[sq1][sq2] = distanceKind;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq1"></param>
	/// <param name="sq2"></param>
	/// <returns></returns>
	inline int GetDistanceKind(const Square sq1, const Square sq2) const {
		return this->m_twoSquaresDistance_[sq1][sq2];
	}


private:


	/// <summary>
	///		<pre>
	/// 何かの駒で一手で行ける位置関係についての距離のテーブル。桂馬の位置は距離1とする。
	/// 
	///		- `sq0 - sq1` みたいな非幾何学的な数（区分？）になってるが、いいのかだぜ（＾～＾）？
	///		<pre>
	/// </summary>
	int m_twoSquaresDistance_[SquareNum][SquareNum];


};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern TwoSquaresDistanceKind g_twoSquaresDistanceKind;
