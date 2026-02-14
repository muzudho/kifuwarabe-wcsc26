#pragma once
#include <iostream>
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../../src/game_engine_layer/game_engine_storage.hpp"


/// <summary>
/// 入玉の沼地を大冒険☆（＾▽＾）！
/// </summary>
class AdventureSwampNyugyoku {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="pos"></param>
	static inline void ExploreSwamp(OurCarriage& ourCarriage, const Position& pos)
	{
		SYNCCOUT << "info nodes " << pos.getNodesSearched()
			<< " time " << ourCarriage.m_stopwatch.GetElapsed() << SYNCENDL;

		if (!ourCarriage.m_signals.m_stop && (ourCarriage.m_limits.m_canPonder || ourCarriage.m_limits.m_isInfinite)) {
			ourCarriage.m_signals.m_stopOnPonderHit = true;
			pos.getHandleMonkey()->WaitFor(ourCarriage.m_signals.m_stop);
		}

		SYNCCOUT << "bestmove win" << SYNCENDL;
	}
};
