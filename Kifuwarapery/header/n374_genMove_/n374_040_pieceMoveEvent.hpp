#pragma once

#include "../n105_color___/n105_100_color.hpp"
#include "../n110_square__/n110_100_square.hpp"
#include "../n112_pieceTyp/n112_050_pieceType.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n165_movStack/n165_300_moveType.hpp"
#include "../n220_position/n220_650_position.hpp"


/// <summary>
/// 
/// </summary>
class PieceMoveEvent {


public:


	/// <summary>
	/// 指し手生成区分
	/// </summary>
	const MoveType m_mt;

	/// <summary>
	/// 
	/// </summary>
	const bool m_all;

	/// <summary>
	/// 局面。
	/// </summary>
	const Position& m_pos;

	/// <summary>
	/// 玉の位置。
	/// </summary>
	const Square m_ksq;


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="mt"></param>
	/// <param name="all"></param>
	/// <param name="pos"></param>
	/// <param name="ksq"></param>
	PieceMoveEvent (
		const MoveType mt,
		const bool all,
		const Position& pos,
		const Square ksq
	):
		m_mt(mt),
		m_all(all),
		m_pos(pos),
		m_ksq(ksq)
	{
	}
};
