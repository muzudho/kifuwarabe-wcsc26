#include "piece_types.hpp"
#include "../lib_5a_toybox_n1/piece_type.hpp"
#include "../n95a55b_toybox_95c_hand_stand/hand_piece.hpp"

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
