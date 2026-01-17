#pragma once

#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n130_100_boardBb_/n160_130_lanceAttackBb.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n372_banKing_/n372_070_PieceAbstract.hpp"


/// <summary>
/// 先手香
/// </summary>
class PieceBLance : public IKingBannable {


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
