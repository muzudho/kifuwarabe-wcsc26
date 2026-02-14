#pragma once

#include "../../header/n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../../header/n165_movStack/n165_400_move.hpp"
#include "../../src/layer_game_engine/game_engine_storage.hpp"


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
		m_maxRandomSweetnessDiff(static_cast<Sweetness>(mr)),
		m_best(g_MOVE_NONE) {}


	/// <summary>
	/// 破棄。
	/// </summary>
	~AdventurerSkill() {}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="s"></param>
	void swapIfEnabled(GameEngineStorageOurCarriage* s) {
		if (enabled()) {
			auto it = std::find(s->m_rootMoves.begin(),
				s->m_rootMoves.end(),
				(!m_best.IsNone() ? m_best : pickMove(s)));
			if (s->m_rootMoves.begin() != it)
				SYNCCOUT << "info string swap multipv 1, " << it - s->m_rootMoves.begin() + 1 << SYNCENDL;
			std::swap(s->m_rootMoves[0], *it);
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool enabled() const { return m_level < 20 || m_maxRandomSweetnessDiff != SweetnessZero; }


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
	Move pickMove(GameEngineStorageOurCarriage* s) {
		// level については未対応。max_random_weetness_diff についてのみ対応する。
		if (m_maxRandomSweetnessDiff != SweetnessZero) {
			size_t i = 1;
			for (; i < s->m_pvSize; ++i) {
				if (m_maxRandomSweetnessDiff < s->m_rootMoves[0].m_sweetness_ - s->m_rootMoves[i].m_sweetness_) { break; }
			}
			// 0 から i-1 までの間でランダムに選ぶ。
			std::uniform_int_distribution<size_t> dist(0, i - 1);
			m_best = s->m_rootMoves[dist(g_randomTimeSeed)].m_pv_[0];
			return m_best;
		}
		m_best = s->m_rootMoves[0].m_pv_[0];
		return m_best;
	}


	/// <summary>
	/// レベル☆？
	/// </summary>
	int m_level;

	/// <summary>
	/// ランダムな評価値の差分の最大値か☆？？
	/// </summary>
	Sweetness m_maxRandomSweetnessDiff;

	/// <summary>
	/// ベストムーブか☆？
	/// </summary>
	Move m_best;
};
