#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n220_position/n220_650_position.hpp"


/// <summary>
/// 駒
/// </summary>
class PieceAbstract{


public:


	/// <summary>
	/// インターフェースのメソッド
	/// </summary>
	/// <param name="bannedKingToBB"></param>
	/// <param name="pos"></param>
	/// <param name="checkSq"></param>
	/// <param name="ksq"></param>
	virtual void MakeBanned2KingTo(
		Bitboard& bannedKingToBB, const Position& pos, const Square checkSq, const Square ksq
	) const = 0;
};
