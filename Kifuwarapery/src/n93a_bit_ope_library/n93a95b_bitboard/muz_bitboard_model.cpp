//
// 📄 局面の状態を表すクラス
//
#include "muz_bitboard_model.hpp"


// ========================================
// アクセッサ
// ========================================


void MuzBitboardModel::SetPiece(const Piece piece, const Square sq)
{
	// XXX: 通常の盤への駒配置は、別のクラスで行ってくれだぜ（＾～＾）

	const Color c = ConvPiece::TO_COLOR10(piece);
	const PieceType pt = ConvPiece::TO_PIECE_TYPE10(piece);

	// TODO: 駒の配置を表すビットボードを更新
	//g_setMaskBb.AddBit(&this->m_BB_ByPiecetype_[pt], sq);
	//g_setMaskBb.AddBit(&this->m_BB_ByColor_[c], sq);
	//g_setMaskBb.AddBit(&this->m_BB_ByPiecetype_[PieceType::N00_Occupied], sq);
}


// ========================================
// 主要メソッド
// ========================================
