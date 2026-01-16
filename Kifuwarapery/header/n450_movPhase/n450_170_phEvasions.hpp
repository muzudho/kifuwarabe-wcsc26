#pragma once


#include "../n160_boardBb_/n160_100_bitboard.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n407_moveGen_/n407_800_moveGenerator200.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "n450_070_movePhaseAbstract.hpp"


class NextmoveEvent;


/// <summary>
/// 王手回避の指し手を生成・スコアリングする。
/// </summary>
class PhEvasions : public MovePhaseAbstract {


public:


	/// <summary>
	///
	/// </summary>
	/// <param name="resultMove"></param>
	/// <param name="nmEvent"></param>
	/// <returns></returns>
	bool GetNext2Move(Move& resultMove, NextmoveEvent& nmEvent) const override {
		Move move = UtilMoveStack::PickBest(nmEvent.GetCurrMove(), nmEvent.GetLastMove())->m_move;
		nmEvent.IncrementCurMove();
		if (move != nmEvent.GetTranspositionTableMove()) {
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
		nmEvent.SetLastMove(g_moveGenerator200.GenerateMoves_2(N06_Evasion,nmEvent.GetCurrMove(), nmEvent.GetPos()) );
		if (nmEvent.GetCurrMove() + 1 < nmEvent.GetLastMove()) {
			nmEvent.ScoreEvasions();
		}
	}
};


/// <summary>
/// 
/// </summary>
extern PhEvasions g_phEvasions;
