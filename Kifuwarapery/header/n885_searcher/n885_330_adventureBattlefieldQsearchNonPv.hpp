#pragma once


#include "n885_310_adventureBattlefieldQsearchAbstract.hpp"


/// <summary>
/// 
/// </summary>
class AdventureBattlefieldQsearchNonPv : public AdventureBattlefieldQsearchAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void DoAssert(
		ScoreIndex alpha,
		ScoreIndex beta
		) const override {
		assert(alpha == beta - 1);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="alpha"></param>
	virtual inline void SetOldAlpha(
		ScoreIndex& oldAlpha,
		ScoreIndex alpha
		) const override {
		//スルー☆！（＾ｑ＾）
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
		ScoreIndex beta,
		ScoreIndex ttScore
		) const override {
		// NonPVノードのとき☆（＾ｑ＾）
		return beta <= ttScore ?
			((*ppTtEntry)->GetBoundKind() & BoundLower)
			:
			((*ppTtEntry)->GetBoundKind() & BoundUpper);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="bestScore"></param>
	virtual inline void SetAlpha(
		ScoreIndex& alpha,
		ScoreIndex bestScore
		) const override {
		// スルーするぜ☆！（＾ｑ＾）
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
		ScoreIndex& futilityScore,
		ScoreIndex& futilityBase,
		Position& pos,
		ScoreIndex& beta,
		ScoreIndex& bestScore,
		const Depth depth
		)const override {
		// 非PVノードのとき☆（＾ｑ＾）
		if (!INCHECK // 駒打ちは王手回避のみなので、ここで弾かれる。
			&& !givesCheck
			&& move != ttMove)
		{
			futilityScore =
				futilityBase + PieceScore::GetCapturePieceScore(pos.GetPiece(move.To()));
			if (move.IsPromotion()) {
				futilityScore += PieceScore::GetPromotePieceScore(move.GetPieceTypeFrom());
			}

			if (futilityScore < beta) {
				bestScore = std::max(bestScore, futilityScore);
				isContinue = true;
				return;
			}

			// todo: ＭｏｖｅＰｉｃｋｅｒ のオーダリングで SEE してるので、ここで SEE するの勿体無い。
			if (futilityBase < beta
				&& depth < Depth0
				&&
				(
					pos.GetTurn()==Color::Black
					?
					pos.GetSee1<Color::Black,Color::White>(move, beta - futilityBase)
					:
					pos.GetSee1<Color::White,Color::Black>(move, beta - futilityBase)
					)
				<= ScoreZero)
			{
				bestScore = std::max(bestScore, futilityBase);
				isContinue = true;
				return;
			}
		}
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
		)const override {
		// PVノードでない場合☆（＾ｑ＾）
		if ((!INCHECK || evasionPrunable)
			&& move != ttMove
			&& (!move.IsPromotion() || move.GetPieceTypeFrom() != N01_Pawn)
			&& pos.GetSeeSign(move) < 0)
		{
			isContinue = true;
			return;
			//continue;
		}
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
		ScoreIndex& returnScore,
		OurCarriage& ourCarriage,
		ScoreIndex& score,
		ScoreIndex& beta,
		ScoreIndex& alpha,
		Move& bestMove,
		Key& posKey,
		Flashlight** ppFlashlight,
		Depth ttDepth,
		Move move
		)const override {
		// fail high
		ourCarriage.m_tt.Store(posKey, ourCarriage.ConvertScoreToTT(score, (*ppFlashlight)->m_ply), Bound::BoundLower,
			ttDepth, move, (*ppFlashlight)->m_staticEval);
		isReturnWithScore = true;
		returnScore = score;
		return;
		//return score;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="bestScore"></param>
	/// <returns></returns>
	virtual inline Bound GetBound01(
		ScoreIndex& oldAlpha,
		ScoreIndex& bestScore
		)const override {
		return Bound::BoundUpper;
	}
};
