#pragma once

#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"


class Position;


/// <summary>
/// 
/// </summary>
struct CheckInfo {

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	explicit CheckInfo(const Position&);

	/// <summary>
	/// discoverd check candidates bitboard
	/// </summary>
	Bitboard m_dcBB;

	/// <summary>
	/// 
	/// </summary>
	Bitboard m_pinned;

	/// <summary>
	/// 
	/// </summary>
	Bitboard m_checkBB[g_PIECETYPE_NUM];
};
