#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n112_pieceTyp/n112_050_pieceType.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n220_position/n220_650_position.hpp"


/// <summary>
/// 静的交換評価の駒種別イベント
/// </summary>
class PieceTypeSeeEvent {


public:


	/// <summary>
	/// 局面
	/// </summary>
	const Position& m_pos;

	/// <summary>
	/// 移動先マス
	/// </summary>
	const Square m_to;

	/// <summary>
    /// 相手の攻撃駒ビットボード
	/// </summary>
	const Bitboard& m_opponentAttackers;

	/// <summary>
	/// 手番の色
	/// </summary>
	const Color m_turn;


public:


	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="to"></param>
	/// <param name="opponentAttackers"></param>
	/// <param name="turn"></param>
	PieceTypeSeeEvent(
		const Position& pos,
		const Square to,
		const Bitboard& opponentAttackers,
		const Color turn
	) :
		m_pos(pos),
		m_to(to),
		m_opponentAttackers(opponentAttackers),
		m_turn(turn)
	{

	}
};
