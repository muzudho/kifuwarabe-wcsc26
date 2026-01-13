#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n080_150_overEnum/n080_150_overloadEnumOperators.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 局面評価値の境界
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// αβ探索時の評価値の境界
/// </summary>
enum Bound {
	BoundNone = 0,

	/// <summary>
	/// fail low  で正しい score が分からない。alpha 以下が確定という意味。
	/// </summary>
	BoundUpper = Binary< 1>::value,

	/// <summary>
	/// fail high で正しい score が分からない。beta 以上が確定という意味。
	/// </summary>
	BoundLower = Binary<10>::value,

	/// <summary>
	/// alpha と beta の間に score がある。
	/// </summary>
	BoundExact = Binary<11>::value
};
