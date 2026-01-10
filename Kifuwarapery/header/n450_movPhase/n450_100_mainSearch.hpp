#pragma once


#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "n450_070_movePhaseAbstract.hpp"


class NextmoveEvent;


/// <summary>
/// 
/// </summary>
class MainSearch : public MovePhaseAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="resultMove"></param>
	/// <param name="nmEvent"></param>
	/// <returns></returns>
	bool GetNext2Move(Move& resultMove, NextmoveEvent& nmEvent) const override {
		nmEvent.IncrementCurMove();
		resultMove = nmEvent.GetTranspositionTableMove();
		return true;
	};


	/// <summary>
	/// 
	/// </summary>
	/// <param name="nmEvent"></param>
	void GoNext2Phase(NextmoveEvent& nmEvent) override {
		UNREACHABLE;
	}
};


/// <summary>
/// 
/// </summary>
extern MainSearch g_mainSearch;
