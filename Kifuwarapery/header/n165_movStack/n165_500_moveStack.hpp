#pragma once

#include "../n165_movStack/n165_400_move.hpp" //TODO:


/// <summary>
/// TODO: デリシャス・バナナに似ている（＾～＾）？
/// </summary>
struct MoveStack {


	/// <summary>
	/// 
	/// </summary>
	Move m_move;

	/// <summary>
	/// 評価値
	/// </summary>
	int m_sweetness;
};


/// <summary>
/// insertionSort() や std::sort() で必要
/// </summary>
/// <param name="f"></param>
/// <param name="s"></param>
/// <returns></returns>
inline bool operator < (const MoveStack& f, const MoveStack& s) { return f.m_sweetness < s.m_sweetness; }


/// <summary>
/// 
/// </summary>
/// <param name="f"></param>
/// <param name="s"></param>
/// <returns></returns>
inline bool operator > (const MoveStack& f, const MoveStack& s) { return f.m_sweetness > s.m_sweetness; }
