//
// 📄 局面の状態を表すクラス
//
#include "muz_position_base_model.hpp"


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// 何手目か
/// </summary>
/// <returns></returns>
Ply MuzPositionBaseModel::GetGamePly() const
{
	return this->m_gamePly_;
}


/// <summary>
/// 
/// </summary>
/// <param name="ply"></param>
void MuzPositionBaseModel::SetStartPosPly(const Ply ply)
{
	this->m_gamePly_ = ply;
}


/// <summary>
/// 手番を取得
/// </summary>
/// <returns></returns>
Color MuzPositionBaseModel::GetTurn() const
{
	return this->m_turn_;
}


/// <summary>
/// 
/// </summary>
/// <param name="sq"></param>
/// <returns></returns>
Piece MuzPositionBaseModel::GetPiece(const Square sq) const
{
	return this->m_piece_[sq];
}


/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
Hand MuzPositionBaseModel::GetHand(const Color c) const
{
	return this->m_hand_[c];
}
