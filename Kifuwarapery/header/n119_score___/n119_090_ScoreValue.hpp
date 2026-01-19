#pragma once
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"	// INT_MAX
#include "../../header/n080_150_overEnum/n080_150_500_overloadEnumOperators.hpp"	// OverloadEnumOperators
#include "../../header/n119_score___/n119_085_ply.hpp"	// g_maxPly


//────────────────────────────────────────────────────────────────────────────────
// 名前のある局面評価値
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 評価値
/// </summary>
enum ScoreValue {
	ScoreZero = 0,
	ScoreDraw = 0,
	ScoreMaxEvaluate = 30000,
	ScoreMateLong = 30002,
	ScoreMate1Ply = 32599,
	ScoreMate0Ply = 32600,
	ScoreMateInMaxPly = ScoreMate0Ply - g_maxPly,
	ScoreMatedInMaxPly = -ScoreMateInMaxPly,
	ScoreInfinite = 32601,
	ScoreNotEvaluated = INT_MAX,
	ScoreNone = 32602
};
OverloadEnumOperators(ScoreValue);
