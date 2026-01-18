#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_180_piece___/n105_180_205_convHandPiece.hpp"
#include "../n165_movStack/n165_300_moveType.hpp"
#include "../n165_movStack/n165_310_promoteMode.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_660_utilMovePos.hpp"
#include "../n220_position/n220_650_position.hpp"


//class Position;


/// <summary>
/// 駒の成る動き
/// </summary>
class MakePromoteMove {


public:


	/// <summary>
	///		<pre>
	///(^q^)新型2
	/// MoveType によって指し手生成関数を使い分ける。
	/// Drop, Check, Evasion, の場合は別で指し手生成を行う。
	///		</pre>
	/// </summary>
	/// <param name="mt"></param>
	/// <param name="pieceTypeAsMove"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	static inline Move GetSelectedMakeMove_ExceptPromote_mt2(
		MoveType mt,
		const Move pieceTypeAsMove,
		const Square from, const Square to, const Position& pos) {

		// キャプチャー系か、非キャプチャー系かで処理を分けるぜ☆（＾ｑ＾）
		Move move = ((mt == N01_NonCapture || mt == N04_NonCaptureMinusPro) ?
			ConvMove::FROM_PT_SRC_DST20(
				pieceTypeAsMove,
				from, to) :
			UtilMovePos::MakeCaptureMove(
				pieceTypeAsMove,// これ Move にならないのかだぜ☆？（＾ｑ＾）？
				from, to, pos)
			);
		return move;
	}


	/// <summary>
	///		<pre>
	///(^q^)新型1
	/// MoveType によって指し手生成関数を使い分ける。
	/// Drop, Check, Evasion, の場合は別で指し手生成を行う。
	///		</pre>
	/// </summary>
	/// <param name="mt"></param>
	/// <param name="pt"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	static inline Move GetSelectedMakeMove_ExceptPromote_goldHorseDragon(
		MoveType mt,
		const PieceType pt, // 新型２ならここを Move にできるぜ☆（＾ｑ＾）
		const Square from, const Square to, const Position& pos) {

		// キャプチャー系か、非キャプチャー系かで処理を分けるぜ☆（＾ｑ＾）
		Move move = ((mt == N01_NonCapture || mt == N04_NonCaptureMinusPro) ?
			ConvMove::FROM_PT_SRC_DST20(
				ConvMove::FROM_PIECETYPE_ONBOARD10(pt),
			from, to) :
			UtilMovePos::MakeCaptureMove(
				ConvMove::FROM_PIECETYPE_ONBOARD10( pt),
			from, to, pos)
		);
		return move;
	}


	/// <summary>
	/// 非キャプチャー系と分かっているならこちら☆（＾ｑ＾）
	/// </summary>
	/// <param name="pieceTypeAsMove"></param>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	static inline Move GetSelectedMakeMove_ExceptPromote_CaptureCategory(
		const Move pieceTypeAsMove,
		const Square from,
		const Square to,
		const Position& pos
		) {
		//MoveType mt_forAssert, assert(!(mt_forAssert == N01_NonCapture || mt_forAssert == N04_NonCaptureMinusPro), "");
		return UtilMovePos::MakeCaptureMove(pieceTypeAsMove, from, to, pos);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="move"></param>
	static inline void APPEND_PROMOTE_FLAG(Move& move)
	{
		//, MoveType mt_forAssert, const PieceType pt_forAssert
		//assert(!(
		//	// 持ち駒の打ち込みに成りは無い☆
		//	mt_forAssert == N02_Drop ||
		//	// 金と玉に成りは無い☆
		//	pt_forAssert == N07_Gold || pt_forAssert == N08_King
		//));
		move |= g_MOVE_PROMOTE_FLAG;
	}
};


/// <summary>
/// 
/// </summary>
extern MakePromoteMove g_makePromoteMove;
