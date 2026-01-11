#pragma once

#include "../n080_common__/n080_150_overloadEnumOperators.hpp"


/// <summary>
/// 位置の差分
/// </summary>
enum SquareDelta {

	/// <summary>
	/// 同一の Square にあるとき
	/// </summary>
	DeltaNothing = 0,
	DeltaN = -1, DeltaE = -9, DeltaS = 1, DeltaW = 9,
	DeltaNE = DeltaN + DeltaE,
	DeltaSE = DeltaS + DeltaE,
	DeltaSW = DeltaS + DeltaW,
	DeltaNW = DeltaN + DeltaW
};
OverloadEnumOperators(SquareDelta);
