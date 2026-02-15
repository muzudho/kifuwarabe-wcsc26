#include "../../src/lib_toybox_base/piece_type.hpp"
#include "../../src/lib_toybox_base/hand_piece.hpp"


/// <summary>
/// 
/// </summary>
const HandPiece g_PIECETYPE_TO_HANDPIECE_TABLE[g_PIECETYPE_NUM] = {
	HandPieceNum,
	
	/// <summary>
    /// 持ち駒の種類の順番と、駒の種類の順番は、同じにしておくぜ☆（＾ｑ＾）
	/// </summary>
	HPawn, HLance, HKnight, HSilver, HBishop, HRook, HGold, HandPieceNum, HPawn, HLance, HKnight, HSilver, HBishop, HRook
};
