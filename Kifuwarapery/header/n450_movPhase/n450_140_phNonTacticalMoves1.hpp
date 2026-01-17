#pragma once


#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "n450_070_movePhaseAbstract.hpp"


class NextmoveEvent;


/// <summary>
/// 
/// </summary>
class PhNonTacticalMoves1 : public MovePhaseAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="resultMove"></param>
	/// <param name="nmEvent"></param>
	/// <returns></returns>
	bool GetNext2Move(Move& resultMove, NextmoveEvent& nmEvent) const override {
		Move move = nmEvent.GetCurrMove()->m_move;
		nmEvent.IncrementCurMove();
		if (move != nmEvent.GetTranspositionTableMove()
			&& move != nmEvent.GetKillerMove(0).m_move
			&& move != nmEvent.GetKillerMove(1).m_move
			)
		{
			resultMove = move;
			return true;
		}
		return false;
	};


	/// <summary>
	/// 
	/// </summary>
	/// <param name="nmEvent"></param>
	void GoNext2Phase(NextmoveEvent& nmEvent) override {
		nmEvent.SetCurrMove(nmEvent.GetLastMove());
		nmEvent.SetLastMove(nmEvent.GetLastNonCapture());

		if (static_cast<Depth>(3 * OnePly) <= nmEvent.GetDepth() ) {
			std::sort(nmEvent.GetCurrMove(), nmEvent.GetLastMove(), std::greater<DeliciousBanana>());
		}
	}
};


/// <summary>
/// 
/// </summary>
extern PhNonTacticalMoves1 g_phNonTacticalMoves1;
