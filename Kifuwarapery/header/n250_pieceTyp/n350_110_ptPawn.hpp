#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_500_convSquare.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n130_100_boardBb_/n160_130_lanceAttackBb.hpp"
#include "../n130_100_boardBb_/n160_190_pawnAttackBb.hpp"
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
/// 盤上の歩の動き
/// </summary>
const static Move g_PTPAWN_ONBOARD_AS_MOVE = ConvMove::FROM_PIECETYPE_ONBOARD10(PieceType::N01_Pawn);

/// <summary>
/// 歩打の動き
/// </summary>
const static Move g_PTPAWN_DA_AS_MOVE = ConvMove::FROM_PIECETYPE_DA10(PieceType::N01_Pawn);


/// <summary>
/// ＰｉｅｃｅＴｙｐｅ：：Ｎ０１＿Ｐａｗｎ
/// </summary>
class PtPawn : public IPieceType {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual Move AsMove() const override {
		return g_PTPAWN_ONBOARD_AS_MOVE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ptEvent"></param>
	/// <returns></returns>
	Bitboard GetAttacks2From(const PieceTypeEvent& ptEvent) const override {
		return g_pawnAttackBb.GetControllBb(ptEvent.m_c, ptEvent.m_sq);
	}


	/// <summary>
	/// pin は省かない。	//FORCE_INLINE
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
		moveStackList->m_move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_CaptureCategory(
			this->AsMove(),
			from,
			to,
			pos
		);

		if (
				ConvSquare::canPromote_n10<Color::White>(ConvSquare::toRank_n10(to))
				|
				ConvSquare::canPromote_n10<Color::White>(ConvSquare::toRank_n10(from))
		){
			MakePromoteMove::APPEND_PROMOTE_FLAG(moveStackList->m_move);
		}

		moveStackList++;
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

		moveStackList->m_move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_CaptureCategory(
			this->AsMove(),
			from,
			to,
			pos
			);

		if (
			ConvSquare::canPromote_n10<Color::Black>(ConvSquare::toRank_n10(to))
			|
			ConvSquare::canPromote_n10<Color::Black>(ConvSquare::toRank_n10(from))
			) {
			MakePromoteMove::APPEND_PROMOTE_FLAG(moveStackList->m_move);
		}

		moveStackList++;
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
