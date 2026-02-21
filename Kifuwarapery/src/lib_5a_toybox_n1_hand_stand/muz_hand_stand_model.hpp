#pragma once

#include "../lib_1a_cpp/int.hpp"
#include "hand_piece.hpp"

/// <summary>
///		<pre>
/// 駒台（持ち駒）
///		</pre>
/// </summary>
class MuzHandStandModel
{


public:


	// ========================================
	// 生成／破棄
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	MuzHandStandModel() {}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="v"></param>
	explicit MuzHandStandModel(u32 v) : m_value_(v) {}


	// ========================================
	// フィールド
	// ========================================


private:


	static const int m_HandPieceShiftBits[HandPieceNum];
	static const int m_HPawnShiftBits = 0;
	static const int m_HLanceShiftBits = 6;
	static const int m_HKnightShiftBits = 10;
	static const int m_HSilverShiftBits = 14;
	static const int m_HGoldShiftBits = 18;
	static const int m_HBishopShiftBits = 22;
	static const int m_HRookShiftBits = 25;


protected:



	/// <summary>
	/// 
	/// </summary>
	u32 m_value_;


public:
	// ========================================
	// アクセッサー
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	u32 Value() const;


	// ========================================
	// 主要メソッド
	// ========================================


	/// <summary>
	/// num が int だけどまあ良いか。
	/// </summary>
	/// <param name="num"></param>
	/// <param name="handPiece"></param>
	void OrEqual(const int num, const HandPiece handPiece);
};
