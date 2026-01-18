#pragma once
#include "../n220_position/n220_650_position.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "../n640_searcher/n640_500_reductions.hpp"
#include "../n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../n885_searcher/n885_040_ourCarriage.hpp"


// PvNode = false
// SplitedNode = true
// RootNode = false

/// <summary>
/// 
/// </summary>
class AdventureNodekindSplitedNodeNonPv : public AdventureNodekindAbstract {


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
	virtual ScoreNumber explorePlain_10a520b500c500d500e500f500g(
		OurCarriage& ourCarriage,
		Position& pos,
		Flashlight* pFlashlight,//サーチスタック
		ScoreNumber alpha,
		ScoreNumber beta,
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
		SplitedNode** ppSplitedNode,
		Flashlight** ppFlashlight,
		Move& bestMove,
		Move& threatMove,
		ScoreIndex& bestScore,
		Move& ttMove,
		Move& excludedMove,
		ScoreIndex& ttScore
		)const override {

		// initialize node

		*ppSplitedNode = (*ppFlashlight)->m_splitedNode;
		bestMove = (*ppSplitedNode)->m_bestMove;
		threatMove = (*ppSplitedNode)->m_threatMove;
		bestScore = (*ppSplitedNode)->m_bestScore;
		//tte = nullptr;
		ttMove = excludedMove = g_MOVE_NONE;
		ttScore = ScoreNone;

		Evaluation09 evaluation;
		evaluation.evaluate(pos, *ppFlashlight);

		assert(-ScoreInfinite < (*ppSplitedNode)->m_bestScore && 0 < (*ppSplitedNode)->m_moveCount);

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
	inline void explorePlain_10a520b500c500d500e500f500g200h200i_updateMaxPly(
		Monkey** ppThisThread,
		const Flashlight* pFlashlight) const override
	{
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
	virtual inline Move explorePlain_n200n400_getTtMove(
		OurCarriage& ourCarriage,
		const TTEntry* pTtEntry,
		Position& pos) const override
	{
		return pTtEntry != nullptr ?
			UtilMoveStack::Move16toMove(pTtEntry->GetMove(), pos) :
			g_MOVE_NONE;
	}


	/// <summary>
	/// 非PVノードの場合☆（＾ｑ＾）
	/// </summary>
	/// <param name="pTtEntry"></param>
	/// <param name="beta"></param>
	/// <param name="ttScore"></param>
	/// <returns></returns>
	virtual inline bool getCondition_n200n450n500(
		const TTEntry* pTtEntry,
		ScoreNumber beta,
		ScoreNumber ttScore) const override
	{
		return  beta <= ttScore ?
			(pTtEntry->GetBoundKind() & Bound::BoundLower)
			:
			(pTtEntry->GetBoundKind() & Bound::BoundUpper);
	}


	/// <summary>
	///		<pre>
	/// internal iterative deepening
	/// 
	///		- PVノードか、そうでないかで手続きが変わるぜ☆！（＾ｑ＾）
	///		</pre>
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
	virtual inline void explorePlain_10a520b500c500d500e500f500g200h800i_internalIterativeDeepening(
		const Depth depth,
		Move& ttMove,
		bool& inCheck,
		ScoreNumber& beta,
		Flashlight** ppFlashlight,
		OurCarriage& ourCarriage,
		Position& pos,
		ScoreNumber& alpha,
		const TTEntry** ppTtEntry,//セットされるぜ☆
		Key& posKey) const override
	{
		if (
			// 非PVノードの場合、８倍☆
			(8 * OnePly) <= depth
			&& ttMove.IsNone()
			// 非PVノードの場合、さらに条件☆
			&& (
				!inCheck && beta <= (*ppFlashlight)->m_staticEval + static_cast<ScoreNumber>(256)
				)
			)
		{
			//const Depth d = depth - 2 * OnePly - (PVNode ? Depth0 : depth / 4);
			// 非PVノードの場合☆
			const Depth d = depth / 2;

			(*ppFlashlight)->m_skipNullMove = true;

			//────────────────────────────────────────────────────────────────────────────────
			// 探索☆？（＾ｑ＾）
			//────────────────────────────────────────────────────────────────────────────────
			// 非PVノード☆
			g_NODEKIND_PROGRAMS[NodeKind::No2_NonPV]->explorePlain_10a520b500c500d500e500f500g(
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
	virtual inline ScoreNumber explorerPlain_10a520b500c500d500e500f500g200h850i_getBeta(
		ScoreNumber beta) const override
	{
		// 非PVノードの場合☆（＾ｑ＾）
		return beta;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="depth"></param>
	/// <param name="score"></param>
	/// <param name="bestScore"></param>
	/// <param name="singularExtensionNode"></param>
	/// <param name="excludedMove"></param>
	/// <param name="pTtEntry"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g200h900i_beforeLoopSplitPointStart(
		Move& ttMove,
		const Depth depth,
		ScoreNumber& score,
		ScoreNumber& bestScore,
		bool& singularExtensionNode,
		Move& excludedMove,
		const TTEntry* pTtEntry) const override
	{
		// ルートでない場合はこういう感じ☆（＾ｑ＾）
		score = bestScore;
		singularExtensionNode = false;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="mp"></param>
	/// <returns></returns>
	virtual inline Move explorePlain_10a520b500c500d500e500f500g200h950i_getNextMove(
		NextmoveEvent& mp) const override
	{
		// スプリットポイントの場合
		return mp.GetNextMove_SplitedNode();
	};


	/// <summary>
	/// スプリット・ポイントかどうかで変わる手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="ci"></param>
	/// <param name="moveCount"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g300h500i_loopHeader(
		bool& isContinue,
		Position& pos,
		Move& move,
		const CheckInfo& ci,
		int& moveCount,
		SplitedNode** ppSplitedNode) const override
	{
		if (!
			(
				pos.getTurn()==Color::Black
				?
				pos.IsPseudoLegalMoveIsLegal<false, false,Color::Black,Color::White>(move, ci.m_pinned)
				:
				pos.IsPseudoLegalMoveIsLegal<false, false,Color::White,Color::Black>(move, ci.m_pinned)
			)
		) {
			isContinue = true;
			return;
		}
		moveCount = ++(*ppSplitedNode)->m_moveCount;
		(*ppSplitedNode)->m_mutex.unlock();
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="move"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g300h600i_loopHeader(
		bool& isContinue,
		const OurCarriage& ourCarriage,
		const Move& move) const override
	{
		// 非ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="moveCount"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g300h700i_displayInfo(
		OurCarriage& ourCarriage,
		int& moveCount) const override
	{
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
	virtual inline const Depth getPredictedDepth_n290n500(
		Depth& newDepth,
		const Depth depth,
		int& moveCount) const override
	{
		// 非PVノードのとき
		return newDepth - g_reductions.DoReduction_NotPvNode(depth, moveCount);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="ci"></param>
	/// <param name="moveCount"></param>
	virtual inline void explorePlain_n400n600_continue(
		bool& isContinue,
		Position& pos,
		Move& move,
		const CheckInfo& ci,
		int& moveCount) const override
	{
		// ルートノード、スプリットポイントはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 本筋かどうか判定するぜ（＾～＾）
	/// </summary>
	/// <param name="moveCount"></param>
	virtual inline bool explorePlain_10a520b500c500d500e500f500g400h700i_isPvMove(
		int moveCount) const override
	{
		return false;	// 非PVノードだぜ☆（＾ｑ＾）
	}


	/// <summary>
	/// スプリット・ポイントか、PVノードかで手続きが変わるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="move"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g400h800i_setMove(
		Move move,
		Flashlight** ppFlashlight) const override
	{
		// 非PVノードだぜ☆（＾ｑ＾）
		(*ppFlashlight)->m_currentMove = move;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="captureOrPawnPromotion"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="movesSearched"></param>
	/// <param name="move"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g400h900i_memoryVariationMove(
		bool& captureOrPawnPromotion,
		int& playedMoveCount,
		Move movesSearched[64],
		Move& move) const override
	{
		// スプリットポイントではスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// Pvノードかどうかで手続きが変わるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="ppFlashlight"></param>
	/// <param name="depth"></param>
	/// <param name="moveCount"></param>
	/// <param name="cutNode"></param>
	virtual inline void setReduction_n530(
		Flashlight** ppFlashlight,
		const Depth depth,
		int& moveCount,
		const bool cutNode) const override
	{
		// 非Pvノードのとき☆！（＾ｑ＾）
		(*ppFlashlight)->m_reduction = g_reductions.DoReduction_NotPvNode(depth, moveCount);
		if (cutNode)
		{
			(*ppFlashlight)->m_reduction += Depth::OnePly;
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="isPVMove"></param>
	/// <param name="alpha"></param>
	/// <param name="score"></param>
	/// <param name="beta"></param>
	/// <param name="newDepth"></param>
	/// <param name="givesCheck"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g600h900i_betaLargeRecursiveSearch(
		OurCarriage& ourCarriage,
		bool& isPVMove,
		ScoreNumber& alpha,
		ScoreNumber& score,
		ScoreNumber& beta,
		Depth& newDepth,
		bool& givesCheck,
		Position& pos,
		Flashlight** ppFlashlight) const override
	{
		// 非PVノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="score"></param>
	/// <param name="beta"></param>
	/// <returns></returns>
	virtual inline bool isBetaLarge_n620(
		ScoreNumber& score,
		ScoreNumber& beta) const override
	{
		// 非ルートノードの場合☆（＾ｑ＾）
		return score < beta;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage"></param>
	/// <param name="move"></param>
	/// <param name="isPVMove">本筋の指し手かどうかかなあ（＾～＾）？</param>
	/// <param name="alpha"></param>
	/// <param name="score"></param>
	/// <param name="pos"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g700h600i_findRootNode(
		OurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		ScoreNumber& alpha,
		ScoreNumber& score,
		Position& pos) const override
	{
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
	/// <param name="score"></param>
	/// <param name="pos"></param>
	/// <param name="bestScore"></param>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestMove"></param>
	/// <param name="beta"></param>
	virtual inline void explorePlain_10a520b500c500d500e500f500g700h700i_updateAlpha(
		bool& isBreak,
		OurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		ScoreNumber& alpha,
		ScoreNumber& score,
		Position& pos,
		ScoreNumber& bestScore,
		SplitedNode** ppSplitedNode,
		Move& bestMove,
		ScoreNumber& beta) const override
	{
		if (bestScore < score) {
			bestScore = (*ppSplitedNode)->m_bestScore = score;

			if (alpha < score) {
				bestMove = (*ppSplitedNode)->m_bestMove = move;

				// PVノードではない場合☆（＾ｑ＾）
				// fail high
				(*ppSplitedNode)->m_isUselessNode = true;
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
	/// <param name="bestScore"></param>
	/// <param name="beta"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="alpha"></param>
	/// <param name="bestMove"></param>
	/// <param name="threatMove"></param>
	/// <param name="moveCount"></param>
	/// <param name="mp"></param>
	/// <param name="cutNode"></param>
	inline void explorePlain_10a520b500c500d500e500f500g700h750i_forkNewMonkey(
		bool& isBreak,
		OurCarriage& ourCarriage,
		const Depth depth,
		Monkey** ppThisThread,
		ScoreNumber& bestScore,
		ScoreNumber& beta,
		Position& pos,
		Flashlight** ppFlashlight,
		ScoreNumber& alpha,
		Move& bestMove,
		Move& threatMove,
		int& moveCount,
		NextmoveEvent& mp,
		const bool cutNode) const override
	{
		// スプリット・ポイントはスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual inline bool isReturn_10a520b500c500d500e500f500g800h400i() const override
	{
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
	/// <param name="bestScore"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="beta"></param>
	/// <param name="posKey"></param>
	/// <param name="depth"></param>
	/// <param name="bestMove"></param>
	/// <param name="inCheck"></param>
	/// <param name="pos"></param>
	/// <param name="movesSearched"></param>
	inline void explorePlain_10a520b500c500d500e500f500g800h500i_workAtReturn(
		int& moveCount,
		Move& excludedMove,
		OurCarriage& ourCarriage,
		ScoreNumber& alpha,
		Flashlight** ppFlashlight,//サーチスタック
		ScoreNumber& bestScore,
		int& playedMoveCount,
		ScoreNumber& beta,
		Key& posKey,
		const Depth depth,
		Move& bestMove,
		bool& inCheck,
		Position& pos,
		Move movesSearched[64]) const override
	{
		// スプリット・ポイントはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bestMoveExists"></param>
	/// <returns></returns>
	inline Bound getBound_n800n500(bool bestMoveExists) const override
	{
		return Bound::BoundUpper;
	}
};


/// <summary>
/// 
/// </summary>
extern AdventureNodekindSplitedNodeNonPv g_NODEKIND_SPLITEDNODE_NON_PV;

