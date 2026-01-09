#pragma once


#include "../n080_common__/n080_100_common.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "n450_070_movePhaseAbstract.hpp"


class NextmoveEvent;


/// <summary>
/// 
/// </summary>
class MovePhaseNum : public MovePhaseAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="resultMove"></param>
	/// <param name="nmEvent"></param>
	/// <returns></returns>
	bool GetNext2Move(Move& resultMove, NextmoveEvent& nmEvent) const override {
		UNREACHABLE;
		return false;
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
extern MovePhaseNum g_movePhaseNum;
