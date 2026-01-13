#pragma once
#include "../n110_square__/n110_100_square.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 列
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 筋の定数
/// </summary>
enum File {
	/// <summary>
	/// ９筋目か☆（＾～＾）？
	/// </summary>
	FileI,
	
	FileH, FileG, FileF, FileE, FileD, FileC, FileB,
	
	/// <summary>
	/// １筋目か☆（＾～＾）？
	/// </summary>
	FileA,
	
	/// <summary>
	/// 列挙型の終端
	/// </summary>
	FileNum,

	FileNoLeftNum = FileD
};
OverloadEnumOperators(File);


/// <summary>
/// 
/// </summary>
extern const File g_squareToFile[SquareNum];
