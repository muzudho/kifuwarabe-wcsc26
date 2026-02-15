#pragma once
#include "../n080_100_sysWorld/n080_100_075_debugcerr.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 2進数表記
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 例えば、Binary<11110>::value とすれば、30 となる。
/// 符合なし64bitなので19桁まで表記可能。
/// </summary>
/// <typeparam name="n"></typeparam>
template <u64 n>
struct Binary
{
	static const u64 value = n % 10 + (Binary<n / 10>::value << 1);
};


/// <summary>
/// template 特殊化
/// </summary>
template <>
struct Binary<0>
{
	static const u64 value = 0;
};
