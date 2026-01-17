#pragma once
#include "n885_310_adventureBattlefieldQsearchAbstract.hpp"


/// <summary>
/// 主となる読み筋
/// </summary>
class AdventureBattlefieldQsearchPv : public AdventureBattlefieldQsearchAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void DoAssert(
		ScoreNumber alpha,
		ScoreNumber beta
		) const override {
		//スルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="alpha"></param>
	virtual inline void SetOldAlpha(
		ScoreNumber& oldAlpha,
		ScoreNumber alpha
		) const override {
		oldAlpha = alpha;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppTtEntry"></param>
	/// <param name="beta"></param>
	/// <param name="ttScore"></param>
	/// <returns></returns>
	virtual inline bool GetCondition01(
		const TTEntry** ppTtEntry,
		ScoreNumber beta,
		ScoreNumber ttScore
		) const override {
		// PVノードのとき☆（＾ｑ＾）
		return (*ppTtEntry)->GetBoundKind() == Bound::BoundExact;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="bestScore"></param>
	virtual inline void SetAlpha(
		ScoreNumber& alpha,
		ScoreNumber bestScore
		) const override {
		// PVノードのとき☆（＾ｑ＾）
		if (alpha < bestScore) {
			alpha = bestScore;
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="INCHECK"></param>
	/// <param name="givesCheck"></param>
	/// <param name="move"></param>
	/// <param name="ttMove"></param>
	/// <param name="futilityScore"></param>
	/// <param name="futilityBase"></param>
	/// <param name="pos"></param>
	/// <param name="beta"></param>
	/// <param name="bestScore"></param>
	/// <param name="depth"></param>
	virtual inline void DoFutilityPruning01(
		bool& isContinue,
		bool& INCHECK,
		bool& givesCheck,
		Move& move,
		Move& ttMove,
		ScoreNumber& futilityScore,
		ScoreNumber& futilityBase,
		Position& pos,
		ScoreNumber& beta,
		ScoreNumber& bestScore,
		const Depth depth
		)const override {
		// スルーだぜ☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="INCHECK"></param>
	/// <param name="evasionPrunable"></param>
	/// <param name="move"></param>
	/// <param name="ttMove"></param>
	/// <param name="pos"></param>
	virtual inline void DoContinue01(
		bool& isContinue,
		bool& INCHECK,
		bool& evasionPrunable,
		Move& move,
		Move& ttMove,
		Position& pos
		)const {
		// スルーだぜ☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="score"></param>
	/// <param name="beta"></param>
	/// <param name="alpha"></param>
	/// <param name="bestMove"></param>
	/// <param name="posKey"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="ttDepth"></param>
	/// <param name="move"></param>
	virtual inline void DoByNewScore(
		bool& isReturnWithScore,
		ScoreNumber& returnScore,
		OurCarriage& ourCarriage,
		ScoreNumber& score,
		ScoreNumber& beta,
		ScoreNumber& alpha,
		Move& bestMove,
		Key& posKey,
		Flashlight** ppFlashlight,
		Depth ttDepth,
		Move move
		)const override {
		if (
			// PVノードのときは条件付きで別手続きがあるぜ☆（＾ｑ＾）
			score < beta
			) {
			alpha = score;
			bestMove = move;
		}
		else {
			// fail high
			ourCarriage.m_tt.Store(
				posKey,
				ourCarriage.ConvertScoreToTT(score, (*ppFlashlight)->m_ply),
				Bound::BoundLower,
				ttDepth,
				move,
				(*ppFlashlight)->m_staticEval
			);
			isReturnWithScore = true;
			returnScore = score;
			return;
			//return score;
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="bestScore"></param>
	/// <returns></returns>
	virtual inline Bound GetBound01(
		ScoreNumber& oldAlpha,
		ScoreNumber& bestScore
		)const override {
		return (oldAlpha < bestScore) ?
			Bound::BoundExact
			:
			Bound::BoundUpper
			;
	}
};
