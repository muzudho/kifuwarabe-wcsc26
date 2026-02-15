#pragma once
#include "../../src/lib_cpp/overload_enum_operators.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 段
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 段の定数
/// </summary>
enum Rank {
	/// <summary>
	/// ９段目
	/// </summary>
	Rank9,
	
	Rank8, Rank7, Rank6, Rank5, Rank4, Rank3, Rank2,
	
	/// <summary>
	/// １段目
	/// </summary>
	Rank1,
	
	/// <summary>
	/// 列挙型の終端
	/// </summary>
	RankNum
};
OverloadEnumOperators(Rank);


/// <summary>
/// 
/// </summary>
extern const Rank g_squareToRank[SquareNum];
