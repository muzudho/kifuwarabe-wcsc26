#pragma once
#include "../n080_150_overEnum/n080_150_500_overloadEnumOperators.hpp"


enum Depth {
	/// <summary>
	/// 先後で 1 Ply☆？（＾ｑ＾）？チェスの数え方なのかだぜ☆？
	/// </summary>
	OnePly = 2,

	Depth0 = 0,
	Depth1 = 1,
	DepthQChecks = -1 * OnePly,
	DepthQNoChecks = -2 * OnePly,
	DepthQRecaptures = -8 * OnePly,
	DepthNone = -127 * OnePly
};


OverloadEnumOperators(Depth);
