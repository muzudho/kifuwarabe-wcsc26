#pragma once

#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n372_banKing_/n372_070_PieceAbstract.hpp"


/// <summary>
/// 後手の桂馬
/// </summary>
class PieceWKnight : public PieceAbstract {


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
