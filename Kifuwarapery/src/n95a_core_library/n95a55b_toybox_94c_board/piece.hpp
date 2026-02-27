//
// 📄 駒
//

#pragma once

/// <summary>
///		<pre>
/// 駒
///		B* に 16 を加算することで、W* を表す。
///		Promoted を加算することで、成りを表す。
///		</pre>
/// </summary>
enum Piece
{
	Empty = 0,
	UnPromoted = 0,
	Promoted = 8,
	BPawn = 1,		// Black Pawn
	BLance,
	BKnight,
	BSilver,
	BBishop,
	BRook,
	BGold,
	BKing,
    BProPawn,		// Black Promoted Pawn
	BProLance,
	BProKnight,
	BProSilver,
	BHorse,
	BDragon,
	// BDragon = 14
	WPawn = 17,		// White Pawn
	WLance,
	WKnight,
	WSilver,
	WBishop,
	WRook,
	WGold,
	WKing,
	WProPawn,
	WProLance,
	WProKnight,
	WProSilver,
	WHorse,
	WDragon,
	PieceNone // PieceNone = 31  これを 32 にした方が多重配列のときに有利か。
};

/// <summary>
/// 列挙型の主に使う要素の数
/// </summary>
static const int g_PIECE_NUM = 32;
