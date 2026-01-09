#include "../../header/n080_common__/n080_100_common.hpp"
#include "../../header/n113_piece___/n113_205_convHandPiece.hpp"
#include "../../header/n113_piece___/n113_500_hand.hpp"


/// <summary>
/// 
/// </summary>
const int Hand::m_HandPieceShiftBits[HandPieceNum] = {
	m_HPawnShiftBits,
	m_HLanceShiftBits,
	m_HKnightShiftBits,
	m_HSilverShiftBits,
	m_HGoldShiftBits,
	m_HBishopShiftBits,
	m_HRookShiftBits
};

/// <summary>
/// 手駒のマスク
/// </summary>
const u32 Hand::m_HandPieceMask[HandPieceNum] = {
	m_HPawnMask,
	m_HLanceMask,
	m_HKnightMask,
	m_HSilverMask,
	m_HGoldMask,
	m_HBishopMask,
	m_HRookMask
};


/// <summary>
/// 特定の種類の持ち駒を 1 つ増やしたり減らしたりするときに使用するテーブル
/// </summary>
const u32 Hand::m_HandPieceOne[HandPieceNum] = {
	1 << m_HPawnShiftBits,
	1 << m_HLanceShiftBits,
	1 << m_HKnightShiftBits,
	1 << m_HSilverShiftBits,
	1 << m_HGoldShiftBits,
	1 << m_HBishopShiftBits,
	1 << m_HRookShiftBits
};


/// <summary>
/// 
/// </summary>
/// <returns></returns>
u32 Hand::Value() const
{
	return this->m_value_;
}


/// <summary>
/// 
/// </summary>
/// <param name="handPiece"></param>
/// <returns></returns>
u32 Hand::NumOf(const HandPiece handPiece) const
{
	return (Value() & m_HandPieceMask[handPiece]) >> m_HandPieceShiftBits[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="handPiece"></param>
/// <returns></returns>
u32 Hand::Exists(const HandPiece handPiece) const
{
	return Value() & m_HandPieceMask[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="hand"></param>
/// <returns></returns>
u32 Hand::ExceptPawnExists(const Hand& hand)
{
	return hand.Value() & m_HandPieceExceptPawnMask;
}


/// <summary>
/// 
/// </summary>
/// <param name="num"></param>
/// <param name="handPiece"></param>
void Hand::OrEqual(const int num, const HandPiece handPiece)
{
	m_value_ |= num << m_HandPieceShiftBits[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="handPiece"></param>
void Hand::PlusOne(const HandPiece handPiece)
{
	m_value_ += m_HandPieceOne[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="handPiece"></param>
void Hand::MinusOne(const HandPiece handPiece)
{
	m_value_ -= m_HandPieceOne[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
bool Hand::operator==(const Hand rhs) const
{
	return this->Value() == rhs.Value();
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
bool Hand::operator!=(const Hand rhs) const
{
	return this->Value() != rhs.Value();
}


/// <summary>
/// 
/// </summary>
/// <param name="ref"></param>
/// <returns></returns>
bool Hand::IsEqualOrSuperior(const Hand ref) const
{
#if 0
	// 全ての駒が ref 以上の枚数なので、true
	return (ref.Exists<HKnight>() <= this->Exists<HKnight>()
		&& ref.Exists<HSilver>() <= this->Exists<HSilver>()
		&& ref.Exists<HGold  >() <= this->Exists<HGold  >()
		&& ref.Exists<HBishop>() <= this->Exists<HBishop>()
		&& ref.Exists<HRook  >() <= this->Exists<HRook  >());
#else
	// こちらは、同じ意味でより高速
	// ref の方がどれか一つでも多くの枚数の駒を持っていれば、Borrow の位置のビットが立つ。
	return ((this->Value() - ref.Value()) & m_BorrowMask) == 0;
#endif
}
