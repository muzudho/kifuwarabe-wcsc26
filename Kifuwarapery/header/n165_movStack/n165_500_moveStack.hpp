#pragma once

#include "../n165_movStack/n165_400_move.hpp" //TODO:


/// <summary>
///		<pre>
/// 指し手とスコア
/// 
///		- 旧名： `MoveStack`
///		</pre>
/// </summary>
struct DeliciousBanana {


	/// <summary>
	/// 
	/// </summary>
	Move m_move;

	/// <summary>
	/// 
	/// </summary>
	int m_score;
};


/// <summary>
/// insertionSort() や std::sort() で必要
/// </summary>
/// <param name="f"></param>
/// <param name="s"></param>
/// <returns></returns>
inline bool operator < (const DeliciousBanana& f, const DeliciousBanana& s) { return f.m_score < s.m_score; }


/// <summary>
/// 
/// </summary>
/// <param name="f"></param>
/// <param name="s"></param>
/// <returns></returns>
inline bool operator > (const DeliciousBanana& f, const DeliciousBanana& s) { return f.m_score > s.m_score; }
