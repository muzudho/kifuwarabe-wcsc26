#include "muz_board_model.hpp"


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// マスにある駒を取得
/// </summary>
/// <param name="sq">マス番号</param>
/// <returns></returns>
const Piece MuzBoardModel::get_piece(const Square sq) const
{
	return this->piece_[sq];
}


/// <summary>
/// マスに駒を置く。
/// </summary>
void MuzBoardModel::set_piece(const Square sq, const Piece piece)
{
	this->piece_[sq] = piece;
}
