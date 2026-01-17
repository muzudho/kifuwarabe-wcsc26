#pragma once
#include "../n220_position/n220_650_position.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "../n640_searcher/n640_500_reductions.hpp"
#include "../n755_sword___/n755_120_SwordNonPv.hpp"
#include "../n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../n885_searcher/n885_040_ourCarriage.hpp"


// PvNode = false
// SplitedNode = false
// RootNode = false

/// <summary>
/// 
/// </summary>
class AdventureNodekindNonPv : public AdventureNodekindAbstract {


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
	virtual ScoreIndex explorePlain_n10(
		OurCarriage& ourCarriage,
		Position& pos,
		Flashlight* pFlashlight,//サーチスタック
		ScoreIndex alpha,
		ScoreIndex beta,
		const Depth depth,
		const bool cutNode
		) const override;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isGotoSplitPointStart"></param>
	/// <param name="pos"></param>
	/// <param name="ppSplitedNode"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="bestMove"></param>
	/// <param name="threatMove"></param>
	/// <param name="bestScore"></param>
	/// <param name="ttMove"></param>
	/// <param name="excludedMove"></param>
	/// <param name="ttScore"></param>
	virtual inline void ExplorerPlainStep1a1InitializeNode(
		bool& isGotoSplitPointStart,
		Position& pos,
		SplitedNode** ppSplitedNode,
		Flashlight** ppFlashlight,
		Move& bestMove,
		Move& threatMove,
		ScoreIndex& bestScore,
		Move& ttMove,
		Move& excludedMove,
		ScoreIndex& ttScore) const override
	{
		// 非スプリット・ポイントはスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppThisThread"></param>
	/// <param name="pFlashlight"></param>
	inline void explorePlain_n90_updateMaxPly(
		Monkey** ppThisThread,
		const Flashlight* pFlashlight) const override
	{
		// 非PVノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// ルートノードか、それ以外かで　値が分かれるぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="pTtEntry"></param>
	/// <param name="pos"></param>
	virtual inline void explorePlain_n110(
		Move& ttMove,
		OurCarriage& ourCarriage,
		const TTEntry* pTtEntry,
		Position& pos
		)const override
	{
		ttMove = pTtEntry != nullptr ?
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
	virtual inline bool GetConditionInStep4y(
		const TTEntry* pTtEntry,
		ScoreIndex& beta,
		ScoreIndex& ttScore
		) const override {
		return  beta <= ttScore ?
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
	virtual inline void explorePlain_n130_internalIterativeDeepening(
		const Depth depth,
		Move& ttMove,
		bool& inCheck,
		ScoreIndex& beta,
		Flashlight** ppFlashlight,
		OurCarriage& ourCarriage,
		Position& pos,
		ScoreIndex& alpha,
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
				!inCheck && beta <= (*ppFlashlight)->m_staticEval + static_cast<ScoreIndex>(256)
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
			// 非PVノードの場合☆
			g_NODEKIND_PROGRAMS[NodeKind::No2_NonPV]->explorePlain_n10(
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
	virtual inline ScoreIndex getBeta_n140(
		ScoreIndex beta
		) const override {
		// 非PVノードの場合☆（＾ｑ＾）
		return beta;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="mp"></param>
	/// <returns></returns>
	virtual inline Move getNextMove_n160(
		NextmoveEvent& mp
		) const override {
		// 非スプリットポイントの場合
		return mp.GetNextMove_NonSplitedNode();
	};


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
	virtual inline void explorePlain_n150_beforeLoop_splitPointStart(
		Move& ttMove,
		const Depth depth,
		ScoreIndex& score,
		ScoreIndex& bestScore,
		bool& singularExtensionNode,
		Move& excludedMove,
		const TTEntry* pTtEntry
		)const override
	{
		// ルートでない場合はこういう感じ☆（＾ｑ＾）
		score = bestScore;
		singularExtensionNode = 8 * Depth::OnePly <= depth
			&& !ttMove.IsNone()
			&& excludedMove.IsNone()
			&& (pTtEntry->GetBoundKind() & Bound::BoundLower)
			&& depth - 3 * Depth::OnePly <= pTtEntry->GetDepth();
	}


	/// <summary>
	/// スプリット・ポイントかどうかで変わる手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="ci"></param>
	/// <param name="moveCount"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void explorePlain_n180_loopHeader(
		bool& isContinue,
		Position& pos,
		Move& move,
		const CheckInfo& ci,
		int& moveCount,
		SplitedNode** ppSplitedNode
		) const override {
		++moveCount;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="ourCarriage"></param>
	/// <param name="move"></param>
	virtual inline void explorePlain_n200_loopHeader(
		bool& isContinue,
		const OurCarriage& ourCarriage,
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
	virtual inline void explorePlain_n220_loopHeader(
		OurCarriage& ourCarriage,
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
	virtual inline const Depth GetPredictedDepthInStep13a(
		Depth& newDepth,
		const Depth depth,
		int& moveCount
		) const override {
		// 非PVノードのとき
		return newDepth - g_reductions.DoReduction_NotPvNode(depth, moveCount);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	virtual inline void LockInStep13a(
		SplitedNode** ppSplitedNode
		) const override
	{
		// 非スプリット・ポイントではスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestScore"></param>
	virtual inline void LockAndUpdateBestScoreInStep13a(
		SplitedNode** ppSplitedNode,
		ScoreIndex& bestScore
		) const override {
		// 非スプリット・ポイントではスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 本筋かどうか判定するぜ（＾～＾）
	/// </summary>
	/// <param name="moveCount"></param>
	virtual inline bool explorePlain_n280_isPvMove(
		int moveCount) const override
	{
		return false;	// 非PVノードだぜ☆！（＾ｑ＾）
	}


	/// <summary>
	/// スプリット・ポイントか、PVノードかで手続きが変わるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="move"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorePlain_n300_setMove(
		Move move,
		Flashlight** ppFlashlight) const override
	{
		// 非PVノードだぜ☆！（＾ｑ＾）
		(*ppFlashlight)->m_currentMove = move;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void UpdateAlphaInStep15(
		ScoreIndex& alpha,
		SplitedNode** ppSplitedNode
		) const override {

		// 非スプリットノードではスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// Pvノードかどうかで手続きが変わるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="ppFlashlight"></param>
	/// <param name="depth"></param>
	/// <param name="moveCount"></param>
	/// <param name="cutNode"></param>
	virtual inline void SetReductionInStep15(
		Flashlight** ppFlashlight,
		const Depth depth,
		int& moveCount,
		const bool cutNode
		) const override {
		// 非Pvノードのとき☆！（＾ｑ＾）
		(*ppFlashlight)->m_reduction = g_reductions.DoReduction_NotPvNode(depth, moveCount);
		if (cutNode) {
			(*ppFlashlight)->m_reduction += Depth::OnePly;
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="doFullDepthSearch"></param>
	/// <param name="alpha"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void ExplorerPlainStep16a(
		bool& doFullDepthSearch,
		ScoreIndex& alpha,
		SplitedNode** ppSplitedNode
		)const override {
		// 非スプリットノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
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
	virtual inline void explorePlain_n400(
		OurCarriage& ourCarriage,
		bool& isPVMove,
		ScoreIndex& alpha,
		ScoreIndex& score,
		ScoreIndex& beta,
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
	/// <param name="score"></param>
	/// <param name="beta"></param>
	/// <returns></returns>
	virtual inline bool IsBetaLargeAtStep16c(
		ScoreIndex& score,
		ScoreIndex& beta
		) const override {
		// 非ルートノードの場合☆（＾ｑ＾）
		return score < beta;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestScore"></param>
	/// <param name="alpha"></param>
	virtual inline void ExplorerPlainStep18a(
		SplitedNode** ppSplitedNode,
		ScoreIndex& bestScore,
		ScoreIndex& alpha
		)const override {
		// 非スプリット・ポイントはスルー☆！（＾ｑ＾）
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
	virtual inline void explorePlain_n440(
		OurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		ScoreIndex& alpha,
		ScoreIndex& score,
		Position& pos
		) const override {
		// 非ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
	}


	/// <summary>
	/// 非スプリット・ポイントの場合☆（＾ｑ＾）
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
	virtual inline void explorePlain_n460(
		bool& isBreak,
		OurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		ScoreIndex& alpha,
		ScoreIndex& score,
		Position& pos,
		ScoreIndex& bestScore,
		SplitedNode** ppSplitedNode,
		Move& bestMove,
		ScoreIndex& beta
		)const override {

		if (bestScore < score) {
			bestScore = score;

			if (alpha < score) {
				bestMove = move;

				// 非PVノードの場合☆
				isBreak = true;
				return;
			}
		}

	}


	/// <summary>
	/// 非スプリットポイントでだけ実行するぜ☆（＾ｑ＾）
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
	virtual inline void explorePlain_n480_forkNewMonkey(
		bool& isBreak,
		OurCarriage& ourCarriage,
		const Depth depth,
		Monkey** ppThisThread,
		ScoreIndex& bestScore,
		ScoreIndex& beta,
		Position& pos,
		Flashlight** ppFlashlight,
		ScoreIndex& alpha,
		Move& bestMove,
		Move& threatMove,
		int& moveCount,
		NextmoveEvent& mp,
		const bool cutNode
		)const override {

		if (ourCarriage.m_monkiesPub.GetMinSplitDepth() <= depth
			&& ourCarriage.m_monkiesPub.GetAvailableSlave(*ppThisThread)
			&& (*ppThisThread)->m_splitedNodesSize < g_MaxSplitedNodesPerThread)
		{
			assert(bestScore < beta);
			(*ppThisThread)->ForkNewMonkey<OurCarriage::FakeSplit>(
				pos,
				*ppFlashlight,
				alpha,
				beta,
				bestScore,
				bestMove,
				depth,
				threatMove,
				moveCount,
				mp,
				&g_SWORD_NON_PV,
				cutNode
				);

			if (beta <= bestScore) {
				isBreak = true;
				return;
			}
		}

	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual inline bool getReturn_beforeN500() const override {
		// 非スプリット・ポイントは　ステップ２０を実行する前に途中抜けはしないぜ☆（＾ｑ＾）
		return false;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bestMoveExists"></param>
	/// <returns></returns>
	inline Bound GetBoundAtStep20(bool bestMoveExists) const override {
		return Bound::BoundUpper;
	}
};


/// <summary>
/// 
/// </summary>
extern AdventureNodekindNonPv g_NODEKIND_NON_PV;
