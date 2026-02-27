#pragma once

#include "../lib_5a_toybox_n1/muz_position_n1_model.hpp"
#include "piece_types.hpp"
#include <string>

namespace {


	//────────────────────────────────────────────────────────────────────────────────
	// 非クラスメンバ 静的グローバル・オブジェクト
	//────────────────────────────────────────────────────────────────────────────────


	/// <summary>
	/// USI用持ち駒。２文字。
	/// </summary>
	static const std::string g_CONV_HAND_PIECE_2LEN_STRING_TABLE[HandPiece::HandPieceNum] = {
		"P*", "L*", "N*", "S*", "G*", "B*", "R*"
	};

	/// <summary>
	/// 
	/// </summary>
	static const char g_CONV_HAND_PIECE_1CHAR_TABLE[HandPiece::HandPieceNum] = {
		'P', 'L', 'N', 'S', 'G', 'B', 'R'
	};
}


/// <summary>
/// 持ち駒の操作
/// </summary>
class ConvHandPiece {


public:


	/// <summary>
	/// 暗算表を使うぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="hp"></param>
	/// <returns></returns>
	static inline std::string GET_2CHARS_STRING(const HandPiece hp) {
		return g_CONV_HAND_PIECE_2LEN_STRING_TABLE[hp];
	}


	/// <summary>
	/// 暗算表を使うぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	static inline HandPiece FromPieceType(const PieceType pt) {
		return g_PIECETYPE_TO_HANDPIECE_TABLE[pt];
	}
};
