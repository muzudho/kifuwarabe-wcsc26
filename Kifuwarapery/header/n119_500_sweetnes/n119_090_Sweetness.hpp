#pragma once
#include "../../src/lib_cpp/overload_enum_operators.hpp"
#include "../../src/lib_toybox_base/ply.hpp"
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"	// INT_MAX


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
