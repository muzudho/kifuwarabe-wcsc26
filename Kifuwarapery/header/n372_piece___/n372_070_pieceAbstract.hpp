#pragma once

#include "../n080_common__/n080_100_common.hpp"
#include "../n110_square__/n110_100_square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n220_position/n220_650_position.hpp"


/// <summary>
/// 駒
/// </summary>
class PieceAbstract{


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bannedKingToBB"></param>
	/// <param name="pos"></param>
	/// <param name="checkSq"></param>
	/// <param name="ksq"></param>
	virtual void MakeBanned2KingTo(
		Bitboard& bannedKingToBB, const Position& pos, const Square checkSq, const Square ksq
	) const = 0;
};
