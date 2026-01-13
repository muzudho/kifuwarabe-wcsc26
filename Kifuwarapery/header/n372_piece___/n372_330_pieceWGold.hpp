#pragma once

#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n160_board___/n160_140_goldAttackBb.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n372_piece___/n372_070_PieceAbstract.hpp"


/// <summary>
/// 後手金
/// </summary>
class PieceWGold : public PieceAbstract {


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
		bannedKingToBB |= g_goldAttackBb.GetControllBb(Color::White, checkSq);
	}
};
