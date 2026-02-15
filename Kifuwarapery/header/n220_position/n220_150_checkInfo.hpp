#pragma once

#include "../../src/lib_toybox_base/piece_type.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"


class Position;


/// <summary>
///		<pre>
/// 王手の情報か（＾～＾）？
///		</pre>
/// </summary>
struct CheckInfo {

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	explicit CheckInfo(const Position&);

	/// <summary>
	///		<pre>
	/// discoverd check candidates bitboard
	/// 
	///		- 空き王手か何かか（＾～＾）？
	///		</pre>
	/// </summary>
	Bitboard m_dcBB;

	/// <summary>
	///		<pre>
	/// どいたら空き王手になる駒か（＾～＾）？
	///		</pre>
	/// </summary>
	Bitboard m_pinned;

	/// <summary>
	/// 
	/// </summary>
	Bitboard m_checkBB[g_PIECETYPE_NUM];
};
