//
// 📄 駒種類
//

#pragma once

/// <summary>
/// pc が遠隔駒であるかを調べるのに使います。
/// </summary>
static const u32 g_CONV_PIECE_TYPE_SLIDER_VAL = 0x60646064;

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
	N00_Occupied = 0,

	N01_Pawn,
	N02_Lance,
	N03_Knight,
	N04_Silver,
	N05_Bishop,
	N06_Rook,
	N07_Gold,
	N08_King,
	N09_ProPawn,
	N10_ProLance,
	N11_ProKnight,
	N12_ProSilver,
	N13_Horse,
	N14_Dragon,
	N15_PieceTypeNum,

	/// <summary>
	/// 単にtemnplate引数として使用
	/// </summary>
	N16_GoldHorseDragon
};

/// <summary>
/// TODO: 列挙型のサイズは、列挙型の外に出したいぜ☆（＾ｑ＾）
/// </summary>
static const int g_PIECETYPE_NUM = PieceType::N15_PieceTypeNum;
