#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_500_convSquare.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n160_board___/n160_150_rookAttackBb.hpp"
#include "../n160_board___/n160_230_setMaskBb.hpp"
#include "../n165_movStack/n165_300_moveType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "n350_030_makePromoteMove.hpp"
#include "n350_040_ptEvent.hpp"
#include "n350_045_pieceTypeSeeEvent.hpp"
#include "n350_070_ptAbstract.hpp"


/// <summary>
/// 盤上の飛車
/// </summary>
const static Move g_PTROOK_ONBOARD_AS_MOVE = ConvMove::FROM_PIECETYPE_ONBOARD10(PieceType::N06_Rook);

/// <summary>
/// 飛打
/// </summary>
const static Move g_PTROOK_DA_AS_MOVE = ConvMove::FROM_PIECETYPE_DA10(PieceType::N06_Rook);


/// <summary>
/// ＰｉｅｃｅＴｙｐｅ：：Ｎ０６＿Ｒｏｏｋ
/// </summary>
class PtRook : public PtAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual Move AsMove() const override {
		return g_PTROOK_ONBOARD_AS_MOVE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ptEvent"></param>
	/// <returns></returns>
	Bitboard GetAttacks2From(const PieceTypeEvent& ptEvent) const override {
		return g_rookAttackBb.GetControllBb(ptEvent.m_occupied, ptEvent.m_sq);
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
			this->AsMove(), from, to, pos);

		if (
			ConvSquare::CAN_PROMOTE10<Color::White>(ConvSquare::TO_RANK10(to))
			|
			ConvSquare::CAN_PROMOTE10<Color::White>(ConvSquare::TO_RANK10(from))
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
			this->AsMove(), from, to, pos);

		if (
			ConvSquare::CAN_PROMOTE10<Color::Black>(ConvSquare::TO_RANK10(to))
			|
			ConvSquare::CAN_PROMOTE10<Color::Black>(ConvSquare::TO_RANK10(from))
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
