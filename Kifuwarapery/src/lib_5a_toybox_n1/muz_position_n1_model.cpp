//
// 📄 局面の状態を表すクラス
//
#include "muz_position_n1_model.hpp"


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// 
/// </summary>
/// <param name="ply"></param>
void MuzPositionN1Model::SetStartPosPly(const Ply ply)
{
	this->m_gamePly_ = ply;
}


/// <summary>
/// 何手目か
/// </summary>
/// <returns></returns>
Ply MuzPositionN1Model::GetGamePly()
{
	return this->m_gamePly_;
}


/// <summary>
/// 手番を取得
/// </summary>
/// <returns></returns>
Color MuzPositionN1Model::GetTurn()
{
	return this->m_turn_;
}


/// <summary>
/// 
/// </summary>
/// <param name="sq"></param>
/// <returns></returns>
Piece MuzPositionN1Model::GetPiece(const Square sq)
{
	return this->m_piece_[sq];
}


void MuzPositionN1Model::SetPiece(const Piece piece, const Square sq)
{
	this->m_piece_[sq] = piece;
}
