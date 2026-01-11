#pragma once

#include "../n080_common__/n080_100_common.hpp"
#include "../n223_move____/n223_040_nodeType.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../n480_tt______/n480_300_tt.hpp"
#include "../n520_evaluate/n520_700_evaluation09.hpp"
#include "../n560_timeMgr_/n560_100_limitsDuringGo.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "n760_250_military.hpp"
#include "n760_300_captain.hpp"
#include "n760_350_warrior.hpp"

const int g_MaxThreads = 64;


class Rucksack;


/// <summary>
///		<pre>
/// 元の名前：　ＴｈｒｅａｄＰｏｏｌ
/// ベクター型。
///		</pre>
/// </summary>
class HerosPub : public std::vector<Military*> {


public:


	/// <summary>
	/// 初期化？
	/// </summary>
	/// <param name="s"></param>
	void Init(Rucksack* s);


	/// <summary>
	/// 終了？
	/// </summary>
	void Exit();


	/// <summary>
	/// メインスレッド？
	/// </summary>
	/// <returns></returns>
	Captain* GetFirstCaptain() { return static_cast<Captain*>((*this)[0]); }


	/// <summary>
	/// 最小の深さ？
	/// </summary>
	/// <returns></returns>
	Depth GetMinSplitDepth() const { return m_minimumSplitDepth_; }


	/// <summary>
	/// タイマースレッド？
	/// </summary>
	/// <returns></returns>
	Warrior* GetCurrWarrior() { return this->m_pWarrior_; }


	/// <summary>
	/// 起きろ？
	/// </summary>
	/// <param name="rucksack"></param>
	void WakeUp(Rucksack* rucksack);


	/// <summary>
	/// 寝ろ？
	/// </summary>
	void Sleep();


	/// <summary>
	/// USIオプションを読め？
	/// </summary>
	/// <param name="s"></param>
	void ReadUSIOptions(Rucksack* s);


	/// <summary>
	/// スレーブ？
	/// </summary>
	/// <param name="master"></param>
	/// <returns></returns>
	Military* GetAvailableSlave(Military* master) const;


	/// <summary>
	///		<pre>
	/// タイマー・スレッドをセット？
	///		</pre>
	/// </summary>
	/// <param name="maxPly">ｍｓｅｃ</param>
	void SetCurrWorrior(const int maxPly);


	/// <summary>
	/// 考えが終わるまで待て？
	/// </summary>
	void WaitForThinkFinished();


	/// <summary>
	/// 考えを始めろ？
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="limits"></param>
	/// <param name="searchMoves"></param>
	void StartThinking(const Position& pos, const LimitsDuringGo& limits,
					   const std::vector<Move>& searchMoves);


public:


	/// <summary>
	/// 寝ているか？
	/// </summary>
	bool m_isSleepWhileIdle_;


	/// <summary>
	/// マックス・スレッド？
	/// </summary>
	size_t m_maxThreadsPerSplitedNode_;


	/// <summary>
	/// ミューテックス？
	/// </summary>
	Mutex m_mutex_;


	/// <summary>
	/// 寝ている条件？
	/// </summary>
	ConditionVariable m_sleepCond_;


private:


	/// <summary>
	/// タイマースレッド☆
	/// </summary>
	Warrior* m_pWarrior_;


	/// <summary>
	/// 
	/// </summary>
	Depth m_minimumSplitDepth_;
};
