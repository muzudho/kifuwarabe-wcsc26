//
// 📄 手番の色
//

#pragma once

#include "../../src/lib_cpp/overload_enum_operators.hpp"

/// <summary>
/// 手番の色
/// </summary>
enum Color
{
	Black,
	White,

	/// <summary>
	/// 黒でも白でもないとき、例えば使っていない引数の穴を埋めるといったときに使う☆（＾ｑ＾）
	/// </summary>
	Null
};

/// <summary>
/// Color 列挙型の要素数
/// </summary>
static const int g_COLOR_NUM = 3;
