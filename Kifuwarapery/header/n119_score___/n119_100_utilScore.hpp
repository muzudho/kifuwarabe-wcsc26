#pragma once

#include "../n080_common__/n080_100_common.hpp"
#include "../n080_common__/n080_150_overloadEnumOperators.hpp"
#include "n119_090_scoreIndex.hpp"


using Ply = int;


/// <summary>
/// 
/// </summary>
class UtilScore {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ply"></param>
	/// <returns></returns>
	static inline ScoreIndex MateIn(const Ply ply) {
		return ScoreMate0Ply - static_cast<ScoreIndex>(ply);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ply"></param>
	/// <returns></returns>
	static inline ScoreIndex MatedIn(const Ply ply) {
		return -ScoreMate0Ply + static_cast<ScoreIndex>(ply);
	}
};
