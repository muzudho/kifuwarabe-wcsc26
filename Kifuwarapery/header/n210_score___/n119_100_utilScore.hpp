#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n080_150_overEnum/n080_150_500_overloadEnumOperators.hpp"
#include "n119_090_scoreIndex.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 局面評価値　＞　メート
//────────────────────────────────────────────────────────────────────────────────


using Ply = int;


/// <summary>
/// メートを算出
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
