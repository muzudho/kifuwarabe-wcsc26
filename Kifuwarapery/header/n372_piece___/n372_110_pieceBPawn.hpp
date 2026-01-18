#pragma once

#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n372_piece___/n372_070_PieceAbstract.hpp"


/// <summary>
/// 先手歩
/// </summary>
class PieceBPawn : public PieceAbstract {


public:


	/// <summary>
	/// 歩、桂馬で王手したときは、どこへ逃げても、その駒で取られることはない。
	/// よって、ここでは何もしない。
	/// </summary>
	/// <param name="bannedKingToBB"></param>
	/// <param name="pos"></param>
	/// <param name="checkSq"></param>
	/// <param name="ksq"></param>
	void MakeBanned2KingTo(Bitboard& bannedKingToBB, const Position& pos, const Square checkSq, const Square ksq
		) const override {
		assert(pos.GetPiece(checkSq) == N01_BPawn || pos.GetPiece(checkSq) == N03_BKnight);
	}
};

