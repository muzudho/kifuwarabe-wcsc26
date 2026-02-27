#pragma once
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n223_move____/n223_200_depth.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "../n640_searcher/n640_500_reductions.hpp"
#include "../n755_whistle_/n755_100_WhistleRoot.hpp"
#include "../n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../../src/n55a_game_engine/muz_game_engine_storage_model.hpp"
#include "../n887_nodeKind/n887_100_adventurePlainNodekindRoot.hpp"


// PvNode = true
// MonkeySplitedPlace = false
// IsRootNode = true

/// <summary>
/// 
/// </summary>
class AdventureNodekindRoot : public AdventureNodekindAbstract {


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
		// PVノードはスルー☆！（＾ｑ＾）
		assert(alpha == beta - 1);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="ttSweetness"></param>
	/// <param name="isGotoSplitPointStart"></param>
	/// <param name="moveCount"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="inCheck"></param>
	/// <param name="pos"></param>
	/// <param name="ppMonkeySplitedPlace"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="bestMove"></param>
	/// <param name="threatMove"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="excludedMove"></param>
	virtual inline void explorePlain_10i1020j_initializeNode(
		Move& ttMove,
		Sweetness& ttSweetness,
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
		Move& excludedMove) const override
	{
		// ［一番乗りする猿］はスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 千日手による探索打切りの判断
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="ppFlashlight"></param>
	virtual inline std::pair<bool, Sweetness> explorePlain_10i1080j_isStopByRepetetion(
		Position& pos,
		MuzGameEngineStorageModel& ourCarriage,
		Flashlight** ppFlashlight
		)const override
	{
		// ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
		return std::make_pair(false, SweetnessNone);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="returnSweetness"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void explorePlain_10i1090j_checkAlpha(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		Flashlight** ppFlashlight,
		Sweetness& alpha,
		Sweetness& beta
		)const override {
		// ルートには無いぜ☆（＾ｑ＾）！
		//UNREACHABLE;
	}


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
		return std::make_unique<Move>(ourCarriage.m_rootMoves[ourCarriage.m_pvIdx].m_pv_[0]);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="ttSweetness"></param>
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="returnSweetness"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pTtEntry"></param>
	/// <param name="depth"></param>
	/// <param name="beta"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorePlain_10i1180j_killerMove(
		Move& ttMove,
		Sweetness& ttSweetness,
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		MuzGameEngineStorageModel& ourCarriage,
		const TTEntry* pTtEntry,
		const Depth depth,
		Sweetness& beta,
		Flashlight** ppFlashlight) const override
	{
		// ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
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
	/// 一手詰めならそのバナナ採用☆（＾～＾）
	/// </summary>
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="returnSweetness"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="inCheck"></param>
	/// <param name="move"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="posKey"></param>
	/// <param name="depth"></param>
	/// <param name="bestMove"></param>
	virtual inline void explorePlain_10i1190j_returnIfMateMoveIn1Ply(
		bool& isReturnWithSweetness,
		Move& bestMove,
		Sweetness& returnSweetness,
		MuzGameEngineStorageModel& ourCarriage,
		bool& inCheck,
		Move& move,
		Position& pos,
		Flashlight** ppFlashlight,
		Sweetness& bestSweetness,
		Key& posKey,
		const Depth depth) const override
	{
		// ルートノードはスルー☆！（＾ｑ＾）
		//UNREACHABLE;
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
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
			// ルートの場合、５倍☆
			(5 * OnePly) <= depth // 深さが５以上で☆
			&&
			ttMove.IsNone()	// トランスポジション・テーブルに指し手がない場合☆
			)
		{
			//const Depth d = depth - 2 * OnePly - (PVNode ? Depth0 : depth / 4);
			// PVノードの場合☆
			const Depth d = depth - 2 * OnePly; // 2手戻した深さ☆

			(*ppFlashlight)->m_skipNullMove = true;

			//────────────────────────────────────────────────────────────────────────────────
			// 根だから、［几帳面な猿］が探索☆（＾ｑ＾）
			//────────────────────────────────────────────────────────────────────────────────
			g_NODEKIND_PROGRAMS[MonkeyPersonalities::Meticulous]->explorePlain_10i(
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
		// PVノードの場合☆（＾ｑ＾）
		return -Sweetness::SweetnessInfinite;
	}


	/// <summary>
	///		<pre>
	/// ［スプリット・ポイント］の開始地点
	///		</pre>
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
		const TTEntry* pTtEntry) const override
	{
		// ルートはこういう感じ☆（＾ｑ＾）
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
		// 非スプリットポイントの場合
		return mp.GetNextMove_NonMonkeySplitedPlace();
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
			++moveCount;
	}


	/// <summary>
	/// 無駄枝狩り☆（＾▽＾）
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
	/// <param name="ppMonkeySplitedPlace"></param>
	virtual inline void lock_10i400j170k300L(
		MonkeySplitedPlace** ppMonkeySplitedPlace
		) const override
	{
		// 非スプリット・ポイントではスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppMonkeySplitedPlace"></param>
	/// <param name="bestSweetness"></param>
	virtual inline void lockAndUpdateBestSweetness_10i400j170k200L(
		MonkeySplitedPlace** ppMonkeySplitedPlace,
		Sweetness& bestSweetness
		) const override {
		// 非スプリット・ポイントではスルー☆！（＾ｑ＾）
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
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
		) const override
	{

		// PVノードだぜ☆！（＾ｑ＾）
		isPVMoveRef = (moveCount == 1);
		(*ppFlashlight)->m_currentMove = move;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="ppMonkeySplitedPlace"></param>
	virtual inline void updateAlpha_10i500j500k200L(
		Sweetness& alpha,
		MonkeySplitedPlace** ppMonkeySplitedPlace
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
	/// <param name="willFullDepthSearch"></param>
	/// <param name="alpha"></param>
	/// <param name="ppMonkeySplitedPlace"></param>
	virtual inline void explorePlain_10i3010j_updateAlpha(
		bool& willFullDepthSearch,
		Sweetness& alpha,
		MonkeySplitedPlace** ppMonkeySplitedPlace
		)const override {
		// 非スプリットノードはスルー☆！（＾ｑ＾）
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
		// ルートノードの場合☆（＾ｑ＾）
		return true;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppMonkeySplitedPlace"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="alpha"></param>
	virtual inline void explorePlain_10i3050j_getAlpha(
		MonkeySplitedPlace** ppMonkeySplitedPlace,
		Sweetness& bestSweetness,
		Sweetness& alpha
		)const override {
		// 非スプリット・ポイントはスルー☆！（＾ｑ＾）
	}


	/// <summary>
	/// 非スプリット・ポイントの場合☆（＾ｑ＾）
	/// </summary>
	/// <param name="isBreak"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
		Sweetness& beta
		)const override {

		if (bestSweetness < sweetness) {
			bestSweetness = sweetness;

			if (alpha < sweetness) {
				bestMove = move;

				// （＾ｑ＾）ＰＶノードの場合☆
				if (sweetness < beta) {
					alpha = sweetness;
				}
				else {
					isBreak = true;
					return;
				}
			}
		}
	}


	/// <summary>
	/// 非スプリットポイントでだけ実行するぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="isBreak"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
	virtual inline void explorePlain_10i3080j_forkNewMonkeyIfPossible(
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
		const bool cutNode) const override
	{

		if (
			// ある程度の深さになってから（＾～＾）
			ourCarriage.m_pub.GetMinSplitDepth() <= depth
			&&
			// ヒマしてる猿のポインターがあるか（＾～＾）？
			ourCarriage.m_pub.GetBoredMonkey(*ppThisThread)
			&&
			// ［一緒に走る猿の数］が上限に達してなければ（＾～＾）
			(*ppThisThread)->m_numberOfMonkeysRunningTogether < g_MaxNumberOfMonkeysRunningTogether)
		{
			assert(bestSweetness < beta);
			(*ppThisThread)->ForkNewMonkey<MuzGameEngineStorageModel::FakeSplit>(
				pos,
				*ppFlashlight,
				alpha,
				beta,
				bestSweetness,
				bestMove,
				depth,
				threatMove,
				moveCount,
				mp,
                &g_WHISTLE_ROOT,	// 猿生成時、ルート用のホイッスルを渡すぜ☆（＾ｑ＾）
				cutNode
				);

			if (beta <= bestSweetness) {
				isBreak = true;
				return;
			}
		}

	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	virtual inline bool isReturnBeforeLastProcess_10i4010j() const override {
		// 非スプリット・ポイントは　ステップ２０を実行する前に途中抜けはしないぜ☆（＾ｑ＾）
		return false;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bestMoveExists"></param>
	/// <returns></returns>
	virtual inline Bound getBound_10i800j200k600L(bool bestMoveExists) const override {
		return bestMoveExists ? Bound::BoundExact : Bound::BoundUpper;
	}
};


/// <summary>
/// 
/// </summary>
extern AdventureNodekindRoot g_NODEKIND_ROOT;
