#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n160_boardBb_/n160_100_bitboard.hpp"
#include "../n160_boardBb_/n160_230_setMaskBb.hpp"
#include "../n165_movStack/n165_300_moveType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "n350_040_ptEvent.hpp"
#include "n350_045_pieceTypeSeeEvent.hpp"
#include "n350_070_ptAbstract.hpp"


/// <summary>
/// 盤上の成り駒の動き
/// </summary>
const static Move g_PTPROMOTE_AS_MOVE = ConvMove::FROM_PIECETYPE_ONBOARD10(PieceType::PTPromote);


/// <summary>
/// PieceType::PTPromote;
/// </summary>
class PtPromote : public PtAbstract {


public:


	/// <summary>
	///
	/// </summary>
	/// <returns></returns>
	virtual Move AsMove() const override {
		return g_PTPROMOTE_AS_MOVE;
	}


	/// <summary>
	///
	/// </summary>
	/// <param name="ptEvent"></param>
	/// <returns></returns>
	Bitboard GetAttacks2From(const PieceTypeEvent& ptEvent) const override {
		return g_nullBitboard;
	}

	/// <summary>
	/// pin は省かない。　FORCE_INLINE
	/// </summary>
	/// <param name="moveStackList"></param>
	void Generate2RecaptureMoves_usWhite(
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
	/// <param name="moveStackList"></param>
	void Generate2RecaptureMoves_usBlack(
		MoveStack* moveStackList,
		const Position& pos,
		const Square from,
		const Square to
		) const override {
		return;
	}


	/// <summary>
	/// </summary>
	/// <param name="occupied"></param>
	PieceType AppendToNextAttackerAndTryPromote(
		Bitboard& occupied,
		Bitboard& attackers,
		PieceType nextPT,
		const PieceTypeSeeEvent ptsEvent
		) const override {
		PieceType PT = PieceType::PTPromote;

		UNREACHABLE;

		// ����ȊO�̋��ނ́A���̂܂ܕԂ���
		return PT;
	}
};
