#pragma once

#include "../../header/n210_score___/n119_090_scoreIndex.hpp"
#include "../../header/n165_movStack/n165_400_move.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


/// <summary>
///		<pre>
/// 冒険者のスキル
/// 
///		- 探索の上手さ☆（＾～＾） ビデオゲームでコンピューター・プレイヤーの強さ調整をしたいときに使う☆（＾～＾） 大会では最強で全ツッパすればいいわけだが（＾～＾）
///		</pre>
/// </summary>
struct AdventurerSkill {


	/// <summary>
	/// 生成。
	/// </summary>
	/// <param name="l"></param>
	/// <param name="mr"></param>
	AdventurerSkill(const int l, const int mr)
		: m_level(l),
		m_maxRandomScoreDiff(static_cast<ScoreIndex>(mr)),
		m_best(g_MOVE_NONE) {}


	/// <summary>
	/// 破棄。
	/// </summary>
	~AdventurerSkill() {}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="s"></param>
	void swapIfEnabled(OurCarriage* s) {
		if (enabled()) {
			auto it = std::find(s->m_rootMovesByID.begin(),
				s->m_rootMovesByID.end(),
				(!m_best.IsNone() ? m_best : pickMove(s)));
			if (s->m_rootMovesByID.begin() != it)
				SYNCCOUT << "info string swap multipv 1, " << it - s->m_rootMovesByID.begin() + 1 << SYNCENDL;
			std::swap(s->m_rootMovesByID[0], *it);
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool enabled() const { return m_level < 20 || m_maxRandomScoreDiff != ScoreZero; }


	/// <summary>
	///
	/// </summary>
	/// <param name="depth"></param>
	/// <returns></returns>
	bool timeToPick(const int depth) const { return depth == 1 + m_level; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	Move pickMove(OurCarriage* s) {
		// level については未対応。max_random_score_diff についてのみ対応する。
		if (m_maxRandomScoreDiff != ScoreZero) {
			size_t i = 1;
			for (; i < s->m_pvSize; ++i) {
				if (m_maxRandomScoreDiff < s->m_rootMovesByID[0].m_score_ - s->m_rootMovesByID[i].m_score_) { break; }
			}
			// 0 から i-1 までの間でランダムに選ぶ。
			std::uniform_int_distribution<size_t> dist(0, i - 1);
			m_best = s->m_rootMovesByID[dist(g_randomTimeSeed)].m_pv_[0];
			return m_best;
		}
		m_best = s->m_rootMovesByID[0].m_pv_[0];
		return m_best;
	}


	/// <summary>
	/// レベル☆？
	/// </summary>
	int m_level;

	/// <summary>
	/// ランダムな評価値の差分の最大値か☆？？
	/// </summary>
	ScoreIndex m_maxRandomScoreDiff;

	/// <summary>
	/// ベストムーブか☆？
	/// </summary>
	Move m_best;
};
