#pragma once

#include "../n119_score___/n119_090_scoreIndex.hpp"
#include "../n165_movStack/n165_400_move.hpp"


/// <summary>
/// 指し手と、評価値。
/// </summary>
class MoveAndScoreIndex {


public:


	/// <summary>
	/// 指し手
	/// </summary>
	const Move m_move;


	/// <summary>
	/// 評価値
	/// </summary>
	const enum ScoreIndex m_scoreIndex;


public:


	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="move"></param>
	/// <param name=""></param>
	MoveAndScoreIndex(Move move, enum ScoreIndex scoreIndex);
	

	/// <summary>
	/// 指し手
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	Move GetMove(void);
};
