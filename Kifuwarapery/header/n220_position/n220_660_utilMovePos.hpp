#pragma once

#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n105_180_piece___/n105_180_155_convPiece.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_650_position.hpp"


/// <summary>
/// 
/// </summary>
class UtilMovePos {


public:


	/// <summary>
	/// 取った駒を Move書式に変換☆
	/// 駒を取らないときは、0 (MoveNone) を返す。
	/// </summary>
	/// <param name="dst"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	static inline Move GET_CAPTURED_PIECE_FROM_SQ(const Square dst, const Position& pos) {

		// 盤面から計算で求めるぜ☆（＾ｑ＾）
		return ConvMove::FROM_CAPTURED_PIECE_TYPE10(
			ConvPiece::TO_PIECE_TYPE10(
				pos.GetPiece(dst)//取った駒☆
				)
			);
	}


	/// <summary>
	/// 取った駒を判別する必要がある。
	/// この関数は駒を取らないときにも使える。
	/// </summary>
	/// <param name="pieceTypeAsMove"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	static inline Move MakeCaptureMove(
		const Move pieceTypeAsMove,
		const Square from,
		const Square to,
		const Position& pos
		) {

		return
			UtilMovePos::GET_CAPTURED_PIECE_FROM_SQ(to, pos)
			|
			ConvMove::FROM_PT_SRC_DST20( pieceTypeAsMove, from,	to)
			;
	}


	/// <summary>
	/// makeCaptureMove() かつ 成り
	/// </summary>
	/// <param name="pieceTypeAsMove"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	static inline Move MakeCapturePromoteMove(
		const Move pieceTypeAsMove,
		const Square from,
		const Square to,
		const Position& pos
	) {
		return
			UtilMovePos::MakeCaptureMove(pieceTypeAsMove, from, to, pos)
			|
			g_MOVE_PROMOTE_FLAG
			;
	}
};
