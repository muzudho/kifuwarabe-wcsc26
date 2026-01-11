#pragma once

#include "../n520_evaluate/n520_700_evaluation09.hpp"
#include "../n560_timeMgr_/n560_100_limitsOfThinking.hpp"


// 依存関係の都合を解消。
class Rucksack;


/// <summary>
/// 時間管理だぜ☆（＾ｑ＾）
/// </summary>
class TimeManager {


public:


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
	/// <param name="pRucksack"></param>
	void Initialize(
		bool& isMoveTime0Clear,
		const LimitsOfThinking& limits,
		const Ply currentPly,
		const Color us,
		Rucksack* pRucksack);


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
	inline bool IsTimeBudgetOver(const int elapsed) { return this->GetThinkSecondsBudget() < elapsed; }


	/// <summary>
	/// まだ反復深化していい時間が残ってるか☆？（＾ｑ＾）
	/// 
	///		- 消費時間が、使っていい時間の60%を下回っている場合。
	/// </summary>
	/// <param name="elapsed"></param>
	/// <returns></returns>
	inline bool IsTimeOk_CanIterativeDeeping(const int elapsed) {
		return elapsed < this->GetThinkSecondsBudget() * 60 / 100;
	}


	/// <summary>
	/// 新しく生まれてくる下級戦士の寿命☆（＾ｑ＾）
	/// </summary>
	/// <returns></returns>
	inline int GetWarriorLifeTime() { return this->GetThinkSecondsBudget() / 16; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="elapsed"></param>
	/// <returns></returns>
	inline bool CanNotNextIteration(const int elapsed) {
		// 使っていい時間の62%が、消費時間（ミリ秒）に満たない場合。
		return (this->GetThinkSecondsBudget() * 62) / 100 < elapsed;
	}


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


	//────────────────────────────────────────────────────────────────────────────────
	// 使っていい思考時間
	//────────────────────────────────────────────────────────────────────────────────


	/// <summary>
	///		<pre>
	/// 元の名前：ＡｖａｉｌａｂｌｅＴｉｍｅ
	/// なんだかんだで、使っちゃうつもりの時間☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <returns></returns>
	int GetThinkSecondsBudget() const {
		// 予定思考タイム　＋　遊びタイム
		return this->GetYoteiBothTurnTime()
			//+ this->GetTemeBonusTime()
			+ this->GetSikoAsobiTime();
	}


	/*
	//────────────────────────────────────────────────────────────────────────────────
	// 手目に応じて調整される時間☆
	//────────────────────────────────────────────────────────────────────────────────
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


	//────────────────────────────────────────────────────────────────────────────────
	// 相手の手番（Oppo teban）で使おうと思っている思考時間
	//────────────────────────────────────────────────────────────────────────────────


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline int GetYosouOppoTurnTime() const {
		return this->m_yosouOppoTurnTime_;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	inline void SetYosouOppoTurnTime(int value) {
		this->m_yosouOppoTurnTime_ = value;
	}


	/// <summary>
	/// 
	/// </summary>
	inline void ZeroclearYosouOppoTurnTime()
	{
		this->m_yosouOppoTurnTime_ = 0;
	}


	//────────────────────────────────────────────────────────────────────────────────
	// 自分の手番と相手の手番の両方（Both turn）で使おうと思っている思考時間
	//────────────────────────────────────────────────────────────────────────────────


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline int GetYoteiBothTurnTime() const {
		return this->m_yoteiMyTurnTime_ + this->m_yosouOppoTurnTime_;
	}


	/// <summary>
	/// 自分の手番（My turn）で使おうと思っている思考時間
	/// </summary>
	/// <returns></returns>
	inline int GetYoteiMyTurnTime() const {
		return this->m_yoteiMyTurnTime_;
	}


	/// <summary>
	/// これだけ時間使って思考しよう、と思ってる設定時間。
	/// </summary>
	/// <param name="value"></param>
	inline void SetYoteiMyTurnTime(int value) {
		this->m_yoteiMyTurnTime_ = value;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	inline void IncreaseYoteiMyTurnTime(int value) {
		this->m_yoteiMyTurnTime_ += value;
	}


	/// <summary>
	/// 少なくなっていた場合、更新します。
	/// </summary>
	/// <param name="newValue"></param>
	inline void SmallUpdate_YoteiMyTurnTime(int newValue) {
		if (newValue < this->GetYoteiBothTurnTime() ) {
			this->SetYoteiMyTurnTime( newValue - this->GetYosouOppoTurnTime() );
		}
	}


	/// <summary>
	/// 大きくなっていた場合、更新します。
	/// </summary>
	/// <param name="newValue"></param>
	inline void LargeUpdate_YoteiMyTurnTime(int newValue) {
		if (this->GetYoteiBothTurnTime() < newValue)
		{
			this->SetYoteiMyTurnTime( newValue - this->GetYosouOppoTurnTime() );
		}
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
	/// 少なくなっていた場合、更新します。
	/// </summary>
	/// <param name="value"></param>
	inline void SmallUpdate_SaidaiEnchoTime(int value) {
		this->m_saidaiEnchoTime_ = std::min(
			this->m_saidaiEnchoTime_, // マキシマム時間
			value // 思考時間＋残り時間
			);
	}


	/// <summary>
	/// 思考の遊び時間
	/// </summary>
	/// <returns></returns>
	inline int GetSikoAsobiTime() const {
		return this->m_sikoAsobiTime_;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	inline void SetSikoAsobiTime(int value) {
		this->m_sikoAsobiTime_ = value;
	}


	/// <summary>
	/// 
	/// </summary>
	inline void ZeroclearSikoAsobiTime() {
		this->SetSikoAsobiTime( 0);
	}


private:


	//────────────────────────────────────────────────────────────────────────────────
	// 手目に応じて調整される時間☆
	//────────────────────────────────────────────────────────────────────────────────
	//int m_temeBonusTime_;

	
	/// <summary>
	/// 相手の手番（Oppo turn）で使おうと思っている思考時間
	/// </summary>
	int m_yosouOppoTurnTime_;

	/// <summary>
	///		<pre>
	/// 自分の手番（my turn）で使おうと思っている思考時間
	/// 元の名前：ＯｐｔｉｍｕｍＳｅａｒｃｈＴｉｍｅ
	///		</pre>
	/// </summary>
	int m_yoteiMyTurnTime_;

	/// <summary>
	///		<pre>
	/// 思考の最大延長時間
	/// 元の名前：ＭａｘｉｍｕｍＳｅａｒｃｈＴｉｍｅ
	///		</pre>
	/// </summary>
	int m_saidaiEnchoTime_;

	/// <summary>
	///		<pre>
	/// 思考の遊び時間
	/// 元の名前：ｕｎｓｔａｂｌｅＰＶＥｘｔｒａＴｉｍｅ
	///		</pre>
	/// </summary>
	int m_sikoAsobiTime_;
};
