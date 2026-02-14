#pragma once
#include "../n220_position/n220_650_position.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "../n640_searcher/n640_500_reductions.hpp"
#include "../n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"


// PvNode = true
// MonkeySplitedPlace = true
// RootNode = false

/// <summary>
/// 
/// </summary>
class AdventureNodekindMonkeySplitedPlacePv : public AdventureNodekindAbstract
{


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pos"></param>
	/// <param name="pFlashlight"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	/// <param name="depth"></param>
	/// <param name="cutNode"></param>
	/// <returns></returns>
	virtual Sweetness explorePlain_10i(
		MuzGameEngineStorageModel& ourCarriage,
		Position& pos,
		Flashlight* pFlashlight,//サーチスタック
		Sweetness alpha,
		Sweetness beta,
		const Depth depth,
		const bool cutNode
		) const override;


	/// <summary>
	/// 非PVノードはassertをするぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void explorePlain_10i1010j_alphaIsBetaMinusOne(
		Sweetness alpha,
		Sweetness beta
		) const override {
		assert(alpha == beta - 1);
	}


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
	/// ルートノードか、それ以外かで　値が分かれるぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pTtEntry"></param>
	/// <param name="pos"></param>
	virtual inline std::unique_ptr<Move> explorePlain_10i1110j_getTtMove(
		MuzGameEngineStorageModel& ourCarriage,
		const TTEntry* pTtEntry,
		Position& pos) const override
	{
		return pTtEntry != nullptr
			?
				std::make_unique<Move>(UtilMoveStack::Move16toMove(pTtEntry->GetMove(), pos))
			:
				std::make_unique<Move>(g_MOVE_NONE)
			;
	}


	/// <summary>
	/// PVノードの場合☆（＾ｑ＾）
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
		return pTtEntry->GetBoundKind() == Bound::BoundExact;
	}


	/// <summary>
	/// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="returnSweetness"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="depth"></param>
	/// <param name="eval"></param>
	/// <param name="beta"></param>
	/// <param name="ttMove"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorePlain_10i1260j_byEasyGoingMonkey(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		MuzGameEngineStorageModel& ourCarriage,
		const Depth depth,
		Sweetness& eval,
		Sweetness& beta,
		Move& ttMove,
		Position& pos,
		Flashlight** ppFlashlight
		)const override {
		// PVノードはスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="returnSweetness"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="depth"></param>
	/// <param name="beta"></param>
	/// <param name="eval"></param>
	virtual inline void explorePlain_10i1270j_byEasyGoingMonkey(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		Flashlight** ppFlashlight,
		const Depth depth,
		Sweetness& beta,
		Sweetness& eval
		)const override {
		// PVノードはスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="returnSweetness"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="ppFlashlight"></param>
	/// <param name="depth"></param>
	/// <param name="beta"></param>
	/// <param name="eval"></param>
	/// <param name="pos"></param>
	/// <param name="st"></param>
	/// <param name="alpha"></param>
	/// <param name="cutNode"></param>
	/// <param name="threatMove"></param>
	virtual inline void explorePlain_10i1280j_byEasyGoingMonkey(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		MuzGameEngineStorageModel& ourCarriage,
		Flashlight** ppFlashlight,
		const Depth depth,
		Sweetness& beta,
		Sweetness& eval,
		Position& pos,
		StateInfo& st,
		Sweetness& alpha,
		const bool cutNode,
		Move& threatMove
		)const override {
		// PVノードはスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="depth"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="beta"></param>
	/// <param name="move"></param>
	/// <param name="pos"></param>
	/// <param name="ttMove"></param>
	/// <param name="st"></param>
	/// <param name="sweetness"></param>
	/// <param name="cutNode"></param>
	virtual inline void explorePlain_10i1290j_byEasyGoingMonkey(
		bool& isReturnWithSweetness,
		MuzGameEngineStorageModel& ourCarriage,
		const Depth& depth,
		Flashlight** ppFlashlight,
		Sweetness& beta,
		Move& move,
		Position& pos,
		Move& ttMove,
		StateInfo& st,
		Sweetness& sweetness,
		const bool cutNode
		)const override {
		// 非PVノードはスルー☆！（＾ｑ＾）
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
		MuzGameEngineStorageModel& ourCarriage,
		Position& pos,
		Sweetness& alpha,
		const TTEntry** ppTtEntry,//セットされるぜ☆
		Key& posKey
		)const override
	{
		// internal iterative deepening
		if (
			// PVノードの場合、５倍☆
			(5 * OnePly) <= depth
			&& ttMove.IsNone()
			)
		{
			//const Depth d = depth - 2 * OnePly - (PVNode ? Depth0 : depth / 4);
			// PVノードの場合☆
			const Depth d = depth - 2 * OnePly;

			(*ppFlashlight)->m_skipNullMove = true;

			//────────────────────────────────────────────────────────────────────────────────
			// ［几帳面な猿］が探索☆（＾ｑ＾）
			//────────────────────────────────────────────────────────────────────────────────
			g_NODEKIND_PROGRAMS[MonkeyPersonalities::Meticulous]->explorePlain_10i(
				ourCarriage, pos, (*ppFlashlight), alpha, beta, d, true);

			(*ppFlashlight)->m_skipNullMove = false;

			(*ppTtEntry) = ourCarriage.m_tt.Probe(posKey);
			ttMove = ((*ppTtEntry) != nullptr ?
				UtilMoveStack::Move16toMove((*ppTtEntry)->GetMove(), pos) :
				g_MOVE_NONE);
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
		// PVノードの場合☆（＾ｑ＾）
		return -Sweetness::SweetnessInfinite;
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
		const MuzGameEngineStorageModel& ourCarriage,
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
		MuzGameEngineStorageModel& ourCarriage,
		int& moveCount
		) const override {
		// 非ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 無駄枝狩り☆（＾▽＾）
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
	virtual inline void explorePlain_10i2070j_futilityPruning(
		bool& isContinue,
		MuzGameEngineStorageModel& ourCarriage,
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
		Sweetness& beta
		) const override {
		// PVノードはスルー☆！（＾ｑ＾）
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
		// PVノードのとき
		return newDepth - g_reductions.DoReduction_PvNode(depth, moveCount);
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
		MuzGameEngineStorageModel& ourCarriage,
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

		// PVノードだぜ☆！（＾ｑ＾）
		isPVMoveRef = (moveCount == 1);
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
		// Pvノードのとき☆！（＾ｑ＾）
		(*ppFlashlight)->m_reduction = g_reductions.DoReduction_PvNode(depth, moveCount);
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
		MuzGameEngineStorageModel& ourCarriage,
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
		MuzGameEngineStorageModel& ourCarriage,
		Move& move,
		bool& isPVMove,
		Sweetness& alpha,
		Sweetness& sweetness,
		Position& pos,
		Sweetness& bestSweetness,
		MonkeySplitedPlace** ppMonkeySplitedPlace,
		Move& bestMove,
		Sweetness& beta) const override
	{
		if (bestSweetness < sweetness) {
			bestSweetness = (*ppMonkeySplitedPlace)->m_bestSweetness = sweetness;

			if (alpha < sweetness) {
				bestMove = (*ppMonkeySplitedPlace)->m_bestMove = move;

				// （＾ｑ＾）PVノードの場合☆
				if (sweetness < beta) {
					alpha = (*ppMonkeySplitedPlace)->m_alpha = sweetness;
				}
				else {
					// fail high
					(*ppMonkeySplitedPlace)->m_isUselessNode = true;
					isBreak = true;
					return;
				}
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
		MuzGameEngineStorageModel& ourCarriage,
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
		MuzGameEngineStorageModel& ourCarriage,
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
		return bestMoveExists ? Bound::BoundExact : Bound::BoundUpper;
	}
};


/// <summary>
/// 
/// </summary>
extern AdventureNodekindMonkeySplitedPlacePv g_NODEKIND_MONKEYSPLITEDPLACE_METICULOUS_MONKEY;

