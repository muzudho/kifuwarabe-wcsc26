#pragma once

#include "../n080_common__/n080_100_common.hpp"
#include "../n105_color___/n105_100_color.hpp"
#include "../n110_square__/n110_100_square.hpp"
#include "../n112_pieceTyp/n112_050_pieceType.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n160_board___/n160_230_setMaskBb.hpp"
#include "../n165_movStack/n165_300_moveType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "n350_040_ptEvent.hpp"
#include "n350_045_pieceTypeSeeEvent.hpp"


/// <summary>
/// 駒の動きの抽象基底クラス
/// </summary>
class PtAbstract {


public:


	/// <summary>
	/// 新方式（＾ｑ＾）
	/// </summary>
	virtual Move AsMove() const = 0;


	/// <summary>
	/// 駒種別イベントから、その駒種別の駒が動けるマスのビットボードを返す。
	/// </summary>
	virtual Bitboard GetAttacks2From(const PieceTypeEvent& ptEvent) const = 0;


	/// <summary>
	/// pin は省かない。//FORCE_INLINE にしたいが、virtual なのでできない。
	/// </summary>
	virtual void Generate2RecaptureMoves_usWhite(
		MoveStack* moveStackList,
		const Position& pos,
		const Square from,
		const Square to
	) const = 0;


	/// <summary>
	///
	/// </summary>
	virtual void Generate2RecaptureMoves_usBlack(
		MoveStack* moveStackList,
		const Position& pos,
		const Square from,
		const Square to
		) const = 0;


	/// <summary>
	/// 駒種別SEEイベントから、その駒種別の駒が動けるマスのビットボードを返す。
	/// </summary>
	virtual PieceType AppendToNextAttackerAndTryPromote(
		Bitboard& occupied,
		Bitboard& attackers,
		PieceType nextPT,
		const PieceTypeSeeEvent ptsEvent
		) const = 0;
};
