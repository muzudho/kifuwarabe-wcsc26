#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n165_movStack/n165_300_movegenType.hpp"
#include "../n220_position/n220_650_position.hpp"


/// <summary>
/// 
/// </summary>
class PieceMoveEvent {


public:


	/// <summary>
	/// 指し手生成区分
	/// </summary>
	const MovegenType m_mt;

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
		const MovegenType mt,
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
