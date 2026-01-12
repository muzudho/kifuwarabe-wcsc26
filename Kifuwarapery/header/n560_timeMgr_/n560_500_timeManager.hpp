#pragma once

#include "../n520_evaluate/n520_700_evaluation09.hpp"
#include "../n560_timeMgr_/n560_100_limitsDuringGo.hpp"


// 依存関係の都合を解消。
class OurCarriage;


/// <summary>
/// 時間管理だぜ☆（＾ｑ＾）
/// 
///		- 寿命はリュックサックの内側。
/// </summary>
class TimeManager {


public:


	// ========================================
	// 軽い開始／終了
	// ========================================


	/// <summary>
	///		<pre>
	/// 元の名前：Ｉｎｉｔ
	/// 
	///		- ヒッチハイカーのThink開始時に初期設定をするぜ☆（＾▽＾）
	///		</pre>
	/// </summary>
	/// <param name="isMoveTime0Clear"></param>
	/// <param name="limits">m_moveTimeを 0にする場合があるぜ☆（＾ｑ＾）</param>
	/// <param name="currentPly"></param>
	/// <param name="us"></param>
	/// <param name="pOurCarriage">わたしたちの馬車</param>
	void Initialize(
		bool& isMoveTime0Clear,
		const LimitsDuringGo& limits,
		const Ply currentPly,
		const Color us,
		OurCarriage* pOurCarriage);


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	///		<pre>
	/// 本譜の情勢不安定さ☆？をセットするぜ☆
	/// 
	///		- 反復深化探索の開始時に呼び出されるぜ（＾～＾）
	///		</pre>
	/// </summary>
	/// <param name="currBestmovePlyChanges"></param>
	/// <param name="prevBestmovePlyChanges"></param>
	void SetPvInstability(
		const Ply currBestmovePlyChanges,
		const Ply prevBestmovePlyChanges);


	/// <summary>
	///		<pre>
	/// 使っていい時間をオーバーしちゃったかどうかだぜ☆（＾ｑ＾）
	/// 
	///		- 最初の指し手のときに呼び出して確認するぜ☆
	///		</pre>
	/// </summary>
	/// <param name="elapsed"></param>
	/// <returns></returns>
	inline bool IsTimeBudgetOver(const int elapsed) { return this->GetPlanThinkSeconds() < elapsed; }


	/// <summary>
	/// まだ反復深化していい時間が残ってるか☆？（＾ｑ＾）
	/// 
	///		- 消費時間が、使っていい時間の60%を下回っている場合。
	/// </summary>
	/// <param name="elapsed"></param>
	/// <returns></returns>
	inline bool IsTimeOk_CanIterativeDeeping(const int elapsed) {
		return elapsed < this->GetPlanThinkSeconds() * 60 / 100;
	}


	/// <summary>
	/// 新しく生まれてくる部下の寿命☆（＾ｑ＾）
	/// </summary>
	/// <returns></returns>
	inline int GetSubordinateLifeTime() { return this->GetPlanThinkSeconds() / 16; }


	/// <summary>
	/// これ以上の時間がないか☆？（＾ｑ＾）
	/// </summary>
	/// <param name="timerResolution"></param>
	/// <param name="elapsed"></param>
	/// <returns></returns>
	inline bool IsNoMoreTime(const int timerResolution, const int elapsed) {
		return this->GetSaidaiEnchoTime() - 2 * timerResolution < elapsed;
	}


private:


	// ========================================
	// フィールド
	// ========================================


	// 手目に応じて調整される時間☆
	//int m_temeBonusTime_;

	/// <summary>
	/// 相手が消費するだろうと思っている時間（秒）。その間に自分も考えようと思っている（＾▽＾）
	/// </summary>
	int m_predictOpponentPaySeconds_;

	/// <summary>
	///		<pre>
	/// 自分の手番で使おうと思っている、自分の残り時間（秒）
	/// 
	///		- 元の名前：ＯｐｔｉｍｕｍＳｅａｒｃｈＴｉｍｅ
	///		</pre>
	/// </summary>
	int m_planPayOwnSeconds_;

	/// <summary>
	///		<pre>
	/// 思考の最大延長時間
	/// 元の名前：ＭａｘｉｍｕｍＳｅａｒｃｈＴｉｍｅ
	///		</pre>
	/// </summary>
	int m_saidaiEnchoTime_;

	/// <summary>
	///		<pre>
	/// 思考の遊び時間（秒）
	/// 
	///		- 元の名前：ｕｎｓｔａｂｌｅＰＶＥｘｔｒａＴｉｍｅ
	///		</pre>
	/// </summary>
	int m_bufferThinkSeconds_;


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	///		<pre>
	/// なんだかんだで、使っちゃうつもりの時間☆（＾ｑ＾）
	/// ［相手が何秒考える］という予測も含まれているぜ（＾ｑ＾）
	/// 
	///		- 元の名前：ＡｖａｉｌａｂｌｅＴｉｍｅ
	///		</pre>
	/// </summary>
	/// <returns></returns>
	int GetPlanThinkSeconds() const {
		// 自分と相手が使うと予測したタイム　＋　遊びタイム
		return this->GetPlanPayBothPlayersSeconds()
			//+ this->GetTemeBonusTime()
			+ this->GetBufferThinkSeconds();
	}


