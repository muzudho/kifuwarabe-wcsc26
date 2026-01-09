#pragma once

#include "../n080_common__/n080_100_common.hpp"
#include "../n119_score___/n119_050_bound.hpp"
#include "../n119_score___/n119_090_scoreIndex.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n223_move____/n223_200_depth.hpp"


/// <summary>
/// トランスポジション・テーブルのエントリ☆（＾ｑ＾）
/// </summary>
class TTEntry {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	u32   GetKey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Depth GetDepth() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ScoreIndex GetScore() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Move  GetMove() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Bound GetType() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	u8    GetGeneration() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	ScoreIndex GetEvalScore() const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="g"></param>
	void SetGeneration(const u8 g);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="depth"></param>
	/// <param name="score"></param>
	/// <param name="move"></param>
	/// <param name="posKeyHigh32"></param>
	/// <param name="bound"></param>
	/// <param name="generation"></param>
	/// <param name="evalScore"></param>
	void SetSave(const Depth depth, const ScoreIndex score, const Move move,
		const u32 posKeyHigh32, const Bound bound, const u8 generation,
		const ScoreIndex evalScore);


private:


	/// <summary>
	/// 
	/// </summary>
	u32 m_key32_;


	/// <summary>
	/// 
	/// </summary>
	u16 m_move16_;


	/// <summary>
	/// 
	/// </summary>
	u8 m_bound_;


	/// <summary>
	/// 
	/// </summary>
	u8 m_generation8_;


	/// <summary>
	/// 
	/// </summary>
	s16 m_score16_;


	/// <summary>
	/// 
	/// </summary>
	s16 m_depth16_;


	/// <summary>
	/// 
	/// </summary>
	s16 m_evalScore_;
};
