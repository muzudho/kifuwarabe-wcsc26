#pragma once

#include "../n080_common__/n080_100_common.hpp"
#include "../n220_position/n220_300_stateInfoMin.hpp"


/// <summary>
/// StateInfoMin だけ memcpy でコピーすることああるので、
/// 継承を使っている。
/// </summary>
struct StateInfo : public StateInfoMin {


public://(^q^)修飾子追加☆m_checkersBBを公開したいんだぜ☆


	/// <summary>
	/// 
	/// </summary>
	Key m_boardKey;

	/// <summary>
	/// 
	/// </summary>
	Key m_handKey;

	/// <summary>
	/// 手番側の玉へ check している駒の Bitboard
	/// </summary>
	Bitboard m_checkersBB;

	/// <summary>
	/// 
	/// </summary>
	StateInfo* m_previous;

	/// <summary>
	/// 手番側の持ち駒
	/// </summary>
	Hand m_hand;

	/// <summary>
	/// capturedPieceType は move.cap() で取得出来るので必要無い。
	/// </summary>
	ChangedLists m_cl;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetKey() const { return m_boardKey + m_handKey; }
};
