#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n130_100_boardBb_/n160_230_setMaskBb.hpp"
#include "../n165_movStack/n165_300_movegenType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "n350_030_makePromoteMove.hpp"
#include "n350_040_ptEvent.hpp"
#include "n350_045_pieceTypeSeeEvent.hpp"
#include "n350_070_IPieceType.hpp"


/// <summary>
/// 駒が存在していることを表す駒種類
/// </summary>
const static Move g_PTOCCUPIED_AS_MOVE = ConvMove::FROM_PIECETYPE_ONBOARD10(PieceType::N00_Occupied);


/// <summary>
/// PieceType::N00_Occupied
/// </summary>
class PtOccupied : public IPieceType {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual Move AsMove() const override {
		return g_PTOCCUPIED_AS_MOVE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ptEvent"></param>
	/// <returns></returns>
	Bitboard GetAttacks2From(const PieceTypeEvent& ptEvent) const override {
		return Bitboard::CreateAllZeroBB();
	}


	/// <summary>
	/// FORCE_INLINE
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	void Generate2RecaptureMoves_usWhite(
		DeliciousBanana* moveStackList,
		const Position& pos,
		const Square from,
		const Square to
	) const override {
		// 最適化の為のダミー
		assert(false);
	}


	/// <summary>
	/// FORCE_INLINE
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	void Generate2RecaptureMoves_usBlack(
		DeliciousBanana* moveStackList,
		const Position& pos,
		const Square from,
		const Square to
		) const override {
		// 最適化の為のダミー
		assert(false);
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
		) const override {
		PieceType PT = PieceType::N00_Occupied;

		UNREACHABLE;

		// それ以外の駒種類は、そのまま返す☆
		return PT;
	}
};
