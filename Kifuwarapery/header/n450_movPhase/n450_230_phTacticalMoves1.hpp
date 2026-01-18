#pragma once


#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n407_moveGen_/n407_800_moveGenerator200.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "n450_070_movePhaseAbstract.hpp"


class NextmoveEvent;


/// <summary>
/// 
/// </summary>
class PhTacticalMoves1 : public MovePhaseAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="resultMove"></param>
	/// <param name="nmEvent"></param>
	/// <returns></returns>
	bool GetNext2Move(Move& resultMove, NextmoveEvent& nmEvent) const override {
		DeliciousBanana* pMoveStack = UtilMoveStack::PickBest(nmEvent.GetCurrMove(), nmEvent.GetLastMove());
		nmEvent.IncrementCurMove();

		// todo: see が確実に駒打ちじゃないから、内部で駒打ちか判定してるのは少し無駄。
		if (pMoveStack->m_move != nmEvent.GetTranspositionTableMove() && nmEvent.GetCaptureThreshold() <
			(
				nmEvent.GetPos().getTurn()==Color::Black
				?
				nmEvent.GetPos().GetSee1<Color::Black,Color::White>(pMoveStack->m_move)
				:
				nmEvent.GetPos().GetSee1<Color::White,Color::Black>(pMoveStack->m_move)
			)			
		) {
			resultMove = pMoveStack->m_move;
			return true;
		}
		return false;
	};


	/// <summary>
	/// 
	/// </summary>
	/// <param name="nmEvent"></param>
	void GoNext2Phase(NextmoveEvent& nmEvent) override {
		nmEvent.SetLastMove(g_moveGenerator200.generateDeliciousBanana_n2(N03_CapturePlusPro,nmEvent.GetCurrMove(), nmEvent.GetPos()));
		nmEvent.ScoreCaptures();
	}
};


/// <summary>
/// 
/// </summary>
extern PhTacticalMoves1 g_phTacticalMoves1;
