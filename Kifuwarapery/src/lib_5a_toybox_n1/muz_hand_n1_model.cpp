#include "muz_hand_n1_model.hpp"


// ========================================
// フィールド
// ========================================


/// <summary>
/// 
/// </summary>
const int MuzHandN1Model::m_HandPieceShiftBits[HandPieceNum] = {
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
u32 MuzHandN1Model::Value() const
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
void MuzHandN1Model::OrEqual(const int num, const HandPiece handPiece)
{
	m_value_ |= num << m_HandPieceShiftBits[handPiece];
}
