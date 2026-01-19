#pragma once
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"	// INT_MAX
#include "../../header/n080_150_overEnum/n080_150_500_overloadEnumOperators.hpp"	// OverloadEnumOperators
#include "../../header/n119_score___/n119_085_ply.hpp"	// g_maxPly


//────────────────────────────────────────────────────────────────────────────────
// 名前のある局面評価値
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
///		<pre>
/// 甘さ
/// 
///		- 評価値
///		</pre>
/// </summary>
enum Sweetness {
	SweetnessZero = 0,
	SweetnessDraw = 0,
	SweetnessMaxEvaluate = 30000,
	SweetnessMateLong = 30002,
	SweetnessMate1Ply = 32599,
	SweetnessMate0Ply = 32600,
	SweetnessMateInMaxPly = SweetnessMate0Ply - g_maxPly,
	SweetnessMatedInMaxPly = -SweetnessMateInMaxPly,
	SweetnessInfinite = 32601,
	SweetnessNotEvaluated = INT_MAX,
	SweetnessNone = 32602
};
OverloadEnumOperators(Sweetness);
