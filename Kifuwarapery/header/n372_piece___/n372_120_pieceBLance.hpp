#pragma once

#include "../../src/lib_toybox_base/square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n160_board___/n160_130_lanceAttackBb.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n372_piece___/n372_070_PieceAbstract.hpp"


/// <summary>
/// 先手香
/// </summary>
class PieceBLance : public PieceAbstract {


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
		bannedKingToBB |= g_lanceAttackBb.GetControllBbToEdge(Color::Black, checkSq);
	}

};
