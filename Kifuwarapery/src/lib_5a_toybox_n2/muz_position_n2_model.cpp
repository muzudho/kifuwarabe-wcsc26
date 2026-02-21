#include "muz_position_n2_model.hpp"


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
MuzHandStandModel MuzPositionN2Model::GetHandStand(const Color c) const
{
	return this->m_hand_stands_[c];
}


/// <summary>
/// 
/// </summary>
/// <param name="piece"></param>
/// <param name="num"></param>
void MuzPositionN2Model::SetHandPiece(const Piece piece, const int num)
{
	const Color c = ConvPiece::TO_COLOR10(piece);
	const PieceType pt = ConvPiece::TO_PIECE_TYPE10(piece);
	const HandPiece hp = ConvHandPiece::FromPieceType(pt);
	this->SetHandPiece(c, hp, num);
}


/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <param name="hp"></param>
/// <param name="num"></param>
void MuzPositionN2Model::SetHandPiece(const Color c, const HandPiece hp, const int num)
{
	this->m_hand_stands_[c].OrEqual(num, hp);
}
