#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../src/lib_toybox_base/square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"


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
