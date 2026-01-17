#pragma once
#include <utility>  // std::pair用
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
///		<pre>
///	大冒険する平野だぜ（＾▽＾）！
/// 
///		- サブクラスが６つあるぜ（＾～＾）
///		</pre>
/// </summary>
class AdventureNodekindAbstract {


public:


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// 平野へ大冒険に出るぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
		const bool cutNode) const = 0;


	/// <summary>
	/// 非PVノードはassertをするぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void AssertBeforeStep1(
		ScoreIndex alpha,
		ScoreIndex beta
		) const {
		// 非PVノードのみ実行☆！（＾ｑ＾）
		assert(alpha == beta - 1);
	}


	/// <summary>
	///		<pre>
	/// ノード初期化
	/// 
	///		- スプリット・ポイントのみ実行☆（＾ｑ＾）
	///		</pre>
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
		ScoreIndex& ttScore) const
	{
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


	/// <summary>
	/// 指し手をクリアーする（＾～＾）？
	/// </summary>
	/// <param name="bestScore"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="threatMove"></param>
	/// <param name="bestMove"></param>
	virtual inline void explorePlain_n80_setMoveNone(
		ScoreIndex& bestScore,
		Flashlight** ppFlashlight,
		Move& threatMove,
		Move& bestMove) const
	{
		bestScore = -ScoreInfinite;
		(*ppFlashlight)->m_currentMove = threatMove = bestMove = ((*ppFlashlight) + 1)->m_excludedMove = g_MOVE_NONE;
		(*ppFlashlight)->m_ply = ((*ppFlashlight) - 1)->m_ply + 1;
		((*ppFlashlight) + 1)->m_skipNullMove = false;
		((*ppFlashlight) + 1)->m_reduction = Depth0;
		((*ppFlashlight) + 2)->m_killers[0] = ((*ppFlashlight) + 2)->m_killers[1] = g_MOVE_NONE;
	}


	/// <summary>
	/// ［本筋ノードでの最大手数］という情報を更新（＾～＾）
	/// </summary>
	/// <param name="ppThisThread"></param>
	/// <param name="pFlashlight"></param>
	virtual inline void explorePlain_n90_updateMaxPly(
		Monkey** ppThisThread,
		const Flashlight* pFlashlight) const
	{
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
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
	/// <param name="pos"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="ppFlashlight"></param>
	virtual inline std::pair<bool, ScoreIndex> ExplorerPlainStep2_IsStopByRepetetion(
		Position& pos,
		OurCarriage& ourCarriage,
		Flashlight** ppFlashlight) const
	{
		// stop と最大探索深さのチェック
		return g_repetitionTypes.m_ARRAY[pos.IsRepetition(16)]->IsStop(
			&ourCarriage,
			(*ppFlashlight));
	}


	/// <summary>
	/// ルートノード以外が実行するぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void ExplorerPlainStep3(
		bool& isReturnWithScore,
		ScoreIndex& returnScore,
		Flashlight** ppFlashlight,
		ScoreIndex& alpha,
		ScoreIndex& beta) const
	{
		// ルート以外のみで行われる手続きだぜ☆（＾ｑ＾）！
		alpha = std::max(UtilScore::MatedIn((*ppFlashlight)->m_ply), alpha);
		beta = std::min(UtilScore::MateIn((*ppFlashlight)->m_ply + 1), beta);
		if (beta <= alpha) {
			isReturnWithScore = true;
			returnScore = alpha;
			return;
			//return alpha;
		}
	}


	/// <summary>
	/// トランスポジション・テーブルのスコアを取得した（＾～＾）？
	/// </summary>
	/// <param name="excludedMove"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="posKey"></param>
	/// <param name="pos"></param>
	/// <param name="ppTtEntry"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="ttScore"></param>
	virtual inline void explorePlain_n100_getTtScore(
		Move& excludedMove,
		Flashlight** ppFlashlight,
		Key& posKey,
		Position& pos,
		const TTEntry** ppTtEntry,//セットされるぜ☆（＾ｑ＾）
		OurCarriage& ourCarriage,
		ScoreIndex& ttScore) const
	{
		// trans position table lookup
		excludedMove = (*ppFlashlight)->m_excludedMove;

		// 局面ハッシュ（＾～＾）？
		posKey = (excludedMove.IsNone() ? pos.GetKey() : pos.GetExclusionKey());

		// トランスポジション・テーブルをなんか探した（＾～＾）？
		(*ppTtEntry) = ourCarriage.m_tt.Probe(posKey);

		// トランスポジション・テーブルのスコアを取得した（＾～＾）？
		ttScore = ((*ppTtEntry) != nullptr ? ourCarriage.ConvertScoreFromTT((*ppTtEntry)->GetScore(), (*ppFlashlight)->m_ply) : ScoreNone);
	}


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// ルートノードか、それ以外かで　値が分かれるぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ttMove"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pTtEntry"></param>
	/// <param name="pos"></param>
	virtual inline void explorePlain_n110_getTtMove(
		Move& ttMove,
		OurCarriage& ourCarriage,
		const TTEntry* pTtEntry,
		Position& pos) const = 0;


	/// <summary>
	/// PVノードか、非PVノードかで実行条件が変わるぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pTtEntry"></param>
	/// <param name="depth"></param>
	/// <param name="ttScore"></param>
	/// <param name="beta"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="ttMove"></param>
	virtual inline void ExplorerPlainStep4y(
		bool& isReturnWithScore,
		ScoreIndex& returnScore,
		OurCarriage& ourCarriage,
		const TTEntry* pTtEntry,
		const Depth depth,
		ScoreIndex& ttScore,
		ScoreIndex& beta,
		Flashlight** ppFlashlight,
		Move& ttMove) const
	{
		// ルートノード以外だけにある手続きだぜ☆（＾ｑ＾）
		if (pTtEntry != nullptr
			&& depth <= pTtEntry->GetDepth()
			&& ttScore != ScoreNone // アクセス競合が起きたときのみ、ここに引っかかる。
			&& this->GetConditionInStep4y(
				pTtEntry,
				beta,
				ttScore
				)
		){
			ourCarriage.m_tt.Refresh(pTtEntry);
			(*ppFlashlight)->m_currentMove = ttMove; // Move::moveNone() もありえる。

			if (beta <= ttScore
				&& !ttMove.IsNone()
				&& !ttMove.IsCaptureOrPawnPromotion()
				&& ttMove != (*ppFlashlight)->m_killers[0])
			{
				(*ppFlashlight)->m_killers[1] = (*ppFlashlight)->m_killers[0];
				(*ppFlashlight)->m_killers[0] = ttMove;
			}

			isReturnWithScore = true;
			returnScore = ttScore;
			return;
			//return ttScore;
		}
	}


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// PVノードか、非PVノードかで実行条件が変わるぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="pTtEntry"></param>
	/// <param name="beta"></param>
	/// <param name="ttScore"></param>
	/// <returns></returns>
	virtual inline bool GetConditionInStep4y(
		const TTEntry* pTtEntry,
		ScoreIndex& beta,
		ScoreIndex& ttScore) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="inCheck"></param>
	/// <param name="move"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="bestScore"></param>
	/// <param name="posKey"></param>
	/// <param name="depth"></param>
	/// <param name="bestMove"></param>
	virtual inline void ExplorerPlainStep4z(
		bool& isReturnWithScore,
		ScoreIndex& returnScore,
		OurCarriage& ourCarriage,
		bool& inCheck,
		Move& move,
		Position& pos,
		Flashlight** ppFlashlight,
		ScoreIndex& bestScore,
		Key& posKey,
		const Depth depth,
		Move& bestMove) const
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
				(*ppFlashlight)->m_staticEval = bestScore = UtilScore::MateIn((*ppFlashlight)->m_ply);
				ourCarriage.m_tt.Store(posKey, ourCarriage.ConvertScoreToTT(bestScore, (*ppFlashlight)->m_ply), BoundExact, depth,
					move, (*ppFlashlight)->m_staticEval);
				bestMove = move;

				isReturnWithScore = true;
				returnScore = bestScore;
				return;
				//return bestScore;
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
	/// <param name="ttScore"></param>
	/// <param name="posKey"></param>
	/// <param name="move"></param>
	virtual inline void explorePlain_n120_eval(
		bool& isGotoIidStart,
		OurCarriage& ourCarriage,
		ScoreIndex& evalScore,
		Flashlight** ppFlashlight,
		Position& pos,
		bool& inCheck,
		const TTEntry* pTtEntry,
		ScoreIndex& ttScore,
		Key& posKey,
		Move& move) const
	{
		// evaluate the position statically
		Evaluation09 evaluation;

		evalScore = (*ppFlashlight)->m_staticEval = evaluation.evaluate(pos, (*ppFlashlight)); // Bonanza の差分評価の為、evaluate() を常に呼ぶ。
		if (inCheck) {
			evalScore = (*ppFlashlight)->m_staticEval = ScoreNone;
			isGotoIidStart = true;
			return;
			//goto iid_start;
		}

		else if (pTtEntry != nullptr) {
			if (
				ttScore != ScoreNone
				&&
				(
					pTtEntry->GetBoundKind()
					&
					((evalScore < ttScore) ? Bound::BoundLower : Bound::BoundUpper)
				)
			)
			{
				evalScore = ttScore;
			}
		}
		else {
			ourCarriage.m_tt.Store(posKey, ScoreNone, BoundNone, DepthNone,
				g_MOVE_NONE, (*ppFlashlight)->m_staticEval);
		}

		// 一手前の指し手について、history を更新する。
		// todo: ここの条件はもう少し考えた方が良い。
		if ((move = ((*ppFlashlight) - 1)->m_currentMove) != g_MOVE_NULL
			&& ((*ppFlashlight) - 1)->m_staticEval != ScoreNone
			&& (*ppFlashlight)->m_staticEval != ScoreNone
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
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="depth"></param>
	/// <param name="eval"></param>
	/// <param name="beta"></param>
	/// <param name="ttMove"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void ExplorerPlainStep6_NonPV(
		bool& isReturnWithScore,
		ScoreIndex& returnScore,
		OurCarriage& ourCarriage,
		const Depth depth,
		ScoreIndex& eval,
		ScoreIndex& beta,
		Move& ttMove,
		Position& pos,
		Flashlight** ppFlashlight) const
	{
		// razoring

		// 非PVノードだけが実行するぜ☆！（＾ｑ＾）
		if (depth < 4 * OnePly
			&& eval + ourCarriage.razorMargin(depth) < beta
			&& ttMove.IsNone()
			&& abs(beta) < ScoreMateInMaxPly)
		{
			const ScoreIndex rbeta = beta - ourCarriage.razorMargin(depth);
			const ScoreIndex s = AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No2_NonPV]->ExploreAsQsearch(
				ourCarriage, false, pos, (*ppFlashlight), rbeta - 1, rbeta, Depth0);
			if (s < rbeta) {
				isReturnWithScore = true;
				returnScore = s;
				return;
				//return s;
			}
		}
	}


	/// <summary>
	/// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="depth"></param>
	/// <param name="beta"></param>
	/// <param name="eval"></param>
	virtual inline void ExplorerPlainStep7(
		bool& isReturnWithScore,
		ScoreIndex& returnScore,
		Flashlight** ppFlashlight,
		const Depth depth,
		ScoreIndex& beta,
		ScoreIndex& eval) const
	{
		// static null move pruning

		// 非PVノードだけが実行するぜ☆！（＾ｑ＾）
		if (!(*ppFlashlight)->m_skipNullMove
			&& depth < 4 * OnePly
			&& beta <= eval - g_futilityMargins.m_FutilityMargins[depth][0]
			&& abs(beta) < ScoreMateInMaxPly)
		{
			bool isReturnWithScore = true;
			returnScore = eval - g_futilityMargins.m_FutilityMargins[depth][0];
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
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
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
	virtual inline void ExplorerPlainStep8_NonPV(
		bool& isReturnWithScore,
		ScoreIndex& returnScore,
		OurCarriage& ourCarriage,
		Flashlight** ppFlashlight,
		const Depth depth,
		ScoreIndex& beta,
		ScoreIndex& eval,
		Position& pos,
		StateInfo& st,
		ScoreIndex& alpha,
		const bool cutNode,
		Move& threatMove) const
	{
		// null move

		// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
		if (!(*ppFlashlight)->m_skipNullMove
			&& 2 * OnePly <= depth
			&& beta <= eval
			&& abs(beta) < ScoreMateInMaxPly)
		{
			(*ppFlashlight)->m_currentMove = g_MOVE_NULL;
			Depth reduction = static_cast<Depth>(3) * OnePly + depth / 4;

			if (beta < eval - PieceScore::m_pawn) {
				reduction += OnePly;
			}

			pos.DoNullMove(true, st);
			((*ppFlashlight) + 1)->m_staticEvalRaw = (*ppFlashlight)->m_staticEvalRaw; // 評価値の差分評価の為。
			((*ppFlashlight) + 1)->m_skipNullMove = true;

			ScoreIndex nullScore = (depth - reduction < OnePly ?
				//────────────────────────────────────────────────────────────────────────────────
				// 深さが２手（先後１組）以上なら　クイックな探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				-AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No2_NonPV]->ExploreAsQsearch(
					ourCarriage, false, pos, (*ppFlashlight) + 1, -beta, -alpha, Depth0)
				:
				//────────────────────────────────────────────────────────────────────────────────
				// 深さが２手（先後１組）未満なら　ふつーの探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				-g_NODEKIND_PROGRAMS[NodeKind::No2_NonPV]->explorePlain_n10(ourCarriage, pos, (*ppFlashlight) + 1, -beta, -alpha, depth - reduction, !cutNode)
			);

			((*ppFlashlight) + 1)->m_skipNullMove = false;
			pos.DoNullMove(false, st);

			if (beta <= nullScore) {
				if (ScoreMateInMaxPly <= nullScore) {
					nullScore = beta;
				}

				if (depth < 6 * OnePly) {
					isReturnWithScore = true;
					returnScore = nullScore;
					return;
					//return nullScore;
				}

				(*ppFlashlight)->m_skipNullMove = true;
				assert(Depth0 < depth - reduction);
				//────────────────────────────────────────────────────────────────────────────────
				// 探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				const ScoreIndex s = g_NODEKIND_PROGRAMS[NodeKind::No2_NonPV]->explorePlain_n10(ourCarriage, pos, (*ppFlashlight), alpha, beta, depth - reduction, false);
				(*ppFlashlight)->m_skipNullMove = false;

				if (beta <= s) {
					isReturnWithScore = true;
					returnScore = nullScore;
					return;
					//return nullScore;
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
					isReturnWithScore = true;
					returnScore = beta - 1;
					return;
					//return beta - 1;
				}
			}
		}
	}


	/// <summary>
	/// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isReturnWithScore"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="depth"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="beta"></param>
	/// <param name="move"></param>
	/// <param name="pos"></param>
	/// <param name="ttMove"></param>
	/// <param name="st"></param>
	/// <param name="score"></param>
	/// <param name="cutNode"></param>
	virtual inline void ExplorerPlainStep9(
		bool& isReturnWithScore,
		OurCarriage& ourCarriage,
		const Depth& depth,
		Flashlight** ppFlashlight,
		ScoreIndex& beta,
		Move& move,
		Position& pos,
		Move& ttMove,
		StateInfo& st,
		ScoreIndex& score,
		const bool cutNode) const
	{
		// probcut

		// 非PVノードだけが実行する手続きだぜ☆！（＾ｑ＾）
		if (5 * OnePly <= depth
			&& !(*ppFlashlight)->m_skipNullMove
			// 確実にバグらせないようにする。
			&& abs(beta) < ScoreInfinite - 200)
		{
			const ScoreIndex rbeta = beta + 200;
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

					((*ppFlashlight) + 1)->m_staticEvalRaw.m_p[0][0] = ScoreNotEvaluated;

					//────────────────────────────────────────────────────────────────────────────────
					// 探索☆？（＾ｑ＾）
					//────────────────────────────────────────────────────────────────────────────────
					score =	-g_NODEKIND_PROGRAMS[NodeKind::No2_NonPV]->explorePlain_n10(ourCarriage, pos, (*ppFlashlight) + 1, -rbeta, -rbeta + 1, rdepth, !cutNode);
					pos.UndoMove(move);
					if (rbeta <= score) {
						isReturnWithScore = true;
						return;
						//return score;
					}
				}
			}
		}
	}


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// PVノードか、そうでないかで手続きが変わるぜ☆！（＾ｑ＾）
	///		</pre>
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
		Key& posKey) const = 0;


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// これはベータ値☆ PVノードか、そうでないかで値が変わるぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="beta"></param>
	/// <returns></returns>
	virtual inline ScoreIndex getBeta_n140(
		ScoreIndex beta) const = 0;


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// これはムーブ☆
	///		</pre>
	/// </summary>
	/// <param name="mp"></param>
	/// <returns></returns>
	virtual inline Move getNextMove_n160(
		NextmoveEvent& mp) const = 0;


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// ルートノードか、そうでないかで分かれるぜ☆（＾ｑ＾）
	///		</pre>
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
		const TTEntry* pTtEntry) const = 0;


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// スプリット・ポイントかどうかで変わる手続きだぜ☆！（＾ｑ＾）
	///		</pre>
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
		SplitedNode** ppSplitedNode) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="move"></param>
	virtual inline void explorePlain_n200_loopHeader(
		bool& isContinue,
		const OurCarriage& ourCarriage,
		const Move& move) const
	{
		// ルートノードにのみある手続きだぜ☆！（＾ｑ＾）
		if (std::find(ourCarriage.m_rootMovesByID.begin() + ourCarriage.m_pvIdx,
				ourCarriage.m_rootMovesByID.end(),
				move) == ourCarriage.m_rootMovesByID.end())
		{
			isContinue = true;
			return;
		}
	}


	/// <summary>
	///		<pre>
	/// info 表示
	/// 
	///		- ルートノードだけ実行する手続きだぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="moveCount"></param>
	virtual inline void explorePlain_n220_displayInfo(
		OurCarriage& ourCarriage,
		int& moveCount) const
	{
		ourCarriage.m_signals.m_isFirstRootMove = (moveCount == 1);
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
	virtual inline void explorePlain_n240_loopHeader(
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
	/// なんか分からんが再帰探索（＾～＾）
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="givesCheck"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="extension"></param>
	/// <param name="singularExtensionNode"></param>
	/// <param name="ttMove"></param>
	/// <param name="ttScore"></param>
	/// <param name="ci"></param>
	/// <param name="depth"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="score"></param>
	/// <param name="cutNode"></param>
	/// <param name="beta"></param>
	/// <param name="newDepth"></param>
	virtual inline void explorePlain_n260_recursiveSearch(
		OurCarriage& ourCarriage,
		bool& givesCheck,
		Position& pos,
		Move& move,
		Depth& extension,
		bool& singularExtensionNode,
		Move& ttMove,
		ScoreIndex& ttScore,
		const CheckInfo& ci,
		const Depth depth,
		Flashlight** ppFlashlight,
		ScoreIndex& score,
		const bool cutNode,
		ScoreIndex& beta,
		Depth& newDepth) const
	{
		if (givesCheck && ScoreIndex::ScoreZero <= pos.GetSeeSign(move))
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
			&& abs(ttScore) < PieceScore::m_ScoreKnownWin)
		{
			assert(ttScore != ScoreNone);

			const ScoreIndex rBeta = ttScore - static_cast<ScoreIndex>(depth);
			(*ppFlashlight)->m_excludedMove = move;
			(*ppFlashlight)->m_skipNullMove = true;


			//────────────────────────────────────────────────────────────────────────────────
			// 探索☆？（＾ｑ＾）
			//────────────────────────────────────────────────────────────────────────────────
			score =	g_NODEKIND_PROGRAMS[No2_NonPV]->explorePlain_n10(ourCarriage, pos, (*ppFlashlight), rBeta - 1, rBeta, depth / 2, cutNode);


			(*ppFlashlight)->m_skipNullMove = false;
			(*ppFlashlight)->m_excludedMove = g_MOVE_NONE;

			if (score < rBeta) {
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
	/// <param name="bestScore"></param>
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
	virtual inline void ExplorerPlainStep13a_FutilityPruning(
		bool& isContinue,
		OurCarriage& ourCarriage,
		bool& captureOrPawnPromotion,
		bool& inCheck,
		bool& dangerous,
		ScoreIndex& bestScore,
		Move& move,
		Move& ttMove,
		const Depth depth,
		int& moveCount,
		Move& threatMove,
		Position& pos,
		SplitedNode** ppSplitedNode,
		Depth& newDepth,
		Flashlight** ppFlashlight,
		ScoreIndex& beta) const
	{
		// futility pruning
		if (!captureOrPawnPromotion
			&& !inCheck
			&& !dangerous
			//&& move != ttMove // 次の行がtrueならこれもtrueなので条件から省く。
			&& ScoreIndex::ScoreMatedInMaxPly < bestScore)
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
				this->LockInStep13a(ppSplitedNode);
				isContinue = true;
				return;
			}

			// score based pruning
			const Depth predictedDepth = this->GetPredictedDepthInStep13a( newDepth, depth, moveCount);
			// gain を 2倍にする。
			const ScoreIndex futilityScore = (*ppFlashlight)->m_staticEval + g_futilityMargins.GetFutilityMargin(predictedDepth, moveCount)
				+ 2 * ourCarriage.m_gains.GetValue(move.IsDrop(), PieceExtensions::FROM_COLOR_AND_PIECE_TYPE10(pos.GetTurn(), move.GetPieceTypeFromOrDropped()), move.To());

			if (futilityScore < beta) {
				bestScore = std::max(bestScore, futilityScore);
				this->LockAndUpdateBestScoreInStep13a(
					ppSplitedNode,
					bestScore
					);
				isContinue = true;
				return;
			}

			if (predictedDepth < 4 * OnePly
				&& pos.GetSeeSign(move) < ScoreZero)
			{
				this->LockInStep13a(ppSplitedNode);
				isContinue = true;
				return;
			}
		}
	}


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// PVノードか、そうでないかで変わるぜ☆！（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="newDepth"></param>
	/// <param name="depth"></param>
	/// <param name="moveCount"></param>
	/// <returns></returns>
	virtual inline const Depth GetPredictedDepthInStep13a(
		Depth& newDepth,
		const Depth depth,
		int& moveCount) const = 0;


	/// <summary>
	/// スプリット・ポイントでだけ実行☆（＾ｑ＾）！
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	virtual inline void LockInStep13a(
		SplitedNode** ppSplitedNode) const
	{
		(*ppSplitedNode)->m_mutex.lock();
	}


	/// <summary>
	/// スプリット・ポイントでだけ実行☆（＾ｑ＾）！
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestScore"></param>
	virtual inline void LockAndUpdateBestScoreInStep13a(
		SplitedNode** ppSplitedNode,
		ScoreIndex& bestScore) const
	{
		(*ppSplitedNode)->m_mutex.lock();
		if ((*ppSplitedNode)->m_bestScore < bestScore) {
			(*ppSplitedNode)->m_bestScore = bestScore;
		}
	}


	/// <summary>
	/// ルートノード、スプリットポイントはしない手続きだぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="ci"></param>
	/// <param name="moveCount"></param>
	virtual inline void ExplorerPlainStep13b(
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
	///		<pre>
	/// インターフェースのメソッド
	/// 本筋かどうか判定するぜ（＾～＾）
	///		</pre>
	/// </summary>
	/// <param name="moveCount"></param>
	virtual inline bool explorePlain_n280_isPvMove(
		int moveCount) const = 0;


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// スプリット・ポイントか、PVノードかで手続きが変わるぜ☆！（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="move"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorePlain_n300_setMove(
		Move move,
		Flashlight** ppFlashlight) const = 0;


	/// <summary>
	/// 非スプリットポイントでだけ実行するぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="captureOrPawnPromotion"></param>
	/// <param name="playedMoveCount"></param>
	/// <param name="movesSearched"></param>
	/// <param name="move"></param>
	virtual inline void explorePlain_n320_memoryVariationMove(
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
	/// １手指すぜ（＾～＾）
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	/// <param name="st"></param>
	/// <param name="ci"></param>
	/// <param name="givesCheck"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorerPlain_n340_doMove(
		Position& pos,
		Move& move,
		StateInfo& st,
		const CheckInfo& ci,
		bool& givesCheck,
		Flashlight** ppFlashlight) const
	{
		pos.GetTurn()==Color::Black
			?
			pos.DoMove<Color::Black,Color::White>(move, st, ci, givesCheck)
			:
			pos.DoMove<Color::White,Color::Black>(move, st, ci, givesCheck)
			;

		((*ppFlashlight) + 1)->m_staticEvalRaw.m_p[0][0] = ScoreIndex::ScoreNotEvaluated;
	}


	/// <summary>
	/// なんか分からんが再帰探索（＾～＾）
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
	/// <param name="score"></param>
	/// <param name="pos"></param>
	/// <param name="doFullDepthSearch"></param>
	virtual inline void explorePlain_n360_recursiveSearch(
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
		ScoreIndex& alpha,
		SplitedNode** ppSplitedNode,
		ScoreIndex& score,
		Position& pos,
		bool& doFullDepthSearch) const
	{
		// LMR
		if (3 * OnePly <= depth
			&& !isPVMove
			&& !captureOrPawnPromotion
			&& move != ttMove
			&& (*ppFlashlight)->m_killers[0] != move
			&& (*ppFlashlight)->m_killers[1] != move)
		{
			this->setReduction_n360(
				ppFlashlight,
				depth,
				moveCount,
				cutNode);
			const Depth d = std::max(newDepth - (*ppFlashlight)->m_reduction, Depth::OnePly);

			// スプリットポイントではアルファを更新☆
			this->updateAlpha_n360(
				alpha,
				ppSplitedNode);

			//────────────────────────────────────────────────────────────────────────────────
			// 探索☆？（＾ｑ＾）
			//────────────────────────────────────────────────────────────────────────────────
			// PVS
			score = -g_NODEKIND_PROGRAMS[No2_NonPV]->explorePlain_n10(ourCarriage, pos, (*ppFlashlight) + 1, -(alpha + 1), -alpha, d, true);

			doFullDepthSearch = (alpha < score && (*ppFlashlight)->m_reduction != Depth0);
			(*ppFlashlight)->m_reduction = Depth0;
		}
		else {
			doFullDepthSearch = !isPVMove;
		}
	}


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// Pvノードかどうかで手続きが変わるぜ☆！（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ppFlashlight"></param>
	/// <param name="depth"></param>
	/// <param name="moveCount"></param>
	/// <param name="cutNode"></param>
	virtual inline void setReduction_n360(
		Flashlight** ppFlashlight,
		const Depth depth,
		int& moveCount,
		const bool cutNode) const = 0;


	/// <summary>
	/// スプリットノードだけが実行するぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void updateAlpha_n360(
		ScoreIndex& alpha,
		SplitedNode** ppSplitedNode) const
	{
		alpha = (*ppSplitedNode)->m_alpha;
	}


	/// <summary>
	/// スプリットノードだけが実行するぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="doFullDepthSearch"></param>
	/// <param name="alpha"></param>
	/// <param name="ppSplitedNode"></param>
	virtual inline void ExplorerPlainStep16a(
		bool& doFullDepthSearch,
		ScoreIndex& alpha,
		SplitedNode** ppSplitedNode) const
	{
		// full depth search
		// PVS
		if (doFullDepthSearch) {
			alpha = (*ppSplitedNode)->m_alpha;
		}
	}


	/// <summary>
	/// （＾ｑ＾）N02_NonPV扱いで再帰するみたいなんだがなんだこれだぜ☆
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="doFullDepthSearch"></param>
	/// <param name="score"></param>
	/// <param name="newDepth"></param>
	/// <param name="givesCheck"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="alpha"></param>
	/// <param name="cutNode"></param>
	virtual inline void explorePlain_n380_nonPVRecursiveSearch(
		OurCarriage& ourCarriage,
		bool& doFullDepthSearch,
		ScoreIndex& score,
		Depth& newDepth,
		bool& givesCheck,
		Position& pos,
		Flashlight** ppFlashlight,
		ScoreIndex& alpha,
		const bool cutNode) const
	{
		// full depth search
		// PVS
		if (doFullDepthSearch) {
			score = (newDepth < OnePly ?
				(givesCheck ? -AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No2_NonPV]->ExploreAsQsearch(ourCarriage, true, pos, (*ppFlashlight) + 1, -(alpha + 1), -alpha, Depth0)
					: -AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No2_NonPV]->ExploreAsQsearch(ourCarriage, false, pos, (*ppFlashlight) + 1, -(alpha + 1), -alpha, Depth0))
				//────────────────────────────────────────────────────────────────────────────────
				// 探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				: -g_NODEKIND_PROGRAMS[No2_NonPV]->explorePlain_n10(ourCarriage, pos, (*ppFlashlight) + 1, -(alpha + 1), -alpha, newDepth, !cutNode));
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
	/// <param name="score"></param>
	/// <param name="beta"></param>
	/// <param name="newDepth"></param>
	/// <param name="givesCheck"></param>
	/// <param name="pos"></param>
	/// <param name="ppFlashlight"></param>
	virtual inline void explorePlain_n400_betaLargeRecursiveSearch(
		OurCarriage& ourCarriage,
		bool& isPVMove,
		ScoreIndex& alpha,
		ScoreIndex& score,
		ScoreIndex& beta,
		Depth& newDepth,
		bool& givesCheck,
		Position& pos,
		Flashlight** ppFlashlight) const
	{
		// 通常の探索
		if (
			isPVMove ||
			(alpha < score && this->IsBetaLargeAtStep16c(score,beta))
		) {
			score = (newDepth < OnePly ?
				(givesCheck ? -AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No1_PV]->ExploreAsQsearch(ourCarriage, true, pos, (*ppFlashlight) + 1, -beta, -alpha, Depth0)
					: -AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[No1_PV]->ExploreAsQsearch(ourCarriage, false, pos, (*ppFlashlight) + 1, -beta, -alpha, Depth0))
				//────────────────────────────────────────────────────────────────────────────────
				// 再帰的探索☆？（＾ｑ＾）
				//────────────────────────────────────────────────────────────────────────────────
				: -g_NODEKIND_PROGRAMS[No1_PV]->explorePlain_n10(ourCarriage, pos, (*ppFlashlight) + 1, -beta, -alpha, newDepth, false));
		}
	}


	/// <summary>
	/// インターフェースのメソッド
	/// </summary>
	/// <param name="score"></param>
	/// <param name="beta"></param>
	/// <returns></returns>
	virtual inline bool IsBetaLargeAtStep16c(
		ScoreIndex& score,
		ScoreIndex& beta) const = 0;
		

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="move"></param>
	virtual inline void explorePlain_n420_undoMove(
		Position& pos,
		Move& move) const
	{
		pos.UndoMove(move);
	}


	/// <summary>
	/// スプリット・ポイントだけが実行するぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestScore"></param>
	/// <param name="alpha"></param>
	virtual inline void ExplorerPlainStep18a(
		SplitedNode** ppSplitedNode,
		ScoreIndex& bestScore,
		ScoreIndex& alpha) const
	{
		(*ppSplitedNode)->m_mutex.lock();
		bestScore = (*ppSplitedNode)->m_bestScore;
		alpha = (*ppSplitedNode)->m_alpha;
	}


	/// <summary>
	/// ルートノードだけが実行するぜ☆！（＾ｑ＾）
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="move"></param>
	/// <param name="isPVMove">本筋の指し手かどうかかなあ（＾～＾）？</param>
	/// <param name="alpha"></param>
	/// <param name="score"></param>
	/// <param name="pos"></param>
	virtual inline void explorePlain_n440_findRootNode(
		OurCarriage& ourCarriage,
		Move& move,
		bool& isPVMove,
		ScoreIndex& alpha,
		ScoreIndex& score,
		Position& pos) const
	{
		// ルート・ムーブのリストから、１つ選んでる（＾～＾）？
		RootMove& rm = *std::find(ourCarriage.m_rootMovesByID.begin(), ourCarriage.m_rootMovesByID.end(), move);

		if (isPVMove || alpha < score) {
			// PV move or new best move
			rm.m_score_ = score;
#if defined BISHOP_IN_DANGER
			if ((bishopInDangerFlag == BlackBishopInDangerIn28 && GetMove.ToCSA() == "0082KA")
				|| (bishopInDangerFlag == WhiteBishopInDangerIn28 && GetMove.ToCSA() == "0028KA")
				|| (bishopInDangerFlag == BlackBishopInDangerIn78 && GetMove.ToCSA() == "0032KA")
				|| (bishopInDangerFlag == WhiteBishopInDangerIn78 && GetMove.ToCSA() == "0078KA"))
			{
				rm.m_score_ -= m_engineOptions["Danger_Demerit_Score"];
			}
#endif
			rm.ExtractPvFromTT(pos);

			if (!isPVMove) {	// 本筋じゃないとき（＾～＾）
				ourCarriage.IncreaseBestMovePlyChanges();
			}
		}
		else {
			rm.m_score_ = -ScoreInfinite;
		}
	}


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// スプリット・ポイントかどうかで分かれるぜ☆！（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="isBreak"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="move"></param>
	/// <param name="isPVMove"></param>
	/// <param name="alpha"></param>
	/// <param name="score"></param>
	/// <param name="pos"></param>
	/// <param name="bestScore"></param>
	/// <param name="ppSplitedNode"></param>
	/// <param name="bestMove"></param>
	/// <param name="beta"></param>
	virtual inline void explorePlain_n460_updateAlpha(
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
		ScoreIndex& beta) const = 0;


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// 非スプリットポイントでだけ実行するぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="isBreak"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
		const bool cutNode) const = 0;


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// スプリット・ポイントは　ステップ２０を実行する前に終了するぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <returns></returns>
	virtual inline bool getReturn_beforeN500() const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="moveCount"></param>
	/// <param name="excludedMove"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
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
	virtual inline void explorePlain_n500(
		int& moveCount,
		Move& excludedMove,
		OurCarriage& ourCarriage,
		ScoreIndex& alpha,
		Flashlight** ppFlashlight,//サーチスタック
		ScoreIndex& bestScore,
		int& playedMoveCount,
		ScoreIndex& beta,
		Key& posKey,
		const Depth depth,
		Move& bestMove,
		bool& inCheck,
		Position& pos,
		Move movesSearched[64]) const
	{
		if (moveCount == 0) {
			bestScore = !excludedMove.IsNone() ? alpha : UtilScore::MatedIn((*ppFlashlight)->m_ply);
			return;
		}

		if (bestScore == -ScoreInfinite) {
			assert(playedMoveCount == 0);
			bestScore = alpha;
		}

		if (beta <= bestScore) {
			// failed high
			ourCarriage.m_tt.Store(posKey, ourCarriage.ConvertScoreToTT(bestScore, (*ppFlashlight)->m_ply), BoundLower, depth,
				bestMove, (*ppFlashlight)->m_staticEval);

			if (!bestMove.IsCaptureOrPawnPromotion() && !inCheck) {
				if (bestMove != (*ppFlashlight)->m_killers[0]) {
					(*ppFlashlight)->m_killers[1] = (*ppFlashlight)->m_killers[0];
					(*ppFlashlight)->m_killers[0] = bestMove;
				}

				const ScoreIndex bonus = static_cast<ScoreIndex>(depth * depth);
				const Piece pc1 = PieceExtensions::FROM_COLOR_AND_PIECE_TYPE10(pos.GetTurn(), bestMove.GetPieceTypeFromOrDropped());
				ourCarriage.m_history.Update(bestMove.IsDrop(), pc1, bestMove.To(), bonus);

				for (int i = 0; i < playedMoveCount - 1; ++i) {
					const Move m = movesSearched[i];
					const Piece pc2 = PieceExtensions::FROM_COLOR_AND_PIECE_TYPE10(pos.GetTurn(), m.GetPieceTypeFromOrDropped());
					ourCarriage.m_history.Update(m.IsDrop(), pc2, m.To(), -bonus);
				}
			}
		}
		else {
			// failed low or PV search
			ourCarriage.m_tt.Store(
				posKey,
				ourCarriage.ConvertScoreToTT(bestScore, (*ppFlashlight)->m_ply),
				this->GetBoundAtStep20(!bestMove.IsNone()),
				depth,
				bestMove,
				(*ppFlashlight)->m_staticEval
			);
		}

		assert(-ScoreIndex::ScoreInfinite < bestScore && bestScore < ScoreIndex::ScoreInfinite);
	}


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// スタティック・メソッドは継承できないので、スタティックにはしないぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="bestMoveExists"></param>
	/// <returns></returns>
	virtual inline Bound GetBoundAtStep20(bool bestMoveExists) const = 0;
};
