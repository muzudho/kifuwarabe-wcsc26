#include "muz_board_model.hpp"


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// マスにある駒を取得
/// </summary>
/// <param name="sq">マス番号</param>
/// <returns></returns>
Piece MuzBoardModel::get_piece(const Square sq)
{
	return this->piece_[sq];
}


/// <summary>
/// マスに駒を置く。
/// </summary>
void MuzBoardModel::set_piece(const Piece piece, const Square sq)
{
	this->piece_[sq] = piece;
}
