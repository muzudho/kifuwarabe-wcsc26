#pragma once

#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n112_pieceTyp/n112_050_pieceType.hpp"
#include "../n113_piece___/n113_155_convPiece.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"


namespace {
	//────────────────────────────────────────────────────────────────────────────────
	// 非クラスメンバ 秘密 静的グローバル・オブジェクト
	//────────────────────────────────────────────────────────────────────────────────

	/*
	//────────────────────────────────────────────────────────────────────────────────
	// きふわらべは 計算が苦手なので、早見表を作っておこうぜ☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	// 駒打ちの駒の種類(pt)から移動元(from)に変換
	// todo: PieceType を HandPiece に変更
	static inline constexpr Square G_PIECETYPE_TO_HANDSQ(const PieceType pt) { return static_cast<Square>(Square::SquareNum - 1 + pt); }
	static const Square g_CONV_MOVE_PIECETYPE_TO_HANDSQ[g_PIECETYPE_NUM] = {
		G_PIECETYPE_TO_HANDSQ(PieceType::N00_Occupied),
		G_PIECETYPE_TO_HANDSQ(PieceType::N01_Pawn),
		G_PIECETYPE_TO_HANDSQ(PieceType::N02_Lance),
		G_PIECETYPE_TO_HANDSQ(PieceType::N03_Knight),
		G_PIECETYPE_TO_HANDSQ(PieceType::N04_Silver),
		G_PIECETYPE_TO_HANDSQ(PieceType::N05_Bishop),
		G_PIECETYPE_TO_HANDSQ(PieceType::N06_Rook),
		G_PIECETYPE_TO_HANDSQ(PieceType::N07_Gold),
		G_PIECETYPE_TO_HANDSQ(PieceType::N08_King),
		G_PIECETYPE_TO_HANDSQ(PieceType::N09_ProPawn),
		G_PIECETYPE_TO_HANDSQ(PieceType::N10_ProLance),
		G_PIECETYPE_TO_HANDSQ(PieceType::N11_ProKnight),
		G_PIECETYPE_TO_HANDSQ(PieceType::N12_ProSilver),
		G_PIECETYPE_TO_HANDSQ(PieceType::N13_Horse),
		G_PIECETYPE_TO_HANDSQ(PieceType::N14_Dragon)
	};
	*/


	//────────────────────────────────────────────────────────────────────────────────
	// きふわらべは 計算が苦手なので、早見表を作っておこうぜ☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────

	/// <summary>
	/// 打とうとしている駒の種類(pt)に、盤上の升の数-1（80）を足すことで、持ち駒用の特別マス番号(from)になる☆
	/// 持ち駒用の特別マス番号は、 <<7 すると Move書式に変換できるぜ☆
	/// todo: PieceType を HandPiece に変更したい
	/// </summary>
	/// <param name="handPt"></param>
	/// <returns></returns>
	static inline Move G_PT_TO_DA_MOVE(const PieceType handPt) { return static_cast<Move>( static_cast<Square>(Square::SquareNum - 1 + handPt) << 7); }
	static const Move g_CONV_MOVE_PT_TO_DA_MOVE[g_PIECETYPE_NUM] = {
		G_PT_TO_DA_MOVE(PieceType::N00_Occupied),
		G_PT_TO_DA_MOVE(PieceType::N01_Pawn),
		G_PT_TO_DA_MOVE(PieceType::N02_Lance),
		G_PT_TO_DA_MOVE(PieceType::N03_Knight),
		G_PT_TO_DA_MOVE(PieceType::N04_Silver),
		G_PT_TO_DA_MOVE(PieceType::N05_Bishop),
		G_PT_TO_DA_MOVE(PieceType::N06_Rook),
		G_PT_TO_DA_MOVE(PieceType::N07_Gold),
		G_PT_TO_DA_MOVE(PieceType::N08_King),
		G_PT_TO_DA_MOVE(PieceType::N09_ProPawn),
		G_PT_TO_DA_MOVE(PieceType::N10_ProLance),
		G_PT_TO_DA_MOVE(PieceType::N11_ProKnight),
		G_PT_TO_DA_MOVE(PieceType::N12_ProSilver),
		G_PT_TO_DA_MOVE(PieceType::N13_Horse),
		G_PT_TO_DA_MOVE(PieceType::N14_Dragon)
	};
}


/// <summary>
/// Ａ　→　指し手　変換、または
/// 指し手　→　Ａ　変換。
/// </summary>
class ConvMove {


public:


	/// <summary>
	/// 移動元から指し手に変換
	/// </summary>
	/// <param name="from"></param>
	/// <returns></returns>
	static inline Move FROM_SRC10(const Square from) { return static_cast<Move>(from << 7); }


	/// <summary>
	/// 駒の種類から MOVE表記（打ではない）に変換
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	static inline Move FROM_PIECETYPE_ONBOARD10(
		const PieceType pt
	) {
		return static_cast<Move>(pt << 16);
	}


	/// <summary>
	/// 駒の種類から MOVE表記（打）に変換
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	static inline Move FROM_PIECETYPE_DA10(
		const PieceType pt
		) {
		return g_CONV_MOVE_PT_TO_DA_MOVE[pt];
	}


	/// <summary>
	/// 取った駒の種類から指し手に変換
	/// </summary>
	/// <param name="captured"></param>
	/// <returns></returns>
	static inline Move FROM_CAPTURED_PIECE_TYPE10(const PieceType captured) { return static_cast<Move>(captured << 20); }


	/// <summary>
	///		<pre>
	/// 移動する駒の種類、移動元、移動先　から指し手に変換
	/// 
	///		- 新型☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="pieceTypeAsMove"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <returns></returns>
	static inline Move FROM_PT_SRC_DST20(
		const Move pieceTypeAsMove,
		const Square from,
		const Square to
		) {
		return pieceTypeAsMove
			|
			ConvMove::FROM_SRC10(from)
			|
			static_cast<Move>(to) // 移動先の Square→Move は、書式変換要らず☆（＾ｑ＾）
			;
	}


	/// <summary>
	///		<pre>
	/// 移動する駒の種類、移動元、移動先　から指し手に変換
	/// 
	///			- 旧型☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="pt">新型なら、ここをムーブにできるぜ☆（＾ｑ＾）</param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <returns></returns>
	static inline Move FROM_PT_SRC_DST30(
		const PieceType pt,
		const Square from,
		const Square to
	) {
		return
			ConvMove::FROM_PIECETYPE_ONBOARD10(pt) // ピースタイプをムーブに変換するだけ☆
			|
			ConvMove::FROM_SRC10(from)
			|
			static_cast<Move>(to) // 移動先の Square→Move は、書式変換要らず☆（＾ｑ＾）
			;
	}


	/// <summary>
	/// 駒を打つ手の符号（Move）を作成するぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="pieceTypeAsDaMove"></param>
	/// <param name="to"></param>
	/// <returns></returns>
	static inline Move Convert30_MakeDropMove_da(
		const Move pieceTypeAsDaMove,
		const Square to) {
		return
			pieceTypeAsDaMove//（打とうとしている駒の種類の）打のMove書式だぜ☆（＾ｑ＾）
			|
			static_cast<Move>(to) // 移動先の Square→Move は、書式変換要らず☆（＾ｑ＾）
			;
	}
};
