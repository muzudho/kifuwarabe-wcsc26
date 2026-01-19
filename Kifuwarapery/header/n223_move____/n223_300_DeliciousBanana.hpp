#pragma once

#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../n165_movStack/n165_400_move.hpp"


/// <summary>
///		<pre>
/// おいしいバナナ
/// 
///		- 指し手と、評価値。
///		- 旧名： `MoveAndＳcoreIndex`
///		</pre>
/// </summary>
class DeliciousBanana {


public:


	/// <summary>
	/// 指し手
	/// </summary>
	const Move m_move;


	/// <summary>
	///		<pre>
	/// 甘さ
	/// 
	///		- 評価値
	///		</pre>
	/// </summary>
	const enum Sweetness m_sweetness;


public:


	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="move"></param>
	/// <param name="sweetness">評価値</param>
	DeliciousBanana(Move move, enum Sweetness sweetness);
	

	/// <summary>
	/// 指し手
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	Move GetMove(void);
};
