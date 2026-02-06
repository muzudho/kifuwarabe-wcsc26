#pragma once
#include <utility>  // std::pair用
#include <memory>  // unique_ptr 用
#include "../n640_searcher/n640_510_futilityMargins.hpp"
#include "../n640_searcher/n640_520_futilityMoveCounts.hpp"
#include "../n885_searcher/n885_340_adventureBattlefieldQsearchPrograms.hpp"
#include "../n886_repeType/n886_500_rtArray.hpp"//FIXME:


/// <summary>
/// 同じファイル内の後ろの方でクラス定義があるとき☆（＾ｑ＾）
/// </summary>
class AdventureNodekindAbstract;
extern AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[];
extern RepetitionTypeModels g_repetitionTypes;


/// <summary>
/// 大冒険する平野だぜ（＾▽＾）！
/// </summary>
class AdventureNodekindAbstract {


public:


	/// <summary>
	/// 平野へ大冒険に出るぜ☆（＾ｑ＾）
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
		OurCarriage& ourCarriage,
		Position& pos,
		Flashlight* pFlashlight,//サーチスタック
		Sweetness alpha,
		Sweetness beta,
		const Depth depth,
		const bool cutNode
		) const = 0;


	/// <summary>
	/// 非PVノードはassertをするぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void explorePlain_10i1010j_assertAtFirst(
		Sweetness alpha,
		Sweetness beta
		) const {
		// 非PVノードのみ実行☆！（＾ｑ＾）
		assert(alpha == beta - 1);
	}


	/// <summary>
	///		<pre>
	/// initialize node
	/// 
	///		- スプリット・ポイントのみ実行☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="ttSweetness"></param>
	/// <param name="isGotoSplitPointStart"></param>
	/// <param name="moveCount"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="inCheck"></param>
	/// <param name="pos"></param>
	/// <param name="ppSplitedNode"></param>
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
		SplitedNode** ppSplitedNode,
		Flashlight** ppFlashlight,
		Move& bestMove,
		Move& threatMove,
		Sweetness& bestSweetness,
		Move& excludedMove) const
	{

		// initialize node

		*ppSplitedNode = (*ppFlashlight)->m_splitedNode;
		bestMove = (*ppSplitedNode)->m_bestMove;
		threatMove = (*ppSplitedNode)->m_threatMove;
		bestSweetness = (*ppSplitedNode)->m_bestSweetness;
		//tte = nullptr;
		ttMove = excludedMove = g_MOVE_NONE;
		ttSweetness = SweetnessNone;

		Evaluation09 evaluation;
		evaluation.evaluate(pos, *ppFlashlight);

		assert(-SweetnessInfinite < (*ppSplitedNode)->m_bestSweetness && 0 < (*ppSplitedNode)->m_moveCount);

		isGotoSplitPointStart = true;
		return;
		//goto split_point_start;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bestSweetness"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="threatMove"></param>
	/// <param name="bestMove"></param>
	virtual inline void explorePlain_10i1030j_clearMove(
		Sweetness& bestSweetness,
		Flashlight** ppFlashlight,
		Move& threatMove,
		Move& bestMove
		)const {

		bestSweetness = -SweetnessInfinite;
		(*ppFlashlight)->m_currentMove = threatMove = bestMove = ((*ppFlashlight) + 1)->m_excludedMove = g_MOVE_NONE;
		(*ppFlashlight)->m_ply = ((*ppFlashlight) - 1)->m_ply + 1;
		((*ppFlashlight) + 1)->m_skipNullMove = false;
		((*ppFlashlight) + 1)->m_reduction = Depth0;
		((*ppFlashlight) + 2)->m_killers[0] = ((*ppFlashlight) + 2)->m_killers[1] = g_MOVE_NONE;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppThisThread"></param>
	/// <param name="pFlashlight"></param>
	virtual inline void explorePlain_10i1040j_mapPly(
		Monkie** ppThisThread,
		const Flashlight* pFlashlight
		)const {
		// PVノードのみ、最大Plyの更新の可能性があるぜ☆（＾ｑ＾）
		if ((*ppThisThread)->m_maxPly < pFlashlight->m_ply) {
			(*ppThisThread)->m_maxPly = pFlashlight->m_ply;
		}
	}


	/// <summary>
	///		<pre>
	/// 千日手による探索打切りの判断
	/// 
	///		- ルートノード以外が実行するぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="ppFlashlight"></param>
	virtual inline std::pair<bool, Sweetness> explorePlain_10i1080j_isStopByRepetetion(
		Position& pos,
		OurCarriage& ourCarriage,
		Flashlight** ppFlashlight) const
	{
		// stop と最大探索深さのチェック
		return g_repetitionTypes.m_ARRAY[pos.IsRepetition(16)]->IsStop(
			//isReturnWithSweetness,
			//returnSweetness,
			&ourCarriage,
			(*ppFlashlight));
	}


	/// <summary>
	/// ルートノード以外が実行するぜ☆（＾ｑ＾）
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
		Sweetness& beta) const
	{
		// ルート以外のみで行われる手続きだぜ☆（＾ｑ＾）！
		alpha = std::max(UtilSweetness::MatedIn((*ppFlashlight)->m_ply), alpha);
		beta = std::min(UtilSweetness::MateIn((*ppFlashlight)->m_ply + 1), beta);
		if (beta <= alpha)
		{
			isReturnWithSweetness = true;
			returnSweetness = alpha;
			return;
			//return alpha;
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="excludedMove"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="posKey"></param>
	/// <param name="pos"></param>
	/// <param name="ppTtEntry"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="ttSweetness"></param>
	virtual inline Sweetness explorePlain_10i1100j_getTtSweetness(
		Move& excludedMove,
		Flashlight** ppFlashlight,
		Key& posKey,
		Position& pos,
		const TTEntry** ppTtEntry,//セットされるぜ☆（＾ｑ＾）
		OurCarriage& ourCarriage) const
	{
		// trans position table lookup
		excludedMove = (*ppFlashlight)->m_excludedMove;
		posKey = (excludedMove.IsNone() ? pos.GetKey() : pos.GetExclusionKey());
		(*ppTtEntry) = ourCarriage.m_tt.Probe(posKey);
		return ((*ppTtEntry) != nullptr ? ourCarriage.ConvertSweetnessFromTT((*ppTtEntry)->GetSweetness(), (*ppFlashlight)->m_ply) : SweetnessNone);
	}


	/// <summary>
	/// ルートノードか、それ以外かで　値が分かれるぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pTtEntry"></param>
	/// <param name="pos"></param>
	virtual inline std::unique_ptr<Move> explorePlain_10i1110j_getTtMove(
		OurCarriage& ourCarriage,
		const TTEntry* pTtEntry,
		Position& pos
		)const = 0;


	/// <summary>
	/// PVノードか、非PVノードかで実行条件が変わるぜ☆（＾ｑ＾）
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
		OurCarriage& ourCarriage,
		const TTEntry* pTtEntry,
		const Depth depth,
		Sweetness& beta,
		Flashlight** ppFlashlight) const
	{

		// ルートノード以外だけにある手続きだぜ☆（＾ｑ＾）
		if (pTtEntry != nullptr
			&& depth <= pTtEntry->GetDepth()
			&& ttSweetness != SweetnessNone // アクセス競合が起きたときのみ、ここに引っかかる。
			&& this->getCondition_10i200j240k100L(
				pTtEntry,
				beta,
				ttSweetness)
		){
			ourCarriage.m_tt.Refresh(pTtEntry);
			(*ppFlashlight)->m_currentMove = ttMove; // Move::moveNone() もありえる。

			if (beta <= ttSweetness
				&& !ttMove.IsNone()
				&& !ttMove.IsCaptureOrPawnPromotion()
				&& ttMove != (*ppFlashlight)->m_killers[0])
			{
				(*ppFlashlight)->m_killers[1] = (*ppFlashlight)->m_killers[0];
				(*ppFlashlight)->m_killers[0] = ttMove;
			}

			isReturnWithSweetness = true;
			returnSweetness = ttSweetness;
			return;
			//return ttSweetness;
		}
	}


	/// <summary>
	/// PVノードか、非PVノードかで実行条件が変わるぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="pTtEntry"></param>
	/// <param name="beta"></param>
	/// <param name="ttSweetness"></param>
	/// <returns></returns>
	virtual inline bool getCondition_10i200j240k100L(
		const TTEntry* pTtEntry,
		Sweetness& beta,
		Sweetness& ttSweetness
		) const = 0;


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
		OurCarriage& ourCarriage,
		bool& inCheck,
		Move& move,
		Position& pos,
		Flashlight** ppFlashlight,
		Sweetness& bestSweetness,
		Key& posKey,
		const Depth depth) const
	{
		// ルートノード以外だけにある手続きだぜ☆（＾ｑ＾）
#if 1
		if (!inCheck)
		{
			if (!(move =
				(
					pos.GetTurn()==Color::Black
					?
					pos.GetMateMoveIn1Ply<Color::Black,Color::White>()
					:
					pos.GetMateMoveIn1Ply<Color::White,Color::Black>()
					)				
				).IsNone()) {
				(*ppFlashlight)->m_staticEval = bestSweetness = UtilSweetness::MateIn((*ppFlashlight)->m_ply);
				ourCarriage.m_tt.Store(posKey, ourCarriage.ConvertSweetnessToTT(bestSweetness, (*ppFlashlight)->m_ply), BoundExact, depth,
					move, (*ppFlashlight)->m_staticEval);
				bestMove = move;

				isReturnWithSweetness = true;
				returnSweetness = bestSweetness;
				return;
				//return bestSweetness;
			}
		}
#endif
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isGotoIidStart"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="eval"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="pos"></param>
	/// <param name="inCheck"></param>
	/// <param name="pTtEntry"></param>
	/// <param name="ttSweetness"></param>
	/// <param name="posKey"></param>
	/// <param name="move"></param>
	virtual inline void explorePlain_10i1200j_evelSweetness(
		bool& isGotoIidStart,
		OurCarriage& ourCarriage,
		Sweetness& evalSweetness,
		Flashlight** ppFlashlight,
		Position& pos,
		bool& inCheck,
		const TTEntry* pTtEntry,
		Sweetness& ttSweetness,
		Key& posKey,
		Move& move
	)const {
		// evaluate the position statically
		Evaluation09 evaluation;
		evalSweetness = (*ppFlashlight)->m_staticEval = evaluation.evaluate(pos, (*ppFlashlight)); // Bonanza の差分評価の為、evaluate() を常に呼ぶ。
		if (inCheck) {
			evalSweetness = (*ppFlashlight)->m_staticEval = SweetnessNone;
			isGotoIidStart = true;
			return;
			//goto iid_start;
		}
		else if (pTtEntry != nullptr) {
			if (
				ttSweetness != SweetnessNone
				&&
				(
					pTtEntry->GetBoundKind()
					&
					((evalSweetness < ttSweetness) ? Bound::BoundLower : Bound::BoundUpper)
				)
			)
			{
				evalSweetness = ttSweetness;
			}
		}
		else {
			ourCarriage.m_tt.Store(posKey, SweetnessNone, BoundNone, DepthNone,
				g_MOVE_NONE, (*ppFlashlight)->m_staticEval);
		}

		// 一手前の指し手について、history を更新する。
		// todo: ここの条件はもう少し考えた方が良い。
		if ((move = ((*ppFlashlight) - 1)->m_currentMove) != g_MOVE_NULL
			&& ((*ppFlashlight) - 1)->m_staticEval != SweetnessNone
			&& (*ppFlashlight)->m_staticEval != SweetnessNone
			&& !move.IsCaptureOrPawnPromotion() // 前回(一手前)の指し手が駒取りでなかった。
			)
		{
			const Square to = move.To();
			ourCarriage.m_gains.Update(move.IsDrop(), pos.GetPiece(to), to, -((*ppFlashlight) - 1)->m_staticEval - (*ppFlashlight)->m_staticEval);
		}
	}


	/// <summary>
	///		<pre>
	/// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
	/// N02_NonPV扱いで実行する関数があるぜ、なんだこれ☆（＾ｑ＾）Qサーチは、スプリットポイントかどうかは見てないのかだぜ☆（＾ｑ＾）
	///		</pre>
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
	virtual inline void explorePlain_10i1260j_nonPV(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		OurCarriage& ourCarriage,
		const Depth depth,
		Sweetness& eval,
		Sweetness& beta,
		Move& ttMove,
		Position& pos,
		Flashlight** ppFlashlight
	)const {
		// razoring

		// 非PVノードだけが実行するぜ☆！（＾ｑ＾）
		if (depth < 4 * OnePly
			&& eval + ourCarriage.razorMargin(depth) < beta
			&& ttMove.IsNone()
			&& abs(beta) < SweetnessMateInMaxPly)
		{
			const Sweetness rbeta = beta - ourCarriage.razorMargin(depth);
			const Sweetness s = AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No2_NonPV]->ExploreAsQsearch(
				ourCarriage, false, pos, (*ppFlashlight), rbeta - 1, rbeta, Depth0);
			if (s < rbeta) {
				isReturnWithSweetness = true;
				returnSweetness = s;
				return;
				//return s;
			}
		}
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
	virtual inline void explorePlain_10i1270j_nonPV(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		Flashlight** ppFlashlight,
		const Depth depth,
		Sweetness& beta,
		Sweetness& eval
	)const {
		// static null move pruning

		// 非PVノードだけが実行するぜ☆！（＾ｑ＾）
		if (!(*ppFlashlight)->m_skipNullMove
			&& depth < 4 * OnePly
			&& beta <= eval - g_futilityMargins.m_FutilityMargins[depth][0]
			&& abs(beta) < SweetnessMateInMaxPly)
		{
			bool isReturnWithSweetness = true;
			returnSweetness = eval - g_futilityMargins.m_FutilityMargins[depth][0];
			//return eval - g_futilityMargins.m_FutilityMargins[depth][0];
			return;
		}
	}


	/// <summary>
	///		<pre>
	/// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
	/// N02_NonPV扱いで実行する関数があるぜ、なんだこれ☆（＾ｑ＾）
	///		</pre>
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
	virtual inline void explorePlain_10i1280j_nonPV(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		OurCarriage& ourCarriage,
		Flashlight** ppFlashlight,
		const Depth depth,
		Sweetness& beta,
		Sweetness& eval,
		Position& pos,
		StateInfo& st,
		Sweetness& alpha,
		const bool cutNode,
		Move& threatMove
	)const {

		// null move

		// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
		if (!(*ppFlashlight)->m_skipNullMove
			&& 2 * OnePly <= depth
			&& beta <= eval
			&& abs(beta) < SweetnessMateInMaxPly)
		{
			(*ppFlashlight)->m_currentMove = g_MOVE_NULL;
			Depth reduction = static_cast<Depth>(3) * OnePly + depth / 4;

			if (beta < eval - PieceSweetness::m_pawn) {
				reduction += OnePly;
			}

			pos.DoNullMove(true, st);
			((*ppFlashlight) + 1)->m_staticEvalRaw = (*ppFlashlight)->m_staticEvalRaw; // 評価値の差分評価の為。
			((*ppFlashlight) + 1)->m_skipNullMove = true;

			Sweetness nullSweetness = (depth - reduction < OnePly ?
				//────────────────────────────────────────────────────────────────────────────────
				// 深さが２手（先後１組）以上なら　クイックな探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				-AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No2_NonPV]->ExploreAsQsearch(
					ourCarriage, false, pos, (*ppFlashlight) + 1, -beta, -alpha, Depth0)
				:
				//────────────────────────────────────────────────────────────────────────────────
				// 深さが２手（先後１組）未満なら　ふつーの探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				-g_NODEKIND_PROGRAMS[NodeKind::No2_NonPV]->explorePlain_10i(ourCarriage, pos, (*ppFlashlight) + 1, -beta, -alpha, depth - reduction, !cutNode)
			);

			((*ppFlashlight) + 1)->m_skipNullMove = false;
			pos.DoNullMove(false, st);

			if (beta <= nullSweetness) {
				if (SweetnessMateInMaxPly <= nullSweetness) {
					nullSweetness = beta;
				}

				if (depth < 6 * OnePly) {
					isReturnWithSweetness = true;
					returnSweetness = nullSweetness;
					return;
					//return nullSweetness;
				}

				(*ppFlashlight)->m_skipNullMove = true;
				assert(Depth0 < depth - reduction);
				//────────────────────────────────────────────────────────────────────────────────
				// 探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				const Sweetness s = g_NODEKIND_PROGRAMS[NodeKind::No2_NonPV]->explorePlain_10i(ourCarriage, pos, (*ppFlashlight), alpha, beta, depth - reduction, false);
				(*ppFlashlight)->m_skipNullMove = false;

				if (beta <= s) {
					isReturnWithSweetness = true;
					returnSweetness = nullSweetness;
					return;
					//return nullSweetness;
				}
			}
			else {
				// fail low
				threatMove = ((*ppFlashlight) + 1)->m_currentMove;
				if (depth < 5 * OnePly
					&& ((*ppFlashlight) - 1)->m_reduction != Depth0
					&& !threatMove.IsNone()
					&& ourCarriage.allows(pos, ((*ppFlashlight) - 1)->m_currentMove, threatMove))
				{
					isReturnWithSweetness = true;
					returnSweetness = beta - 1;
					return;
					//return beta - 1;
				}
			}
		}
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
	virtual inline void explorePlain_10i1290j_nonPV(
		bool& isReturnWithSweetness,
		OurCarriage& ourCarriage,
		const Depth& depth,
		Flashlight** ppFlashlight,
		Sweetness& beta,
		Move& move,
		Position& pos,
		Move& ttMove,
		StateInfo& st,
		Sweetness& sweetness,
		const bool cutNode
		)const {

		// probcut

		// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
		if (5 * OnePly <= depth
			&& !(*ppFlashlight)->m_skipNullMove
			// 確実にバグらせないようにする。
			&& abs(beta) < SweetnessInfinite - 200)
		{
			const Sweetness rbeta = beta + 200;
			const Depth rdepth = depth - OnePly - 3 * OnePly;

			assert(OnePly <= rdepth);
			assert(!((*ppFlashlight) - 1)->m_currentMove.IsNone());
			assert(((*ppFlashlight) - 1)->m_currentMove != g_MOVE_NULL);

			assert(move == (*((ppFlashlight) - 1))->m_currentMove);
			// move.cap() は前回(一手前)の指し手で取った駒の種類
			NextmoveEvent mp(pos, ttMove, ourCarriage.m_history, move.GetCap());
			const CheckInfo ci(pos);
			while (!(move = mp.GetNextMove_NonSplitedNode()).IsNone()) {
				if (
					pos.GetTurn()==Color::Black
					?
					pos.IsPseudoLegalMoveIsLegal<false, false, Color::Black, Color::White>(move, ci.m_pinned)
					:
					pos.IsPseudoLegalMoveIsLegal<false, false, Color::White, Color::Black>(move, ci.m_pinned)
					) {
					(*ppFlashlight)->m_currentMove = move;

					pos.GetTurn()==Color::Black
						?
						pos.DoMove<Color::Black,Color::White>(move, st, ci, pos.IsMoveGivesCheck(move, ci))
						:
						pos.DoMove<Color::White,Color::Black>(move, st, ci, pos.IsMoveGivesCheck(move, ci))
						;

					((*ppFlashlight) + 1)->m_staticEvalRaw.m_p[0][0] = SweetnessNotEvaluated;

					//────────────────────────────────────────────────────────────────────────────────
					// 探索☆？（＾ｑ＾）
					//────────────────────────────────────────────────────────────────────────────────
					sweetness =	-g_NODEKIND_PROGRAMS[NodeKind::No2_NonPV]->explorePlain_10i(ourCarriage, pos, (*ppFlashlight) + 1, -rbeta, -rbeta + 1, rdepth, !cutNode);
					pos.UndoMove(move);
					if (rbeta <= sweetness) {
						isReturnWithSweetness = true;
						return;
						//return sweetness;
					}
				}
			}
		}
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
		OurCarriage& ourCarriage,
		Position& pos,
		Sweetness& alpha,
		const TTEntry** ppTtEntry,//セットされるぜ☆
		Key& posKey
		)const = 0;


	/// <summary>
	/// これはベータ値☆ PVノードか、そうでないかで値が変わるぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="beta"></param>
	/// <returns></returns>
	virtual inline Sweetness getBeta_10i1310j(
		Sweetness beta
		) const = 0;


	/// <summary>
	/// ルートノードか、そうでないかで分かれるぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="depth"></param>
	/// <param name="sweetness"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="singularExtensionNode"></param>
	/// <param name="excludedMove"></param>
	/// <param name="pTtEntry"></param>
	virtual inline void explorePlain_10i1320j_beforeLoopSplitPointStart(
		Move& ttMove,
		const Depth depth,
		Sweetness& sweetness,
		Sweetness& bestSweetness,
		bool& singularExtensionNode,
		Move& excludedMove,
		const TTEntry* pTtEntry) const = 0;


	/// <summary>
	/// これはムーブ☆
	/// </summary>
	/// <param name="mp"></param>
	/// <returns></returns>
	virtual inline Move getNextMove_10i2010j(
		NextmoveEvent& mp
		) const = 0;


	/// <summary>
	/// スプリット・ポイントかどうかで変わる手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="ci"></param>
	/// <param name="moveCount"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void explorePlain_10i2020j_resetSweetness(
		bool& isContinue,
		Position& pos,
		Move& move,
		const CheckInfo& ci,
		int& moveCount,
		SplitedNode** ppSplitedNode
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="move"></param>
	virtual inline void explorePlain_10i2030j_isRootMoveEnd(
		bool& isContinue,
		const OurCarriage& ourCarriage,
		const Move& move
		)const {
		// ルートノードにのみある手続きだぜ☆！（＾ｑ＾）
		if (std::find(
				ourCarriage.m_rootMoves.begin() + ourCarriage.m_pvIdx,
				ourCarriage.m_rootMoves.end(),
				move) == ourCarriage.m_rootMoves.end())
		{
			isContinue = true;
			return;
		}
	}


	/// <summary>
	/// ルートノードだけ実行する手続きだぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="moveCount"></param>
	virtual inline void explorerPlain_10i2040j_displayInfo(
		OurCarriage& ourCarriage,
		int& moveCount) const
	{
		ourCarriage.m_signals.m_firstRootMove = (moveCount == 1);
#if 0
		if (GetThisThread == ourCarriage.m_ownerHerosPub.GetFirstCaptain() && 3000 < ourCarriage.m_stopwatch.GetElapsed()) {
			SYNCCOUT << "info depth " << GetDepth / OnePly
				<< " currmove " << GetMove.ToUSI()
				<< " currmovenumber " << ourCarriage.m_moveCount + ourCarriage.m_pvIdx << SYNCENDL;
		}
#endif
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="extension"></param>
	/// <param name="captureOrPawnPromotion"></param>
	/// <param name="move"></param>
	/// <param name="givesCheck"></param>
	/// <param name="ci"></param>
	/// <param name="pos"></param>
	/// <param name="dangerous"></param>
	virtual inline void explorePlain_10i2050j_resetState(
		Depth& extension,
		bool& captureOrPawnPromotion,
		Move& move,
		bool& givesCheck,
		const CheckInfo& ci,
		Position& pos,
		bool& dangerous) const
	{
		extension = Depth0;
		captureOrPawnPromotion = move.IsCaptureOrPawnPromotion();
		givesCheck = pos.IsMoveGivesCheck(move, ci);
		dangerous = givesCheck; // todo: not implement
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="givesCheck"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="extension"></param>
	/// <param name="singularExtensionNode"></param>
	/// <param name="ttMove"></param>
	/// <param name="ttSweetness"></param>
	/// <param name="ci"></param>
	/// <param name="depth"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="sweetness"></param>
	/// <param name="cutNode"></param>
	/// <param name="beta"></param>
	/// <param name="newDepth"></param>
	virtual inline void explorerPlain_10i2060j_recursiveSearchA(
		OurCarriage& ourCarriage,
		bool& givesCheck,
		Position& pos,
		Move& move,
		Depth& extension,
		bool& singularExtensionNode,
		Move& ttMove,
		Sweetness& ttSweetness,
		const CheckInfo& ci,
		const Depth depth,
		Flashlight** ppFlashlight,
		Sweetness& sweetness,
		const bool cutNode,
		Sweetness& beta,
		Depth& newDepth) const
	{
		if (givesCheck && Sweetness::SweetnessZero <= pos.GetSeeSign(move))
		{
			extension = Depth::OnePly;
		}

		// singuler extension
		if (singularExtensionNode
			&& extension == Depth0
			&& move == ttMove
			&&
			(
				pos.GetTurn() == Color::Black
					?
					pos.IsPseudoLegalMoveIsLegal<false, false, Color::Black, Color::White>(move, ci.m_pinned)
					:
					pos.IsPseudoLegalMoveIsLegal<false, false, Color::White, Color::Black>(move, ci.m_pinned)
			)
			&& abs(ttSweetness) < PieceSweetness::m_sweetnessKnownWin)
		{
			assert(ttSweetness != SweetnessNone);

			const Sweetness rBeta = ttSweetness - static_cast<Sweetness>(depth);
			(*ppFlashlight)->m_excludedMove = move;
			(*ppFlashlight)->m_skipNullMove = true;
			//────────────────────────────────────────────────────────────────────────────────
			// 探索☆？（＾ｑ＾）
			//────────────────────────────────────────────────────────────────────────────────
			sweetness =	g_NODEKIND_PROGRAMS[No2_NonPV]->explorePlain_10i(ourCarriage, pos, (*ppFlashlight), rBeta - 1, rBeta, depth / 2, cutNode);
			(*ppFlashlight)->m_skipNullMove = false;
			(*ppFlashlight)->m_excludedMove = g_MOVE_NONE;

			if (sweetness < rBeta) {
				//extension = OnePly;
				extension = (beta <= rBeta ? OnePly + OnePly / 2 : OnePly);
			}
		}

		newDepth = depth - OnePly + extension;
	}


	/// <summary>
	///		<pre>
	/// 無駄枝狩り☆（＾▽＾）
	/// 非PVノードだけ実行するぜ☆！（＾ｑ＾）
	///		</pre>
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
	/// <param name="ppSplitedNode"></param>
	/// <param name="newDepth"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="beta"></param>
	virtual inline void explorePlain_10i2070j_futilityPruning(
		bool& isContinue,
		OurCarriage& ourCarriage,
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
		SplitedNode** ppSplitedNode,
		Depth& newDepth,
		Flashlight** ppFlashlight,
		Sweetness& beta) const
	{
		// futility pruning
		if (!captureOrPawnPromotion
			&& !inCheck
			&& !dangerous
			//&& move != ttMove // 次の行がtrueならこれもtrueなので条件から省く。
			&& Sweetness::SweetnessMatedInMaxPly < bestSweetness)
		{
			assert(move != ttMove);
			// move count based pruning
			if (depth < 16 * OnePly
				&& g_futilityMoveCounts.m_futilityMoveCounts[depth] <= moveCount
				&& (
					threatMove.IsNone()
					||
					!
					(
						pos.GetTurn()==Color::Black
						?
						ourCarriage.refutes<Color::Black,Color::White>(pos, move, threatMove)
						:
						ourCarriage.refutes<Color::White,Color::Black>(pos, move, threatMove)
					)
					)
			){
				this->lock_10i400j170k300L(ppSplitedNode);
				isContinue = true;
				return;
			}

			// sweetness based pruning
			const Depth predictedDepth = this->getPredictedDepth_10i400j170k100L( newDepth, depth, moveCount);
			// gain を 2倍にする。
			const Sweetness futilitySweetness = (*ppFlashlight)->m_staticEval + g_futilityMargins.GetFutilityMargin(predictedDepth, moveCount)
				+ 2 * ourCarriage.m_gains.GetValue(move.IsDrop(), ConvPiece::FROM_COLOR_AND_PIECE_TYPE10(pos.GetTurn(), move.GetPieceTypeFromOrDropped()), move.To());

			if (futilitySweetness < beta) {
				bestSweetness = std::max(bestSweetness, futilitySweetness);
				this->lockAndUpdateBestSweetness_10i400j170k200L(
					ppSplitedNode,
					bestSweetness
					);
				isContinue = true;
				return;
			}

			if (predictedDepth < 4 * OnePly
				&& pos.GetSeeSign(move) < SweetnessZero)
			{
				this->lock_10i400j170k300L(ppSplitedNode);
				isContinue = true;
				return;
			}
		}
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
		) const = 0;


	/// <summary>
	/// スプリット・ポイントでだけ実行☆（＾ｑ＾）！
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestSweetness"></param>
	virtual inline void lockAndUpdateBestSweetness_10i400j170k200L(
		SplitedNode** ppSplitedNode,
		Sweetness& bestSweetness
	) const {

		(*ppSplitedNode)->m_mutex.lock();
		if ((*ppSplitedNode)->m_bestSweetness < bestSweetness) {
			(*ppSplitedNode)->m_bestSweetness = bestSweetness;
		}
	}


	/// <summary>
	/// スプリット・ポイントでだけ実行☆（＾ｑ＾）！
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	virtual inline void lock_10i400j170k300L(
		SplitedNode** ppSplitedNode
		) const
	{
		(*ppSplitedNode)->m_mutex.lock();
	}


	/// <summary>
	/// ルートノード、スプリットポイントはしない手続きだぜ☆！（＾ｑ＾）
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
		int& moveCount) const
	{
		// RootNode, SPNode はすでに合法手であることを確認済み。
		if (!
			(
				pos.GetTurn()==Color::Black
				?
					pos.IsPseudoLegalMoveIsLegal<false, false,Color::Black,Color::White>(move, ci.m_pinned)
				:
					pos.IsPseudoLegalMoveIsLegal<false, false,Color::White,Color::Black>(move, ci.m_pinned)
			)
		) {
			--moveCount;
			isContinue = true;
			return;
		}
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
	/// <param name="ppSplitedNode"></param>
	/// <param name="newDepth"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="beta"></param>
	/// <param name="ci"></param>
	/// <param name="isPVMoveRef"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="movesSearched"></param>
	virtual inline void explorePlain_10i2090j_updateCurrentMove(
		bool& isContinue,
		OurCarriage& ourCarriage,
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
		SplitedNode** ppSplitedNode,
		Depth& newDepth,
		Flashlight** ppFlashlight,
		Sweetness& beta,
		const CheckInfo& ci,
		bool& isPVMoveRef,
		int& playedMoveCount,
		Move movesSearched[64]
		) const = 0;


	/// <summary>
	/// 非スプリットポイントでだけ実行するぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="captureOrPawnPromotion"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="movesSearched"></param>
	/// <param name="move"></param>
	virtual inline void explorerPlain_10i2100j_updateMoveSearched(
		bool& captureOrPawnPromotion,
		int& playedMoveCount,
		Move movesSearched[64],
		Move& move) const
	{
		if (!captureOrPawnPromotion && playedMoveCount < 64) {
			movesSearched[playedMoveCount++] = move;
		}
	}


	/// <summary>
	/// 一手指す（＾～＾）
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="st"></param>
	/// <param name="ci"></param>
	/// <param name="givesCheck"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorePlain_10i2110j_doMove(
		Position& pos,
		Move& move,
		StateInfo& st,
		const CheckInfo& ci,
		bool& givesCheck,
		Flashlight** ppFlashlight
		) const
	{
		pos.GetTurn()==Color::Black
			?
				pos.DoMove<Color::Black,Color::White>(move, st, ci, givesCheck)
			:
				pos.DoMove<Color::White,Color::Black>(move, st, ci, givesCheck)
			;

		((*ppFlashlight) + 1)->m_staticEvalRaw.m_p[0][0] = Sweetness::SweetnessNotEvaluated;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="depth"></param>
	/// <param name="isPVMove"></param>
	/// <param name="captureOrPawnPromotion"></param>
	/// <param name="move"></param>
	/// <param name="ttMove"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="moveCount"></param>
	/// <param name="cutNode"></param>
	/// <param name="newDepth"></param>
	/// <param name="alpha"></param>
	/// <param name="ppSplitedNode"></param>
	/// <param name="sweetness"></param>
	/// <param name="pos"></param>
	/// <param name="doFullDepthSearch"></param>
	virtual inline void explorePlain_10i2999j_recursiveSearch(
		OurCarriage& ourCarriage,
		const Depth depth,
		bool& isPVMove,
		bool& captureOrPawnPromotion,
		Move& move,
		Move& ttMove,
		Flashlight** ppFlashlight,
		int& moveCount,
		const bool cutNode,
		Depth& newDepth,
		Sweetness& alpha,
		SplitedNode** ppSplitedNode,
		Sweetness& sweetness,
		Position& pos,
		bool& doFullDepthSearch
		) const
	{
		// LMR
		if (3 * OnePly <= depth
			&& !isPVMove
			&& !captureOrPawnPromotion
			&& move != ttMove
			&& (*ppFlashlight)->m_killers[0] != move
			&& (*ppFlashlight)->m_killers[1] != move)
		{
			this->setReduction_10i500j500k100L(
				ppFlashlight,
				depth,
				moveCount,
				cutNode);
			const Depth d = std::max(newDepth - (*ppFlashlight)->m_reduction, Depth::OnePly);

			// スプリットポイントではアルファを更新☆
			this->updateAlpha_10i500j500k200L(
				alpha,
				ppSplitedNode);

			//────────────────────────────────────────────────────────────────────────────────
			// 探索☆？（＾ｑ＾）
			//────────────────────────────────────────────────────────────────────────────────
			// PVS
			sweetness = -g_NODEKIND_PROGRAMS[No2_NonPV]->explorePlain_10i(ourCarriage, pos, (*ppFlashlight) + 1, -(alpha + 1), -alpha, d, true);

			doFullDepthSearch = (alpha < sweetness && (*ppFlashlight)->m_reduction != Depth0);
			(*ppFlashlight)->m_reduction = Depth0;
		}
		else {
			doFullDepthSearch = !isPVMove;
		}
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
		) const = 0;


	/// <summary>
	/// スプリットノードだけが実行するぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void updateAlpha_10i500j500k200L(
		Sweetness& alpha,
		SplitedNode** ppSplitedNode
		) const {

		alpha = (*ppSplitedNode)->m_alpha;
	}


	/// <summary>
	/// スプリットノードだけが実行するぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="doFullDepthSearch"></param>
	/// <param name="alpha"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void explorePlain_10i3010j_updateAlpha(
		bool& doFullDepthSearch,
		Sweetness& alpha,
		SplitedNode** ppSplitedNode) const
	{
		// full depth search
		// PVS
		if (doFullDepthSearch) {
			alpha = (*ppSplitedNode)->m_alpha;
		}
	}


	/// <summary>
	/// （＾ｑ＾）N02_NonPV扱いで実行するみたいなんだがなんだこれだぜ☆
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="doFullDepthSearch"></param>
	/// <param name="sweetness"></param>
	/// <param name="newDepth"></param>
	/// <param name="givesCheck"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="alpha"></param>
	/// <param name="cutNode"></param>
	virtual inline void explorePlain_10i3020j_getSweetnessNonPV(
		OurCarriage& ourCarriage,
		bool& doFullDepthSearch,
		Sweetness& sweetness,
		Depth& newDepth,
		bool& givesCheck,
		Position& pos,
		Flashlight** ppFlashlight,
		Sweetness& alpha,
		const bool cutNode) const
	{
		// full depth search
		// PVS
		if (doFullDepthSearch) {
			sweetness = (newDepth < OnePly ?
				(givesCheck ? -AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No2_NonPV]->ExploreAsQsearch(ourCarriage, true, pos, (*ppFlashlight) + 1, -(alpha + 1), -alpha, Depth0)
					: -AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No2_NonPV]->ExploreAsQsearch(ourCarriage, false, pos, (*ppFlashlight) + 1, -(alpha + 1), -alpha, Depth0))
				//────────────────────────────────────────────────────────────────────────────────
				// 探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				: -g_NODEKIND_PROGRAMS[No2_NonPV]->explorePlain_10i(ourCarriage, pos, (*ppFlashlight) + 1, -(alpha + 1), -alpha, newDepth, !cutNode));
		}
	}


	/// <summary>
	///		<pre>
	/// PVノードだけが実行するぜ☆！（＾ｑ＾）
	/// N01_PV扱いで実行するみたいだが……☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="isPVMove"></param>
	/// <param name="alpha"></param>
	/// <param name="sweetness"></param>
	/// <param name="beta"></param>
	/// <param name="newDepth"></param>
	/// <param name="givesCheck"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorerPlain_10i3030j_getSweetness(
		OurCarriage& ourCarriage,
		bool& isPVMove,
		Sweetness& alpha,
		Sweetness& sweetness,
		Sweetness& beta,
		Depth& newDepth,
		bool& givesCheck,
		Position& pos,
		Flashlight** ppFlashlight) const
	{
		// 通常の探索
		if (
			isPVMove ||
			(alpha < sweetness && this->isBetaLarge_10i600j140k100L(sweetness,beta))
		) {
			sweetness = (newDepth < OnePly ?
				(givesCheck ? -AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No1_PV]->ExploreAsQsearch(ourCarriage, true, pos, (*ppFlashlight) + 1, -beta, -alpha, Depth0)
					: -AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No1_PV]->ExploreAsQsearch(ourCarriage, false, pos, (*ppFlashlight) + 1, -beta, -alpha, Depth0))
				//────────────────────────────────────────────────────────────────────────────────
				// 探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				: -g_NODEKIND_PROGRAMS[No1_PV]->explorePlain_10i(ourCarriage, pos, (*ppFlashlight) + 1, -beta, -alpha, newDepth, false));
		}
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
		) const = 0;
		

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	virtual inline void explorerPlain_10i3040j_undoMove(
		Position& pos,
		Move& move
		) const
	{
		pos.UndoMove(move);
	}


	/// <summary>
	/// スプリット・ポイントだけが実行するぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="alpha"></param>
	virtual inline void explorePlain_10i3050j_getAlpha(
		SplitedNode** ppSplitedNode,
		Sweetness& bestSweetness,
		Sweetness& alpha
		) const
	{
		(*ppSplitedNode)->m_mutex.lock();
		bestSweetness = (*ppSplitedNode)->m_bestSweetness;
		alpha = (*ppSplitedNode)->m_alpha;
	}


	/// <summary>
	/// ルートノードだけが実行するぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="move"></param>
	/// <param name="isPVMove">本筋の指し手かどうかかなあ（＾～＾）？</param>
	/// <param name="alpha"></param>
	/// <param name="sweetness"></param>
	/// <param name="pos"></param>
	virtual inline void explorerPlain_10i3060j_bestMovePlyChanges(
		OurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		Sweetness& alpha,
		Sweetness& sweetness,
		Position& pos
		) const
	{
		// ルート・ムーブのリストから、１つ選んでる（＾～＾）？
		RootMove& rm = *std::find(ourCarriage.m_rootMoves.begin(), ourCarriage.m_rootMoves.end(), move);

		if (isPVMove || alpha < sweetness) {
			// PV move or new best move
			rm.m_sweetness_ = sweetness;
#if defined BISHOP_IN_DANGER
			if ((bishopInDangerFlag == BlackBishopInDangerIn28 && GetMove.ToCSA() == "0082KA")
				|| (bishopInDangerFlag == WhiteBishopInDangerIn28 && GetMove.ToCSA() == "0028KA")
				|| (bishopInDangerFlag == BlackBishopInDangerIn78 && GetMove.ToCSA() == "0032KA")
				|| (bishopInDangerFlag == WhiteBishopInDangerIn78 && GetMove.ToCSA() == "0078KA"))
			{
				rm.m_sweetness_ -= m_engineOptions["Danger_Demerit_Score"];
			}
#endif
			rm.ExtractPvFromTT(pos);

			if (!isPVMove) {	// 本筋じゃないとき（＾～＾）
				ourCarriage.IncreaseBestMovePlyChanges();
			}
		}
		else {
			rm.m_sweetness_ = -SweetnessInfinite;
		}
	}


	/// <summary>
	/// スプリット・ポイントかどうかで分かれるぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isBreak"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="move"></param>
	/// <param name="isPVMove"></param>
	/// <param name="alpha"></param>
	/// <param name="sweetness"></param>
	/// <param name="pos"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestMove"></param>
	/// <param name="beta"></param>
	virtual inline void explorePlain_10i3070j_getBestUpdateAlpha(
		bool& isBreak,
		OurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		Sweetness& alpha,
		Sweetness& sweetness,
		Position& pos,
		Sweetness& bestSweetness,
		SplitedNode** ppSplitedNode,
		Move& bestMove,
		Sweetness& beta) const = 0;


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
	virtual inline void explorePlain_10i3080j_forkNewMonkey(
		bool& isBreak,
		OurCarriage& ourCarriage,
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
		const bool cutNode) const = 0;


	/// <summary>
	/// スプリット・ポイントは　ステップ２０を実行する前に終了するぜ☆（＾ｑ＾）
	/// </summary>
	/// <returns></returns>
	virtual inline bool isReturnBeforeLastProcess_10i4010j() const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="moveCount"></param>
	/// <param name="excludedMove"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
	virtual inline void explorePlain_10i4020j_backwardProcess(
		int& moveCount,
		Move& excludedMove,
		OurCarriage& ourCarriage,
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
		Move movesSearched[64]) const
	{
		if (moveCount == 0) {
			bestSweetness = !excludedMove.IsNone() ? alpha : UtilSweetness::MatedIn((*ppFlashlight)->m_ply);
			return;
		}

		if (bestSweetness == -SweetnessInfinite) {
			assert(playedMoveCount == 0);
			bestSweetness = alpha;
		}

		if (beta <= bestSweetness) {
			// failed high
			ourCarriage.m_tt.Store(posKey, ourCarriage.ConvertSweetnessToTT(bestSweetness, (*ppFlashlight)->m_ply), BoundLower, depth,
				bestMove, (*ppFlashlight)->m_staticEval);

			if (!bestMove.IsCaptureOrPawnPromotion() && !inCheck) {
				if (bestMove != (*ppFlashlight)->m_killers[0]) {
					(*ppFlashlight)->m_killers[1] = (*ppFlashlight)->m_killers[0];
					(*ppFlashlight)->m_killers[0] = bestMove;
				}

				const Sweetness bonus = static_cast<Sweetness>(depth * depth);
				const Piece pc1 = ConvPiece::FROM_COLOR_AND_PIECE_TYPE10(pos.GetTurn(), bestMove.GetPieceTypeFromOrDropped());
				ourCarriage.m_history.Update(bestMove.IsDrop(), pc1, bestMove.To(), bonus);

				for (int i = 0; i < playedMoveCount - 1; ++i) {
					const Move m = movesSearched[i];
					const Piece pc2 = ConvPiece::FROM_COLOR_AND_PIECE_TYPE10(pos.GetTurn(), m.GetPieceTypeFromOrDropped());
					ourCarriage.m_history.Update(m.IsDrop(), pc2, m.To(), -bonus);
				}
			}
		}
		else {
			// failed low or PV search
			ourCarriage.m_tt.Store(
				posKey,
				ourCarriage.ConvertSweetnessToTT(bestSweetness, (*ppFlashlight)->m_ply),
				this->getBound_10i800j200k600L(!bestMove.IsNone()),
				depth,
				bestMove,
				(*ppFlashlight)->m_staticEval
			);
		}

		assert(-Sweetness::SweetnessInfinite < bestSweetness && bestSweetness < Sweetness::SweetnessInfinite);
	}


	/// <summary>
	/// スタティック・メソッドは継承できないので、スタティックにはしないぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="bestMoveExists"></param>
	/// <returns></returns>
	virtual inline Bound getBound_10i800j200k600L(bool bestMoveExists) const = 0;
};
