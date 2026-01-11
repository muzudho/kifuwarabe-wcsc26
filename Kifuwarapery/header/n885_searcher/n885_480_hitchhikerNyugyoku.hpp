#pragma once


#include <iostream>
#include "../n080_common__/n080_100_common.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "n885_040_rucksack.hpp"


/// <summary>
/// 
/// </summary>
class HitchhikerNyugyoku {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="rucksack"></param>
	/// <param name="pos"></param>
	static inline void Travel_885_480(Rucksack& rucksack, const Position& pos)
	{
		SYNCCOUT << "info nodes " << pos.GetNodesSearched()
			<< " time " << rucksack.m_stopwatch.GetElapsed() << SYNCENDL;

		if (!rucksack.m_signals.m_stop && (rucksack.m_limits.m_canPonder || rucksack.m_limits.m_isInfinite)) {
			rucksack.m_signals.m_stopOnPonderHit = true;
			pos.GetThisThread()->WaitFor(rucksack.m_signals.m_stop);
		}

		SYNCCOUT << "bestmove win" << SYNCENDL;
	}
};
