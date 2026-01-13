#pragma once
#include "../n085_overEnum/n085_500_overloadEnumOperators.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 手番の色
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 手番の色
/// </summary>
enum Color {
	Black,
	White,

	/// <summary>
	/// 黒でも白でもないとき、例えば使っていない引数の穴を埋めるといったときに使う☆（＾ｑ＾）
	/// </summary>
	Null
};
OverloadEnumOperators(Color);


/// <summary>
/// Color 列挙型の要素数
/// </summary>
static const int g_COLOR_NUM = 3;
