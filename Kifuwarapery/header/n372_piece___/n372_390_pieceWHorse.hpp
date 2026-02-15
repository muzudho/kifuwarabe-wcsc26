#pragma once

#include "../../src/lib_toybox_base/square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n160_board___/n160_120_bishopAttackBb.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n372_piece___/n372_070_PieceAbstract.hpp"


/// <summary>
/// 後手馬。
/// </summary>
class PieceWHorse : public PieceAbstract {


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
		bannedKingToBB |= g_bishopAttackBb.GetControllBbToEdge(checkSq);
	}
};
