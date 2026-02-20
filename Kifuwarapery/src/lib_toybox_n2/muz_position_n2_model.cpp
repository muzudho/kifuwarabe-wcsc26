#include "muz_position_n2_model.hpp"


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
MuzHandN1Model MuzPositionN2Model::GetHand(const Color c) const
{
	return this->m_hand_models_[c];
}


/// <summary>
/// 
/// </summary>
/// <param name="piece"></param>
/// <param name="num"></param>
void MuzPositionN2Model::SetHand(const Piece piece, const int num)
{
	const Color c = ConvPiece::TO_COLOR10(piece);
	const PieceType pt = ConvPiece::TO_PIECE_TYPE10(piece);
	const HandPiece hp = ConvHandPiece::FromPieceType(pt);
	this->SetHand(hp, c, num);
}


/// <summary>
/// 
/// </summary>
/// <param name="hp"></param>
/// <param name="c"></param>
/// <param name="num"></param>
void MuzPositionN2Model::SetHand(const HandPiece hp, const Color c, const int num)
{
	this->m_hand_models_[c].OrEqual(num, hp);
}
