#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../../src/lib_toybox_base/square.hpp"
#include "../../src/lib_toybox_base/piece_type.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n160_board___/n160_230_setMaskBb.hpp"
#include "../n165_movStack/n165_300_moveType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "n350_030_makePromoteMove.hpp"
#include "n350_040_ptEvent.hpp"
#include "n350_045_pieceTypeSeeEvent.hpp"
#include "n350_070_ptAbstract.hpp"


// PieceType::N16_GoldHorseDragon


/// <summary>
///		<pre>
/// （＾ｑ＾）金馬龍の動きをするプログラムだぜ☆
///		</pre>
/// </summary>
class PtGoldHorseDragon : public PtAbstract {


public:


	/// <summary>
	/// </summary>
	virtual Move AsMove() const override {
		UNREACHABLE;
        return g_MOVE_NONE;	// 使わない☆
	}

	Bitboard GetAttacks2From(const PieceTypeEvent& ptEvent) const override {
		return g_nullBitboard;
	}

	/// <summary>
	/// pin は省かない
	/// FORCE_INLINE
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	void Generate2RecaptureMoves_usWhite(
		MoveStack* moveStackList,
		const Position& pos,
		const Square from,
		const Square to
		) const override {
		return;
	}


	/// <summary>
	/// FORCE_INLINE
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	void Generate2RecaptureMoves_usBlack(
		MoveStack* moveStackList,
		const Position& pos,
		const Square from,
		const Square to
		) const override {
		return;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="occupied"></param>
	/// <param name="attackers"></param>
	/// <param name="nextPT"></param>
	/// <param name="ptsEvent"></param>
	/// <returns></returns>
	PieceType AppendToNextAttackerAndTryPromote(
		Bitboard& occupied,
		Bitboard& attackers,
		PieceType nextPT,
		const PieceTypeSeeEvent ptsEvent
		) const override;
};
