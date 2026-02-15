#pragma once

#include "../../src/lib_toybox_base/square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n372_piece___/n372_070_PieceAbstract.hpp"


/// <summary>
/// 後手の歩
/// </summary>
class PieceWPawn : public PieceAbstract {


public:


	/// <summary>
	///		<pre>
	/// 歩、桂馬で王手したときは、どこへ逃げても、その駒で取られることはない。
	/// よって、ここでは何もしない。
	///		</pre>
	/// </summary>
	/// <param name="bannedKingToBB"></param>
	/// <param name="pos"></param>
	/// <param name="checkSq"></param>
	/// <param name="ksq"></param>
	void MakeBanned2KingTo(Bitboard& bannedKingToBB, const Position& pos, const Square checkSq, const Square ksq
		) const override {
		assert(
			pos.GetPiece(checkSq) == N17_WPawn ||
			pos.GetPiece(checkSq) == N19_WKnight
			);
	}
};
