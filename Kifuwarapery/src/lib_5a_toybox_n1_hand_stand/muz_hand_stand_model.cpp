#include "muz_hand_stand_model.hpp"


// ========================================
// フィールド
// ========================================


/// <summary>
/// 
/// </summary>
const int MuzHandStandModel::m_HandPieceShiftBits[HandPieceNum] = {
	m_HPawnShiftBits,
	m_HLanceShiftBits,
	m_HKnightShiftBits,
	m_HSilverShiftBits,
	m_HGoldShiftBits,
	m_HBishopShiftBits,
	m_HRookShiftBits
};


// ========================================
// アクセッサー
// ========================================


/// <summary>
/// 
/// </summary>
/// <returns></returns>
u32 MuzHandStandModel::Value() const
{
	return this->m_value_;
}


// ========================================
// 主要メソッド
// ========================================


/// <summary>
/// 
/// </summary>
/// <param name="num"></param>
/// <param name="handPiece"></param>
void MuzHandStandModel::OrEqual(const int num, const HandPiece handPiece)
{
	m_value_ |= num << m_HandPieceShiftBits[handPiece];
}
