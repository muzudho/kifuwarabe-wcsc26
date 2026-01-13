#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n085_overEnum/n085_500_overloadEnumOperators.hpp"
#include "n119_055_utilBound.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 名前のある局面評価値
//────────────────────────────────────────────────────────────────────────────────


using Ply = int;


/// <summary>
/// 
/// </summary>
const Ply g_maxPly = 128;

/// <summary>
/// 
/// </summary>
const Ply g_maxPlyPlus2 = g_maxPly + 2;


/// <summary>
/// 評価値
/// </summary>
enum ScoreIndex {
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
OverloadEnumOperators(ScoreIndex);