	/*
	// 手目に応じて調整される時間☆
	inline int GetTemeBonusTime() const {
		return this->m_temeBonusTime_;
	}
	inline void ZeroclearTemeBonusTime() {
		this->m_temeBonusTime_ = 0;
	}
	inline void SetTemeBonusTime(int value) {
		this->m_temeBonusTime_ = value;
	}
	//*/


	/// <summary>
	/// 相手が思考に使ってくれる時間（秒）の予想値。その時間で思考しようと思っているぜ（＾▽＾）
	/// </summary>
	/// <returns></returns>
	inline int GetPredictOpponentPaySeconds() const {
		return this->m_predictOpponentPaySeconds_;
	}


	/// <summary>
	/// 相手が思考に使ってくれる時間（秒）の予想値。その時間で思考しようと思っているぜ（＾▽＾）
	/// </summary>
	/// <param name="value"></param>
	inline void SetPredictOpponentPaySeconds(int value) {
		this->m_predictOpponentPaySeconds_ = value;
	}


	/// <summary>
	/// 相手が思考に使ってくれる時間（秒）の予想値。その時間で思考しようと思っているぜ（＾▽＾）
	/// </summary>
	inline void ZeroclearPredictOpponentPaySeconds()
	{
		this->m_predictOpponentPaySeconds_ = 0;
	}


	/// <summary>
	/// 自分と相手の両方が消費すると思っている思考時間。その時間で思考しようと思っているぜ（＾▽＾）
	/// </summary>
	/// <returns></returns>
	inline int GetPlanPayBothPlayersSeconds() const {
		return this->m_planPayOwnSeconds_ + this->m_predictOpponentPaySeconds_;
	}


	/// <summary>
	/// 自分の手番で使おうと思っている、自分の持ち時間
	/// </summary>
	/// <returns></returns>
	inline int GetPlanPayOwnSeconds() const {
		return this->m_planPayOwnSeconds_;
	}


	/// <summary>
	/// これだけ時間使って思考しよう、と思ってる設定時間。
	/// </summary>
	/// <param name="value"></param>
	inline void SetPlanPayOwnSeconds(int value) {
		this->m_planPayOwnSeconds_ = value;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	inline void IncreasePlanPayOwnSeconds(int value) {
		this->m_planPayOwnSeconds_ += value;
	}


	/// <summary>
	/// 思考の最大延長時間
	/// </summary>
	/// <returns></returns>
	inline int GetSaidaiEnchoTime() const {
		return this->m_saidaiEnchoTime_;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	inline void SetSaidaiEnchoTime(int value) {
		this->m_saidaiEnchoTime_ = value;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	inline void IncreaseSaidaiEnchoTime(int value) {
		this->m_saidaiEnchoTime_ += value;
	}


	/// <summary>
	/// 思考の遊び時間
	/// </summary>
	/// <returns></returns>
	inline int GetBufferThinkSeconds() const {
		return this->m_bufferThinkSeconds_;
	}


	/// <summary>
	/// 思考の遊び時間
	/// </summary>
	/// <param name="value"></param>
	inline void SetBufferThinkSeconds(int value) {
		this->m_bufferThinkSeconds_ = value;
	}


	/// <summary>
	/// 思考の遊び時間
	/// </summary>
	inline void ZeroclearBufferThinkSeconds() {
		this->SetBufferThinkSeconds(0);
	}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// 少なくなっていた場合、更新します。
	/// </summary>
	/// <param name="newValue"></param>
	inline void SmallUpdate_YoteiMyTurnTime(int newValue) {
		if (newValue < this->GetPlanPayBothPlayersSeconds() ) {
			this->SetPlanPayOwnSeconds( newValue - this->GetPredictOpponentPaySeconds() );
		}
	}


	/// <summary>
	/// 大きくなっていた場合、更新します。
	/// </summary>
	/// <param name="newValue"></param>
	inline void LargeUpdate_YoteiMyTurnTime(int newValue) {
		if (this->GetPlanPayBothPlayersSeconds() < newValue)
		{
			this->SetPlanPayOwnSeconds( newValue - this->GetPredictOpponentPaySeconds() );
		}
	}


	/// <summary>
	/// 少なくなっていた場合、更新します。
	/// </summary>
	/// <param name="value"></param>
	inline void SmallUpdate_SaidaiEnchoTime(int value) {
		this->m_saidaiEnchoTime_ = std::min(
			this->m_saidaiEnchoTime_, // マキシマム時間
			value // 思考時間＋残り時間
			);
	}
};
