#pragma once
#include "../n220_position/n220_650_position.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "../n640_searcher/n640_500_reductions.hpp"
#include "../n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../../src/game_engine_layer/game_engine_storage.hpp"


// PvNode = false
// MonkeySplitedPlace = true
// RootNode = false

/// <summary>
/// 
/// </summary>
class AdventureNodekindMonkeySplitedPlaceNonPv : public AdventureNodekindAbstract
{


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="pos"></param>
	/// <param name="pFlashlight"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	/// <param name="depth"></param>
	/// <param name="cutNode"></param>
	/// <returns></returns>
	virtual Sweetness explorePlain_10i(
		GameEngineStorageOurCarriage& ourCarriage,
		Position& pos,
		Flashlight* pFlashlight,//サーチスタック
		Sweetness alpha,
		Sweetness beta,
		const Depth depth,
		const bool cutNode
		) const override;

	/*
	// スプリット・ポイントのみ実行☆（＾ｑ＾）
	virtual inline void DoStep1a(
		bool& isGotoSplitPointStart,
		int& moveCount,
		int& playedMoveCount,
		bool& inCheck,
		Position& pos,
		MonkeySplitedPlace** ppMonkeySplitedPlace,
		Flashlight** ppFlashlight,
		Move& bestMove,
		Move& threatMove,
		Sweetness& bestSweetness,
		Move& ttMove,
		Move& excludedMove,
		Sweetness& ttSweetness
		)const override {

		// initialize node

		*ppMonkeySplitedPlace = (*ppFlashlight)->m_monkeySplitedPlace;
		bestMove = (*ppMonkeySplitedPlace)->m_bestMove;
		threatMove = (*ppMonkeySplitedPlace)->m_threatMove;
		bestSweetness = (*ppMonkeySplitedPlace)->m_bestSweetness;
		//tte = nullptr;
		ttMove = excludedMove = g_MOVE_NONE;
		ttSweetness = SweetnessNone;

		Evaluation09 evaluation;
		evaluation.evaluate(pos, *ppFlashlight);

		assert(-SweetnessInfinite < (*ppMonkeySplitedPlace)->m_bestSweetness && 0 < (*ppMonkeySplitedPlace)->m_moveCount);

		isGotoSplitPointStart = true;
		return;
		//goto split_point_start;
	}
	//*/


