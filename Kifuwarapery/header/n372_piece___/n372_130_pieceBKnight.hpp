#pragma once

#include "../../src/lib_toybox_base/square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n372_piece___/n372_070_PieceAbstract.hpp"


/// <summary>
/// 先手桂馬
/// </summary>
class PieceBKnight : public PieceAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bannedKingToBB"></param>
	/// <param name="pos"></param>
	/// <param name="checkSq"></param>
	/// <param name="ksq"></param>
	void MakeBanned2KingTo(Bitboard& bannedKingToBB, const Position& pos, const Square checkSq, const Square ksq
		) const override {
		// 歩、桂馬で王手したときは、どこへ逃げても、その駒で取られることはない。
		// よって、ここでは何もしない。
		assert(pos.GetPiece(checkSq) == N01_BPawn || pos.GetPiece(checkSq) == N03_BKnight);
	}
};
