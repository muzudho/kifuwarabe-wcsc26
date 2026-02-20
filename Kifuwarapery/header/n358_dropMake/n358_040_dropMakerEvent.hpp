#pragma once

#include "../../src/lib_toybox_base/color.hpp"
#include "../../src/lib_toybox_base/piece_type.hpp"
#include "../../src/lib_toybox_base/hand.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../../src/lib_bitboard/n160_100_bitboard.hpp"


/// <summary>
/// 
/// </summary>
class DropMakerEvent {


public:


	/// <summary>
	/// FIXME: ／（＾ｑ＾）＼これを消すと bench コマンドの実行時に強制終了してしまう☆ 使ってないけど置いておく必要があるぜ☆（＾～＾）
	/// </summary>
	void* m_pDontUseThisMember__;


public:


	/// <summary>
	/// 自分の色。
	/// </summary>
	const Color		m_us;

	/// <summary>
	/// 局面。
	/// </summary>
	const Position& m_pos;

	/// <summary>
	/// 
	/// </summary>
	const Bitboard& m_target;

	/// <summary>
	/// 持ち駒
	/// </summary>
	const MuzHandModel&		m_hand;

	/// <summary>
	/// 持ち駒の数
	/// </summary>
	const int		m_haveHandNum;

	/// <summary>
	/// 桂馬？
	/// </summary>
	const int		m_noKnightIdx;

	/// <summary>
	/// 桂馬と香？
	/// </summary>
	const int		m_noKnightLanceIdx;

	/// <summary>
    /// ８段目のビットボード☆
	/// </summary>
	const Bitboard& m_tRank8BB;

	/// <summary>
    /// ９段目のビットボード☆
	/// </summary>
	const Bitboard& m_tRank9BB;

	//PieceType m_haveHandArr[6];//(^q^)配列はコンストラクタに渡せないぜ☆！


public:


	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="us"></param>
	/// <param name="pos"></param>
	/// <param name="target"></param>
	/// <param name="hand"></param>
	/// <param name="haveHandNum"></param>
	/// <param name="noKnightIdx"></param>
	/// <param name="noKnightLanceIdx"></param>
	/// <param name="tRank8BB"></param>
	/// <param name="tRank9BB"></param>
	DropMakerEvent(
		const Color us,
		const Position& pos,
		const Bitboard& target,
		const MuzHandModel& hand,
		const int haveHandNum,
		const int noKnightIdx,
		const int noKnightLanceIdx,
		const Bitboard& tRank8BB,
		const Bitboard& tRank9BB
		//PieceType haveHandArr[6]
	) :
		m_us				(us),
		m_pos				(pos),
		m_target			(target),
		m_hand				(hand),
		m_haveHandNum		(haveHandNum),
		m_noKnightIdx		(m_noKnightIdx),
		m_noKnightLanceIdx	(m_noKnightLanceIdx),
		m_tRank8BB			(tRank8BB),
		m_tRank9BB			(tRank9BB)
	{
		//m_haveHandArr = haveHandArr;
	}
};
