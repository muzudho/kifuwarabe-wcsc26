#pragma once
#include "../n085_overEnum/n085_500_overloadEnumOperators.hpp"
#include "../n110_square__/n110_100_square.hpp"


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
