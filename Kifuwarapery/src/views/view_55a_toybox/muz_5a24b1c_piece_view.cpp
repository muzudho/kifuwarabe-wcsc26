#include "muz_5a24b1c_piece_view.hpp"


// ========================================
// 主要メソッド
// ========================================


std::string MuzPieceView::pretty(const Piece piece)
{
	switch (piece)
	{
    case BPawn:
        return " 歩";
    case BLance:
		return " 香";
    case BKnight:
		return " 桂";
    case BSilver:
        return " 銀";
    case BGold:
        return " 金";
    case BBishop:
        return " 角";
    case BRook:
        return " 飛";
    case BKing:
        return " 玉";
    case BProPawn:
        return " と";
    case BProLance:
        return " 杏";
    case BProKnight:
        return " 圭";
    case BProSilver:
        return " 全";
    case BHorse:
        return " 馬";
    case BDragon:
        return " 龍";
    case WPawn:
        return "v歩";
    case WLance:
        return "v香";
    case WKnight:
        return "v桂";
    case WSilver:
        return "v銀";
    case WGold:
        return "v金";
    case WBishop:
        return "v角";
    case WRook:
        return "v飛";
    case WKing:
        return "v玉";
    case WProPawn:
        return "vと";
    case WProLance:
        return "v杏";
    case WProKnight:
        return "v圭";
    case WProSilver:
        return "v全";
    case WHorse:
        return "v馬";
    case WDragon:
        return "v龍";
    case Empty: // thru
    default:
        return "  ";
	}
}
