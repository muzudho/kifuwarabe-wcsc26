#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n113_piece___/n113_205_convHandPiece.hpp"
#include "../../src/lib_toybox_base/hand.hpp"


/// <summary>
/// 手駒のマスク
/// </summary>
const u32 MuzHandModel::m_HandPieceMask[HandPieceNum] = {
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
const u32 MuzHandModel::m_HandPieceOne[HandPieceNum] = {
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
/// <param name="handPiece"></param>
/// <returns></returns>
u32 MuzHandModel::NumOf(const HandPiece handPiece) const
{
	return (Value() & m_HandPieceMask[handPiece]) >> m_HandPieceShiftBits[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="handPiece"></param>
/// <returns></returns>
u32 MuzHandModel::Exists(const HandPiece handPiece) const
{
	return Value() & m_HandPieceMask[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="hand"></param>
/// <returns></returns>
u32 MuzHandModel::ExceptPawnExists(const MuzHandModel& hand)
{
	return hand.Value() & m_HandPieceExceptPawnMask;
}


/// <summary>
/// 
/// </summary>
/// <param name="handPiece"></param>
void MuzHandModel::PlusOne(const HandPiece handPiece)
{
	m_value_ += m_HandPieceOne[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="handPiece"></param>
void MuzHandModel::MinusOne(const HandPiece handPiece)
{
	m_value_ -= m_HandPieceOne[handPiece];
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
bool MuzHandModel::operator==(const MuzHandModel rhs) const
{
	return this->Value() == rhs.Value();
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
bool MuzHandModel::operator!=(const MuzHandModel rhs) const
{
	return this->Value() != rhs.Value();
}


/// <summary>
/// 
/// </summary>
/// <param name="ref"></param>
/// <returns></returns>
bool MuzHandModel::IsEqualOrSuperior(const MuzHandModel ref) const
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
