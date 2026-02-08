#include "../../header/n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n220_position/n220_665_utilMoveStack.hpp"
#include "../../header/n223_move____/n223_200_depth.hpp"
#include "../../header/n223_move____/n223_500_flashlight.hpp"
#include "../../header/n640_searcher/n640_040_nodeKind.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"	// FIXME:
#include "../../header/n885_searcher/n885_310_adventureBattlefieldQsearchAbstract.hpp"


/// <summary>
/// N01_PV か、N02_NonPV でだけ使うことができるぜ☆（＾ｑ＾）
/// スプリット・ポイントかそうでないかは見てないぜ☆
/// </summary>
/// <param name="ourCarriage"></param>
/// <param name="INCHECK"></param>
/// <param name="pos"></param>
/// <param name="pFlashlight"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <param name="depth"></param>
/// <returns></returns>
Sweetness AdventureBattlefieldQsearchAbstract::ExploreAsQsearch(
	OurCarriage& ourCarriage,
	bool INCHECK,
	Position& pos,
	Flashlight* pFlashlight,
	Sweetness alpha,
	Sweetness beta,
	const Depth depth) const
{

	assert(INCHECK == pos.inCheck());
	assert(-SweetnessInfinite <= alpha && alpha < beta && beta <= SweetnessInfinite);
	this->DoAssert(alpha,beta);
	assert(depth <= Depth0);

	StateInfo st;
	const TTEntry* pTtEntry;
	Key posKey;
	Move ttMove;
	Move move;
	Move bestMove;
	Sweetness bestSweetness;
	Sweetness sweetness;
	Sweetness ttSweetness;
	Sweetness futilitySweetness;
	Sweetness futilityBase;
	Sweetness oldAlpha;
	bool givesCheck;
	bool evasionPrunable;
	Depth ttDepth;

	this->SetOldAlpha(oldAlpha, alpha);

	pFlashlight->m_currentMove = bestMove = g_MOVE_NONE;
	pFlashlight->m_ply = (pFlashlight - 1)->m_ply + 1;

	if (g_maxPly < pFlashlight->m_ply) { return SweetnessDraw; }

	ttDepth = ((INCHECK || DepthQChecks <= depth) ? DepthQChecks : DepthQNoChecks);

	posKey = pos.GetKey();
	pTtEntry = ourCarriage.m_tt.Probe(posKey);
	ttMove = (pTtEntry != nullptr ? UtilMoveStack::Move16toMove(pTtEntry->GetMove(), pos) : g_MOVE_NONE);
	ttSweetness = (pTtEntry != nullptr ? ourCarriage.ConvertSweetnessFromTT(pTtEntry->GetSweetness(), pFlashlight->m_ply) : SweetnessNone);

	if (pTtEntry != nullptr
		&& ttDepth <= pTtEntry->GetDepth()
		&& ttSweetness != SweetnessNone // アクセス競合が起きたときのみ、ここに引っかかる。
		&& this->GetCondition01(
			&pTtEntry,
			beta,
			ttSweetness
			)
	){
		pFlashlight->m_currentMove = ttMove;
		return ttSweetness;
	}

	pos.setNodesSearched(pos.getNodesSearched() + 1);

	if (INCHECK) {
		pFlashlight->m_staticEval = SweetnessNone;
		bestSweetness = futilityBase = -SweetnessInfinite;
	}
	else {
		if (!(move =
			(
				pos.GetTurn()==Color::Black
				?
				pos.GetMateMoveIn1Ply<Color::Black,Color::White>()
				:
				pos.GetMateMoveIn1Ply<Color::White, Color::Black>()
			)			
			).IsNone()) {
			return UtilSweetness::MateIn(pFlashlight->m_ply);
		}

		if (pTtEntry != nullptr) {
			if (
				(pFlashlight->m_staticEval = bestSweetness = pTtEntry->GetEvalSweetness()) == SweetnessNone
				) {
				Evaluation09 evaluation;
				pFlashlight->m_staticEval = bestSweetness = evaluation.evaluate(pos, pFlashlight);
			}
		}
		else {
			Evaluation09 evaluation;
			pFlashlight->m_staticEval = bestSweetness = evaluation.evaluate(pos, pFlashlight);
		}

		if (beta <= bestSweetness) {
			if (pTtEntry == nullptr) {
				ourCarriage.m_tt.Store(pos.GetKey(), ourCarriage.ConvertSweetnessToTT(bestSweetness, pFlashlight->m_ply), BoundLower,
					DepthNone, g_MOVE_NONE, pFlashlight->m_staticEval);
			}

			return bestSweetness;
		}

		// PVノードのとき☆（＾ｑ＾）
		this->SetAlpha(alpha, bestSweetness);

		futilityBase = bestSweetness + 128; // todo: 128 より大きくて良いと思う。
	}

	Evaluation09 evaluation;
	evaluation.evaluate(pos, pFlashlight);

	NextmoveEvent mp(pos, ttMove, depth, ourCarriage.m_history, (pFlashlight - 1)->m_currentMove.To());
	const CheckInfo ci(pos);

	while (!(move = mp.GetNextMove_NonMonkeySplitedPlace()).IsNone())
	{
		assert(pos.IsOK());

		givesCheck = pos.IsMoveGivesCheck(move, ci);

		// futility pruning
		// 非PVノードのとき☆（＾ｑ＾）
		bool isContinue = false;
		this->DoFutilityPruning01(
			isContinue,
			INCHECK,
			givesCheck,
			move,
			ttMove,
			futilitySweetness,
			futilityBase,
			pos,
			beta,
			bestSweetness,
			depth
			);
		if (isContinue) { continue; }

		evasionPrunable = (INCHECK
			&& SweetnessMatedInMaxPly < bestSweetness
			&& !move.IsCaptureOrPawnPromotion());

		// 非PVノードのとき☆（＾ｑ＾）
		this->DoContinue01(
			isContinue,
			INCHECK,
			evasionPrunable,
			move,
			ttMove,
			pos
			);
		if (isContinue) { continue; }

		if (!
			(
				pos.GetTurn()==Color::Black
				?
				pos.IsPseudoLegalMoveIsLegal<false, false, Color::Black,Color::White>(move, ci.m_pinned)
				:
				pos.IsPseudoLegalMoveIsLegal<false, false, Color::White,Color::Black>(move, ci.m_pinned)
			)
		) {
			continue;
		}

		pFlashlight->m_currentMove = move;

		pos.GetTurn()==Color::Black
			?
			pos.DoMove<Color::Black,Color::White>(move, st, ci, givesCheck)
			:
			pos.DoMove<Color::White,Color::Black>(move, st, ci, givesCheck)
			;

		(pFlashlight + 1)->m_staticEvalRaw.m_p[0][0] = SweetnessNotEvaluated;
		sweetness = // 再帰関数☆（＾ｑ＾）
			-this->ExploreAsQsearch(ourCarriage, givesCheck, pos, pFlashlight + 1, -beta, -alpha, depth - OnePly);
		pos.UndoMove(move);

		assert(-SweetnessInfinite < sweetness && sweetness < SweetnessInfinite);

		if (bestSweetness < sweetness) {
			bestSweetness = sweetness;

			if (alpha < sweetness) {
				// PVノードのときは条件付きで手続きが変わるぜ☆（＾ｑ＾）
				bool isReturnWithSweetness = false;
				Sweetness returnSweetness = Sweetness::SweetnessNone;
				this->doByNewSweetness(
					isReturnWithSweetness,
					returnSweetness,
					ourCarriage,
					sweetness,
					beta,
					alpha,
					bestMove,
					posKey,
					&pFlashlight,
					ttDepth,
					move
					);
				if (isReturnWithSweetness) { return returnSweetness; }
			}
		}
	}

	if (INCHECK && bestSweetness == -SweetnessInfinite) { return UtilSweetness::MatedIn(pFlashlight->m_ply); }

	ourCarriage.m_tt.Store(
		posKey,
		ourCarriage.ConvertSweetnessToTT(bestSweetness, pFlashlight->m_ply),
		this->GetBound01( oldAlpha, bestSweetness),
		ttDepth,
		bestMove,
		pFlashlight->m_staticEval
	);

	assert(-SweetnessInfinite < bestSweetness && bestSweetness < SweetnessInfinite);

	return bestSweetness;
}