	/// <summary>
	/// 非PVノードはassertをするぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="ppThisThread"></param>
	/// <param name="pFlashlight"></param>
	inline void explorePlain_10i1040j_updateMaxPly(
		Monkie** ppThisThread,
		const Flashlight* pFlashlight
		)const override {
		// PVノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// ルートノードか、それ以外かで　値が分かれるぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="pTtEntry"></param>
	/// <param name="pos"></param>
	virtual inline std::unique_ptr<Move> explorePlain_10i1110j_getTtMove(
		GameEngineStorageOurCarriage& ourCarriage,
		const TTEntry* pTtEntry,
		Position& pos
		)const override
	{
		return pTtEntry != nullptr
			?
				std::make_unique<Move>(UtilMoveStack::Move16toMove(pTtEntry->GetMove(), pos))
			:
				std::make_unique<Move>(g_MOVE_NONE)
			;
	}


	/// <summary>
	/// 非PVノードの場合☆（＾ｑ＾）
	/// </summary>
	/// <param name="pTtEntry"></param>
	/// <param name="beta"></param>
	/// <param name="ttSweetness"></param>
	/// <returns></returns>
	virtual inline bool getCondition_10i200j240k100L(
		const TTEntry* pTtEntry,
		Sweetness& beta,
		Sweetness& ttSweetness
		) const override {
		return  beta <= ttSweetness ?
			(pTtEntry->GetBoundKind() & Bound::BoundLower)
			:
			(pTtEntry->GetBoundKind() & Bound::BoundUpper);
	}


	/// <summary>
	/// PVノードか、そうでないかで手続きが変わるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="depth"></param>
	/// <param name="ttMove"></param>
	/// <param name="inCheck"></param>
	/// <param name="beta"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="pos"></param>
	/// <param name="alpha"></param>
	/// <param name="ppTtEntry"></param>
	/// <param name="posKey"></param>
	virtual inline void explorerPlain_10i1300j_internalIterativeDeepening(
		const Depth depth,
		Move& ttMove,
		bool& inCheck,
		Sweetness& beta,
		Flashlight** ppFlashlight,
		GameEngineStorageOurCarriage& ourCarriage,
		Position& pos,
		Sweetness& alpha,
		const TTEntry** ppTtEntry,//セットされるぜ☆
		Key& posKey
		)const override
	{
		// internal iterative deepening
		if (
			// 非PVノードの場合、８倍☆
			(8 * OnePly) <= depth
			&& ttMove.IsNone()
			// 非PVノードの場合、さらに条件☆
			&& (
				!inCheck && beta <= (*ppFlashlight)->m_staticEval + static_cast<Sweetness>(256)
				)
			)
		{
			//const Depth d = depth - 2 * OnePly - (PVNode ? Depth0 : depth / 4);
			// 非PVノードの場合☆
			const Depth d = depth / 2;

			(*ppFlashlight)->m_skipNullMove = true;

			//────────────────────────────────────────────────────────────────────────────────
			// ［大雑把な性格の猿］が引き続き探索☆（＾ｑ＾）
			//────────────────────────────────────────────────────────────────────────────────
			g_NODEKIND_PROGRAMS[MonkeyPersonalities::EasyGoing]->explorePlain_10i(
				ourCarriage, pos, (*ppFlashlight), alpha, beta, d, true);

			(*ppFlashlight)->m_skipNullMove = false;

			(*ppTtEntry) = ourCarriage.m_tt.Probe(posKey);
			ttMove = (
				(*ppTtEntry) != nullptr
				?
				UtilMoveStack::Move16toMove((*ppTtEntry)->GetMove(), pos)
				:
				g_MOVE_NONE
				);
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="beta"></param>
	/// <returns></returns>
	virtual inline Sweetness getBeta_10i1310j(
		Sweetness beta
		) const override {
		// 非PVノードの場合☆（＾ｑ＾）
		return beta;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="depth"></param>
	/// <param name="sweetness"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="singularExtensionNode"></param>
	/// <param name="excludedMove"></param>
	/// <param name="pTtEntry"></param>
	virtual inline void explorePlain_10i1320j_atWelcomeEnd(
		Move& ttMove,
		const Depth depth,
		Sweetness& sweetness,
		Sweetness& bestSweetness,
		bool& singularExtensionNode,
		Move& excludedMove,
		const TTEntry* pTtEntry
	)const override
	{
		// ルートでない場合はこういう感じ☆（＾ｑ＾）
		sweetness = bestSweetness;
		singularExtensionNode = false;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="mp"></param>
	/// <returns></returns>
	virtual inline Move getNextMove_10i2010j(
		NextmoveEvent& mp
		) const override {
		// スプリットポイントの場合
		return mp.GetNextMove_MonkeySplitedPlace();
	};


	/// <summary>
	/// スプリット・ポイントかどうかで変わる手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="ci"></param>
	/// <param name="moveCount"></param>
	/// <param name="ppMonkeySplitedPlace"></param>
	virtual inline void explorePlain_10i2020j_resetSweetness(
		bool& isContinue,
		Position& pos,
		Move& move,
		const CheckInfo& ci,
		int& moveCount,
		MonkeySplitedPlace** ppMonkeySplitedPlace
	) const override {
		// DoStep11c
		if (!
			(
				pos.GetTurn()==Color::Black
				?
				pos.IsPseudoLegalMoveIsLegal<false, false,Color::Black,Color::White>(move, ci.m_pinned)
				:
				pos.IsPseudoLegalMoveIsLegal<false, false,Color::White,Color::Black>(move, ci.m_pinned)
			)
		) {
			isContinue = true;
			return;
		}
		moveCount = ++(*ppMonkeySplitedPlace)->m_moveCount;
		(*ppMonkeySplitedPlace)->m_mutex.unlock();
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="move"></param>
	virtual inline void explorePlain_10i2030j_isRootMoveEnd(
		bool& isContinue,
		const GameEngineStorageOurCarriage& ourCarriage,
		const Move& move
		)const override {
		// 非ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="moveCount"></param>
	virtual inline void explorerPlain_10i2040j_displayInfo(
		GameEngineStorageOurCarriage& ourCarriage,
		int& moveCount
		) const override {
		// 非ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// PVノードか、そうでないかで変わるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="newDepth"></param>
	/// <param name="depth"></param>
	/// <param name="moveCount"></param>
	/// <returns></returns>
	virtual inline const Depth getPredictedDepth_10i400j170k100L(
		Depth& newDepth,
		const Depth depth,
		int& moveCount
		) const override {
		// 非PVノードのとき
		return newDepth - g_reductions.DoReduction_NotMeticulousMonkey(depth, moveCount);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="ci"></param>
	/// <param name="moveCount"></param>
	virtual inline void explorePlain_10i2080_isContinue(
		bool& isContinue,
		Position& pos,
		Move& move,
		const CheckInfo& ci,
		int& moveCount
		) const override {
		// ルートノード、スプリットポイントはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// スプリット・ポイントか、PVノードかで手続きが変わるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="captureOrPawnPromotion"></param>
	/// <param name="inCheck"></param>
	/// <param name="dangerous"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="move"></param>
	/// <param name="ttMove"></param>
	/// <param name="depth"></param>
	/// <param name="moveCount"></param>
	/// <param name="threatMove"></param>
	/// <param name="pos"></param>
	/// <param name="ppMonkeySplitedPlace"></param>
	/// <param name="newDepth"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="beta"></param>
	/// <param name="ci"></param>
	/// <param name="isPVMoveRef"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="movesSearched"></param>
	virtual inline void explorePlain_10i2090j_updateCurrentMove(
		bool& isContinue,
		GameEngineStorageOurCarriage& ourCarriage,
		bool& captureOrPawnPromotion,
		bool& inCheck,
		bool& dangerous,
		Sweetness& bestSweetness,
		Move& move,
		Move& ttMove,
		const Depth depth,
		int& moveCount,
		Move& threatMove,
		Position& pos,
		MonkeySplitedPlace** ppMonkeySplitedPlace,
		Depth& newDepth,
		Flashlight** ppFlashlight,
		Sweetness& beta,
		const CheckInfo& ci,
		bool& isPVMoveRef,
		int& playedMoveCount,
		Move movesSearched[64]
		)const override {

		// 非PVノードだぜ☆（＾ｑ＾）
		isPVMoveRef = false;
		(*ppFlashlight)->m_currentMove = move;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="captureOrPawnPromotion"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="movesSearched"></param>
	/// <param name="move"></param>
	virtual inline void explorerPlain_10i2100j_updateMoveSearched(
		bool& captureOrPawnPromotion,
		int& playedMoveCount,
		Move movesSearched[64],
		Move& move
		) const override {

		// スプリットポイントではスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// Pvノードかどうかで手続きが変わるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="ppFlashlight"></param>
	/// <param name="depth"></param>
	/// <param name="moveCount"></param>
	/// <param name="cutNode"></param>
	virtual inline void setReduction_10i500j500k100L(
		Flashlight** ppFlashlight,
		const Depth depth,
		int& moveCount,
		const bool cutNode
		) const override {
		// 非Pvノードのとき☆！（＾ｑ＾）
		(*ppFlashlight)->m_reduction = g_reductions.DoReduction_NotMeticulousMonkey(depth, moveCount);
		if (cutNode) {
			(*ppFlashlight)->m_reduction += Depth::OnePly;
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="isPVMove"></param>
	/// <param name="alpha"></param>
	/// <param name="sweetness"></param>
	/// <param name="beta"></param>
	/// <param name="newDepth"></param>
	/// <param name="givesCheck"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorerPlain_10i3030j_getSweetnessIfMeticulous(
		GameEngineStorageOurCarriage& ourCarriage,
		bool& isPVMove,
		Sweetness& alpha,
		Sweetness& sweetness,
		Sweetness& beta,
		Depth& newDepth,
		bool& givesCheck,
		Position& pos,
		Flashlight** ppFlashlight
		)const override {
		// 非PVノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sweetness"></param>
	/// <param name="beta"></param>
	/// <returns></returns>
	virtual inline bool isBetaLarge_10i600j140k100L(
		Sweetness& sweetness,
		Sweetness& beta
		) const override {
		// 非ルートノードの場合☆（＾ｑ＾）
		return sweetness < beta;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="move"></param>
	/// <param name="isPVMove">本筋の指し手かどうかかなあ（＾～＾）？</param>
	/// <param name="alpha"></param>
	/// <param name="sweetness"></param>
	/// <param name="pos"></param>
	virtual inline void explorerPlain_10i3060j_bestMovePlyChanges(
		GameEngineStorageOurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		Sweetness& alpha,
		Sweetness& sweetness,
		Position& pos
		) const override {
		// 非ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// スプリット・ポイントの場合☆（＾ｑ＾）
	/// </summary>
	/// <param name="isBreak"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="move"></param>
	/// <param name="isPVMove"></param>
	/// <param name="alpha"></param>
	/// <param name="sweetness"></param>
	/// <param name="pos"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="ppMonkeySplitedPlace"></param>
	/// <param name="bestMove"></param>
	/// <param name="beta"></param>
	virtual inline void explorePlain_10i3070j_getBestUpdateAlpha(
		bool& isBreak,
		GameEngineStorageOurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		Sweetness& alpha,
		Sweetness& sweetness,
		Position& pos,
		Sweetness& bestSweetness,
		MonkeySplitedPlace** ppMonkeySplitedPlace,
		Move& bestMove,
		Sweetness& beta
		)const override {

		if (bestSweetness < sweetness) {
			bestSweetness = (*ppMonkeySplitedPlace)->m_bestSweetness = sweetness;

			if (alpha < sweetness) {
				bestMove = (*ppMonkeySplitedPlace)->m_bestMove = move;

				// PVノードではない場合☆（＾ｑ＾）
				// fail high
				(*ppMonkeySplitedPlace)->m_isUselessNode = true;
				isBreak = true;
				return;
			}
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isBreak"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="depth"></param>
	/// <param name="ppThisThread"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="beta"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="alpha"></param>
	/// <param name="bestMove"></param>
	/// <param name="threatMove"></param>
	/// <param name="moveCount"></param>
	/// <param name="mp"></param>
	/// <param name="cutNode"></param>
	inline void explorePlain_10i3080j_forkNewMonkeyIfPossible(
		bool& isBreak,
		GameEngineStorageOurCarriage& ourCarriage,
		const Depth depth,
		Monkie** ppThisThread,
		Sweetness& bestSweetness,
		Sweetness& beta,
		Position& pos,
		Flashlight** ppFlashlight,
		Sweetness& alpha,
		Move& bestMove,
		Move& threatMove,
		int& moveCount,
		NextmoveEvent& mp,
		const bool cutNode
		)const override {
		// スプリット・ポイントはスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual inline bool isReturnBeforeLastProcess_10i4010j() const override {
		// スプリット・ポイントは　ステップ２０を実行する前に途中抜けするぜ☆（＾ｑ＾）
		return true;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="moveCount"></param>
	/// <param name="excludedMove"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="alpha"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="beta"></param>
	/// <param name="posKey"></param>
	/// <param name="depth"></param>
	/// <param name="bestMove"></param>
	/// <param name="inCheck"></param>
	/// <param name="pos"></param>
	/// <param name="movesSearched"></param>
	inline void explorePlain_10i4020j_backwardProcess(
		int& moveCount,
		Move& excludedMove,
		GameEngineStorageOurCarriage& ourCarriage,
		Sweetness& alpha,
		Flashlight** ppFlashlight,//サーチスタック
		Sweetness& bestSweetness,
		int& playedMoveCount,
		Sweetness& beta,
		Key& posKey,
		const Depth depth,
		Move& bestMove,
		bool& inCheck,
		Position& pos,
		Move movesSearched[64]
		)const override {
		// スプリット・ポイントはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bestMoveExists"></param>
	/// <returns></returns>
	inline Bound getBound_10i800j200k600L(bool bestMoveExists) const override {
		return Bound::BoundUpper;
	}
};


/// <summary>
/// 
/// </summary>
extern AdventureNodekindMonkeySplitedPlaceNonPv g_NODEKIND_MONKEYSPLITEDPLACE_EASY_GOING_MONKEY;

