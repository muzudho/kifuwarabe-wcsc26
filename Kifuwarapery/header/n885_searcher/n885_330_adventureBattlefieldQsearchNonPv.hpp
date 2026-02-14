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
		Sweetness alpha,
		Sweetness beta
		) const override {
		assert(alpha == beta - 1);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="alpha"></param>
	virtual inline void SetOldAlpha(
		Sweetness& oldAlpha,
		Sweetness alpha
		) const override {
		//スルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppTtEntry"></param>
	/// <param name="beta"></param>
	/// <param name="ttSweetness"></param>
	/// <returns></returns>
	virtual inline bool GetCondition01(
		const TTEntry** ppTtEntry,
		Sweetness beta,
		Sweetness ttSweetness
		) const override {
		// NonPVノードのとき☆（＾ｑ＾）
		return beta <= ttSweetness ?
			((*ppTtEntry)->GetBoundKind() & BoundLower)
			:
			((*ppTtEntry)->GetBoundKind() & BoundUpper);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="bestSweetness"></param>
	virtual inline void SetAlpha(
		Sweetness& alpha,
		Sweetness bestSweetness
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
	/// <param name="futilitySweetness"></param>
	/// <param name="futilityBase"></param>
	/// <param name="pos"></param>
	/// <param name="beta"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="depth"></param>
	virtual inline void DoFutilityPruning01(
		bool& isContinue,
		bool& INCHECK,
		bool& givesCheck,
		Move& move,
		Move& ttMove,
		Sweetness& futilitySweetness,
		Sweetness& futilityBase,
		Position& pos,
		Sweetness& beta,
		Sweetness& bestSweetness,
		const Depth depth
		)const override {
		// 非PVノードのとき☆（＾ｑ＾）
		if (!INCHECK // 駒打ちは王手回避のみなので、ここで弾かれる。
			&& !givesCheck
			&& move != ttMove)
		{
			futilitySweetness =
				futilityBase + PieceSweetness::getSweetnessByCapturePiece(pos.GetPiece(move.To()));
			if (move.IsPromotion()) {
				futilitySweetness += PieceSweetness::getSweetnessByPromotePiece(move.GetPieceTypeFrom());
			}

			if (futilitySweetness < beta) {
				bestSweetness = std::max(bestSweetness, futilitySweetness);
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
				<= SweetnessZero)
			{
				bestSweetness = std::max(bestSweetness, futilityBase);
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
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="returnSweetness"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="sweetness"></param>
	/// <param name="beta"></param>
	/// <param name="alpha"></param>
	/// <param name="bestMove"></param>
	/// <param name="posKey"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="ttDepth"></param>
	/// <param name="move"></param>
	virtual inline void doByNewSweetness(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		MuzGameEngineStorage& ourCarriage,
		Sweetness& sweetness,
		Sweetness& beta,
		Sweetness& alpha,
		Move& bestMove,
		Key& posKey,
		Flashlight** ppFlashlight,
		Depth ttDepth,
		Move move
		)const override {
		// fail high
		ourCarriage.m_tt.Store(posKey, ourCarriage.ConvertSweetnessToTT(sweetness, (*ppFlashlight)->m_ply), Bound::BoundLower,
			ttDepth, move, (*ppFlashlight)->m_staticEval);
		isReturnWithSweetness = true;
		returnSweetness = sweetness;
		return;
		//return sweetness;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="bestSweetness"></param>
	/// <returns></returns>
	virtual inline Bound GetBound01(
		Sweetness& oldAlpha,
		Sweetness& bestSweetness
		)const override {
		return Bound::BoundUpper;
	}
};
