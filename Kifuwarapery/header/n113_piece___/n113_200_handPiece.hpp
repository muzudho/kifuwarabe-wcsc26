#pragma once
#include "../../src/lib_toybox_base/piece_type.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 持ち駒
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 持ち駒を表すときに使用する。
/// todo: HGold を HRook の後ろに持っていき、PieceType との変換を簡単に出来るようにする。
/// </summary>
enum HandPiece {
	/// <summary>
	/// 持ち駒の歩
	/// </summary>
	HPawn,

	/// <summary>
	/// 持ち駒の香
	/// </summary>
	HLance,
	
	/// <summary>
	/// 持ち駒の桂馬
	/// </summary>
	HKnight,
	
	/// <summary>
	/// 持ち駒の銀
	/// </summary>
	HSilver,
	
	/// <summary>
	/// 持ち駒の金
	/// </summary>
	HGold,
	
	/// <summary>
	/// 持ち駒の角
	/// </summary>
	HBishop,
	
	/// <summary>
	/// 持ち駒の飛車
	/// </summary>
	HRook,
	
	/// <summary>
	/// 列挙型の終端
	/// </summary>
	HandPieceNum
};
OverloadEnumOperators(HandPiece);


/// <summary>
/// 
/// </summary>
extern const HandPiece g_PIECETYPE_TO_HANDPIECE_TABLE[g_PIECETYPE_NUM];
