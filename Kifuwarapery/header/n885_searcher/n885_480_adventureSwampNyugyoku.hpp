#pragma once
#include <iostream>
#include "../n080_common__/n080_100_common.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "n885_040_ourCarriage.hpp"


/// <summary>
/// 
/// </summary>
class HitchhikerNyugyoku {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="pos"></param>
	static inline void Travel_885_480(OurCarriage& ourCarriage, const Position& pos)
	{
		SYNCCOUT << "info nodes " << pos.GetNodesSearched()
			<< " time " << ourCarriage.m_stopwatch.GetElapsed() << SYNCENDL;

		if (!ourCarriage.m_signals.m_stop && (ourCarriage.m_limits.m_canPonder || ourCarriage.m_limits.m_isInfinite)) {
			ourCarriage.m_signals.m_stopOnPonderHit = true;
			pos.GetThisThread()->WaitFor(ourCarriage.m_signals.m_stop);
		}

		SYNCCOUT << "bestmove win" << SYNCENDL;
	}
};
