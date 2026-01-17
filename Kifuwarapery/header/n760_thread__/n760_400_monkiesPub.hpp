#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n220_position/n220_645_gameStats.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../n480_tt______/n480_300_tt.hpp"
#include "../n520_evaluate/n520_700_evaluation09.hpp"
#include "../n560_timeMgr_/n560_100_limitsDuringGo.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "n760_250_MonkeyAbstract.hpp"
#include "n760_300_CaptainMonkey.hpp"
#include "n760_350_ErrandMonkey.hpp"


// 依存関係の回避
class OurCarriage;


const int g_MaxThreads = 64;


/// <summary>
///		<pre>
/// 猿酒場
/// 
///		- 元の名前：　`ＴhreadPool`
///		</pre>
/// </summary>
class MonkiesPub : public std::vector<MonkeyAbstract*> {


public:


	// ========================================
	// フィールド
	// ========================================


	// クエスチョン・フィールド


	/// <summary>
	/// 寝ているか？
	/// </summary>
	bool m_isSleepWhileIdle_;


	// メイン・フィールド


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


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// メインスレッド？
	/// </summary>
	/// <returns></returns>
	CaptainMonkey* GetFirstCaptain() { return static_cast<CaptainMonkey*>((*this)[0]); }


	/// <summary>
	/// 最小の深さ？
	/// </summary>
	/// <returns></returns>
	Depth GetMinSplitDepth() const { return m_minimumSplitDepth_; }


	/// <summary>
	/// 現在の部下スレッド
	/// </summary>
	/// <returns></returns>
	ErrandMonkey* GetCurrSubordinate() { return this->m_pSubordinate_; }


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// 初期化？
	/// </summary>
	/// <param name="s"></param>
	void Init(OurCarriage* s);


	/// <summary>
	/// 終了？
	/// </summary>
	void Exit();


	/// <summary>
	/// 起きろ？
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	void WakeUp(OurCarriage* ourCarriage);


	/// <summary>
	/// 寝ろ？
	/// </summary>
	void Sleep();


	/// <summary>
	/// USIオプションを読め？
	/// </summary>
	/// <param name="s"></param>
	void ReadUSIOptions(OurCarriage* s);


	/// <summary>
	/// スレーブ？
	/// </summary>
	/// <param name="master"></param>
	/// <returns></returns>
	MonkeyAbstract* GetAvailableSlave(MonkeyAbstract* master) const;


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
	void StartThinking(
		const GameStats& gameStats,
		const Position& pos,
		const LimitsDuringGo& limits,
		const std::vector<Move>& searchMoves);


private:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// タイマースレッド☆
	/// </summary>
	ErrandMonkey* m_pSubordinate_;


	/// <summary>
	/// 
	/// </summary>
	Depth m_minimumSplitDepth_;
};
