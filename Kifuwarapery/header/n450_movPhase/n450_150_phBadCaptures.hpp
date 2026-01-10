#pragma once


#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "n450_070_movePhaseAbstract.hpp"


class NextmoveEvent;


/// <summary>
/// 
/// </summary>
class PhBadCaptures : public MovePhaseAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="resultMove"></param>
	/// <param name="nmEvent"></param>
	/// <returns></returns>
	bool GetNext2Move(Move& resultMove, NextmoveEvent& nmEvent) const override {
		resultMove = nmEvent.GetCurrMove()->m_move;
		nmEvent.DecrementCurMove();

		return true;
	};


	/// <summary>
	/// 
	/// </summary>
	/// <param name="nmEvent"></param>
	void GoNext2Phase(NextmoveEvent& nmEvent) override {
		nmEvent.SetCurrMove(nmEvent.GetLegalMoves() + Move::m_MAX_LEGAL_MOVES - 1 );
		nmEvent.SetLastMove(nmEvent.GetEndBadCaptures());
	}
};


/// <summary>
/// 
/// </summary>
extern PhBadCaptures g_phBadCaptures;
