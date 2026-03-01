#pragma once

/// <summary>
///		<pre>
/// 駒種類
/// 
///		- Pro* は 元の 駒の種類に 8 を加算したもの。
///		</pre>
/// </summary>
enum PieceType
{
	PTPromote = 8,

	/// <summary>
	/// 各 PieceType の or をとったもの。
	/// </summary>
	Occupied = 0,

	Pawn,			// 1
	Lance,			// 2
	Knight,
	Silver,
	Bishop,
	Rook,
	Gold,
	King,
	ProPawn,
	ProLance,
	ProKnight,
	ProSilver,
	Horse,
	Dragon,
	PieceTypeNum,	// 15 - 要素数、または None の代わり（＾～＾）

	/// <summary>
	/// 単にtemnplate引数として使用
	/// </summary>
	GoldHorseDragon		// 16
};

/// <summary>
/// TODO: 列挙型のサイズは、列挙型の外に出したいぜ☆（＾ｑ＾）
/// </summary>
static const int g_PIECETYPE_NUM = PieceType::PieceTypeNum;
