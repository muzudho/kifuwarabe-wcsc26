#pragma once


#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "n450_070_movePhaseAbstract.hpp"


class NextmoveEvent;


/// <summary>
/// 
/// </summary>
class PhKillers : public MovePhaseAbstract {


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
		if (!move.IsNone()
			&& move != nmEvent.GetTranspositionTableMove()
			&&
			(
				nmEvent.GetPos().getTurn()==Color::Black
				?
				nmEvent.GetPos().MoveIsPseudoLegal<Color::Black,Color::White>(move, true)
				:
				nmEvent.GetPos().MoveIsPseudoLegal<Color::White,Color::Black>(move, true)
			)			
			&& nmEvent.GetPos().GetPiece(move.To()) == N00_Empty)
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
		nmEvent.SetCurrMove(nmEvent.GetKillerMoves());//m_currMove_ = m_killerMoves_;
		nmEvent.SetLastMove(nmEvent.GetCurrMove() + 2);
	}
};


/// <summary>
/// 
/// </summary>
extern PhKillers g_phKillers;
