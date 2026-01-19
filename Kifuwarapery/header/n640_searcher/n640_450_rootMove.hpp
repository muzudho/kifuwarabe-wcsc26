#pragma once

#include <vector>
#include "../n165_movStack/n165_400_move.hpp"
#include "../n223_move____/n223_300_DeliciousBanana.hpp"

#include "n640_440_splitedNode.hpp"


/// <summary>
/// 
/// </summary>
class RootMove {


public:


	/// <summary>
	/// 生成。
	/// </summary>
	RootMove() {}


	/// <summary>
	/// 生成。
	/// </summary>
	/// <param name="m"></param>
	explicit RootMove(const Move m) : m_score_(-SweetnessInfinite), m_prevScore_(-SweetnessInfinite) {
		m_pv_.push_back(m);
		m_pv_.push_back(g_MOVE_NONE);
	}


	/// <summary>
	/// 生成。
	/// </summary>
	/// <param name="m"></param>
	explicit RootMove(const DeliciousBanana banana) : m_score_(banana.m_sweetness), m_prevScore_(-SweetnessInfinite) {
		m_pv_.push_back(banana.m_move);
		m_pv_.push_back(g_MOVE_NONE);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	bool operator < (const RootMove& m) const {
		return m_score_ < m.m_score_;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	bool operator == (const Move& m) const {
		return m_pv_[0] == m;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	void ExtractPvFromTT(Position& pos);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	void InsertPvInTT(Position& pos);


public:


	/// <summary>
	/// 評価値
	/// </summary>
	Sweetness m_score_;

	/// <summary>
	/// 前の評価値
	/// </summary>
	Sweetness m_prevScore_;

	/// <summary>
	/// 指し手のスタック
	/// </summary>
	std::vector<Move> m_pv_;
};
