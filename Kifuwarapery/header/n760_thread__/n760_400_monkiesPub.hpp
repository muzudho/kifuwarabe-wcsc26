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
#include "n760_250_Monkey.hpp"
#include "n760_300_Orangutans.hpp"
#include "n760_350_Chimpanzee.hpp"


// 依存関係の回避
class OurCarriage;


const int g_MaxThreads = 64;


/// <summary>
///		<pre>
/// 猿酒場
/// 
///		- 元の名前：　`ＴhreadPool`
///		- ベクターを（持っているのではなく）継承していることに注意。
///		</pre>
/// </summary>
class MonkiesPub
{


public:


	// ========================================
	// フィールド
	// ========================================


	// クエスチョン・フィールド


	/// <summary>
	/// ［やることない猿は寝てろ］フラグ
	/// </summary>
	bool m_idleMonkeyIsSleep_;


	// メイン・フィールド


	/// <summary>
	/// お客の猿たち
	/// </summary>
	std::vector<Monkey*> m_itemMonkies;

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
	///		<pre>
	/// オランウータンを取得
	/// 
	///		- たくさん居る猿のうち、最初の１匹を［オランウータン］扱いする。
	///		- オランウータン＝メインスレッド。
	///		</pre>
	/// </summary>
	/// <returns></returns>
	Orangutans* getFirstMonkeyAsOrangutans() { return static_cast<Orangutans*>((*this).m_itemMonkies[0]); }


	/// <summary>
	/// 最小の深さ？
	/// </summary>
	/// <returns></returns>
	Depth GetMinSplitDepth() const { return m_minimumSplitDepth_; }


	/// <summary>
	/// 現在のチンパンジー
	/// </summary>
	/// <returns></returns>
	Chimpanzee* GetCurrentChimpanzee() { return this->m_pChimpanzee_; }


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// 初期化？
	/// </summary>
	/// <param name="s"></param>
	void initialize_10a520b_monkiePub(OurCarriage* s);


	/// <summary>
	/// 終了？
	/// </summary>
	void exit_90a500b();


	/// <summary>
	/// 起きろ？
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	void wakeUpMonkies_n10(OurCarriage* ourCarriage);


	/// <summary>
	/// 寝ろ？
	/// </summary>
	void Sleep();


	/// <summary>
	/// USIオプションを読め？
	/// </summary>
	/// <param name="s"></param>
	void newAllMonkiesByUSIOptions(OurCarriage* s);


	/// <summary>
	/// スレーブ？
	/// </summary>
	/// <param name="master"></param>
	/// <returns></returns>
	Monkey* GetAvailableSlave(Monkey* master) const;


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
	void waitForThinkFinished();


	/// <summary>
	/// 考えを始めろ？
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="limits"></param>
	/// <param name="searchMoves"></param>
	void go_50a500b500c500d_awakeMonkies(
		const GameStats& gameStats,
		const Position& pos,
		const LimitsDuringGo& limits,
		const std::vector<Move>& searchMoves);


private:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///		<pre>
	/// チンパンジー
	/// 
	///		- タイマースレッド☆
	///		</pre>
	/// </summary>
	Chimpanzee* m_pChimpanzee_;


	/// <summary>
	/// 
	/// </summary>
	Depth m_minimumSplitDepth_;
};
