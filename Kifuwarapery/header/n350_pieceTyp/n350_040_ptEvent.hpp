#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../../src/lib_toybox_base/square.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"


/// <summary>
/// 
/// </summary>
class PieceTypeEvent {


public:

	/// <summary>
    /// 占有しているマスのビットボード☆
	/// </summary>
	const Bitboard& m_occupied;

	/// <summary>
    /// 色☆
    /// </summary>
	const Color m_c;

	/// <summary>
	/// マス☆
    /// </summary>
	const Square m_sq;


public:


	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="occupied"></param>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	PieceTypeEvent(
		const Bitboard& occupied,
		const Color c,
		const Square sq
	) :
		m_occupied(occupied),//(^q^)修正：タイプミス　→　m_occupied(m_occupied),
		m_c(c),
		m_sq(sq)
	{

	}
};
