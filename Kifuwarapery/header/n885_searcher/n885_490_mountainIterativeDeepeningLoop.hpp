#pragma once


#include "../n080_common__/n080_100_common.hpp"
#include "../n119_score___/n119_090_scoreIndex.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n883_nodeType/n883_070_nodetypeAbstract.hpp"
#include "n885_040_ourCarriage.hpp"
#include "n885_580_skill.hpp"


extern NodetypeAbstract* g_NODETYPE_PROGRAMS[];


/// <summary>
///		<pre>
/// 深い反復ループ☆？（iterative deepening loop）
/// 反復深化探索のことなのかだぜ☆（＾ｑ＾）？
///		</pre>
/// </summary>
class IterativeDeepeningLoop {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pos"></param>
	static inline void Execute885_500(OurCarriage& ourCarriage, Position& pos)
	{
		Flashlight flashlight[g_maxPlyPlus2];
		Ply depth;

		// ベストムーブは何手目かだろうかなんだぜ☆？（＾ｑ＾）？
		Ply prevBestMovePlyChanges;

		ScoreIndex bestScore = -ScoreInfinite;
		ScoreIndex delta = -ScoreInfinite;
		ScoreIndex alpha = -ScoreInfinite;
		ScoreIndex beta = ScoreInfinite;
		bool bestMoveNeverChanged = true;
		int lastInfoTime = -1; // 将棋所のコンソールが詰まる問題への対処用

		memset(flashlight, 0, 4 * sizeof(Flashlight));
		ourCarriage.ZeroclearBestMovePlyChanges();
#if defined LEARN
		// 高速化の為に浅い探索は反復深化しないようにする。学習時は浅い探索をひたすら繰り返す為。
		GetDepth = std::max<Ply>(0, m_limits.GetDepth - 1);
#else
		depth = 0;
#endif

		flashlight[0].m_currentMove = g_MOVE_NULL; // skip update gains
		ourCarriage.m_tt.NewSearch();
		ourCarriage.m_history.Clear();
		ourCarriage.m_gains.Clear();

		// マルチＰＶの数☆？
		ourCarriage.m_pvSize = ourCarriage.m_engineOptions["MultiPV"];
		Skill skill(ourCarriage.m_engineOptions["Skill_Level"], ourCarriage.m_engineOptions["Max_Random_Score_Diff"]);

		if (ourCarriage.m_engineOptions["Max_Random_Score_Diff_Ply"] < pos.GetGamePly()) {
			skill.m_maxRandomScoreDiff = ScoreZero;
			ourCarriage.m_pvSize = 1;
			assert(!skill.enabled()); // level による設定が出来るようになるまでは、これで良い。
		}

		if (skill.enabled() && ourCarriage.m_pvSize < 3) {
			ourCarriage.m_pvSize = 3;
		}
		ourCarriage.m_pvSize = std::min(ourCarriage.m_pvSize, ourCarriage.m_rootMoves.size());

		// 指し手が無ければ負け
		if (ourCarriage.m_rootMoves.empty()) {
			ourCarriage.m_rootMoves.push_back(RootMove(g_MOVE_NONE));
			SYNCCOUT << "info depth 0 score "
				<< ourCarriage.scoreToUSI(-ScoreMate0Ply)
				<< SYNCENDL;

			return;
		}

#if defined BISHOP_IN_DANGER
		if ((bishopInDangerFlag == BlackBishopInDangerIn28
			&& std::find_if(std::begin(m_rootMoves), std::IsEnd(m_rootMoves),
				[](const RootMove& rm) { return rm.m_pv_[0].ToCSA() == "0082KA"; }) != std::IsEnd(m_rootMoves))
			|| (bishopInDangerFlag == WhiteBishopInDangerIn28
				&& std::find_if(std::begin(m_rootMoves), std::IsEnd(m_rootMoves),
					[](const RootMove& rm) { return rm.m_pv_[0].ToCSA() == "0028KA"; }) != std::IsEnd(m_rootMoves))
			|| (bishopInDangerFlag == BlackBishopInDangerIn78
				&& std::find_if(std::begin(m_rootMoves), std::IsEnd(m_rootMoves),
					[](const RootMove& rm) { return rm.m_pv_[0].ToCSA() == "0032KA"; }) != std::IsEnd(m_rootMoves))
			|| (bishopInDangerFlag == WhiteBishopInDangerIn78
				&& std::find_if(std::begin(m_rootMoves), std::IsEnd(m_rootMoves),
					[](const RootMove& rm) { return rm.m_pv_[0].ToCSA() == "0078KA"; }) != std::IsEnd(m_rootMoves)))
		{
			if (m_rootMoves.m_size() != 1)
				m_pvSize = std::max<size_t>(m_pvSize, 2);
		}
#endif

		// 反復深化で探索を行う。
		while (++depth <= g_maxPly && !ourCarriage.m_signals.m_stop && (!ourCarriage.m_limits.m_depth || depth <= ourCarriage.m_limits.m_depth)) {

			// 前回の iteration の結果を全てコピー
			for (size_t i = 0; i < ourCarriage.m_rootMoves.size(); ++i) {
				ourCarriage.m_rootMoves[i].m_prevScore_ = ourCarriage.m_rootMoves[i].m_score_;
			}

			prevBestMovePlyChanges = ourCarriage.GetBestMovePlyChanges();
			ourCarriage.ZeroclearBestMovePlyChanges(); // 退避したので、ゼロクリアーするぜ☆（＾ｑ＾）

			// Multi PV loop
			for (ourCarriage.m_pvIdx = 0; ourCarriage.m_pvIdx < ourCarriage.m_pvSize && !ourCarriage.m_signals.m_stop; ++ourCarriage.m_pvIdx) {
#if defined LEARN
				m_alpha = ourCarriage.m_alpha;
				m_beta = ourCarriage.m_beta;
#else
				// aspiration search
				// alpha, beta をある程度絞ることで、探索効率を上げる。
				if (
					// 深さ５以上で
					5 <= depth &&
					abs(ourCarriage.m_rootMoves[ourCarriage.m_pvIdx].m_prevScore_) < PieceScore::m_ScoreKnownWin
					) {
					delta = static_cast<ScoreIndex>(16);
					alpha = ourCarriage.m_rootMoves[ourCarriage.m_pvIdx].m_prevScore_ - delta;
					beta = ourCarriage.m_rootMoves[ourCarriage.m_pvIdx].m_prevScore_ + delta;
				}
				else {
					alpha = -ScoreInfinite;
					beta = ScoreInfinite;
				}
#endif

				// aspiration search の window 幅を、初めは小さい値にして探索し、
				// fail high/low になったなら、今度は window 幅を広げて、再探索を行う。
				while (true) {
					// 探索を行う。
					flashlight->m_staticEvalRaw.m_p[0][0] = (flashlight + 1)->m_staticEvalRaw.m_p[0][0] = ScoreNotEvaluated;

					//────────────────────────────────────────────────────────────────────────────────
					// 探索☆？（＾ｑ＾）　１回目のぐるんぐるんだぜ～☆　ルート～☆
					//────────────────────────────────────────────────────────────────────────────────
					bestScore = g_NODETYPE_PROGRAMS[NodeType::N00_Root]->GoToTheAdventure_new(ourCarriage, pos, flashlight + 1, alpha, beta, static_cast<Depth>(depth * OnePly), false);

					// 先頭が最善手になるようにソート
					UtilMoveStack::InsertionSort(ourCarriage.m_rootMoves.begin() + ourCarriage.m_pvIdx, ourCarriage.m_rootMoves.end());

					for (size_t i = 0; i <= ourCarriage.m_pvIdx; ++i) {
						flashlight->m_staticEvalRaw.m_p[0][0] = (flashlight + 1)->m_staticEvalRaw.m_p[0][0] = ScoreNotEvaluated;
						ourCarriage.m_rootMoves[i].InsertPvInTT(pos);
					}

#if 0
					// 詰みを発見したら即指す。
					if (ScoreMateInMaxPly <= abs(ourCarriage.m_bestScore) && abs(ourCarriage.m_bestScore) < ScoreInfinite) {
						SYNCCOUT << PvInfoToUSI(GetPos, ourCarriage.m_ply, ourCarriage.m_alpha, ourCarriage.m_beta) << SYNCENDL;
						ourCarriage.m_signals.m_stop = true;
					}
#endif

#if defined LEARN
					break;
#endif

					if (ourCarriage.m_signals.m_stop) { break; }
					if (alpha < bestScore && bestScore < beta) { break; }

					if (
						// 思考時間が3秒経過するまで、読み筋を出力しないぜ☆！（＾ｑ＾）
						3000 < ourCarriage.m_stopwatch.GetElapsed()
						// 将棋所のコンソールが詰まるのを防ぐ。
						&& (depth < 10 || lastInfoTime + 200 < ourCarriage.m_stopwatch.GetElapsed()))
					{
						lastInfoTime = ourCarriage.m_stopwatch.GetElapsed();
						SYNCCOUT << ourCarriage.PvInfoToUSI(pos, depth, alpha, beta) << SYNCENDL;
					}

					// fail high/low のとき、aspiration window を広げる。
					if (PieceScore::m_ScoreKnownWin <= abs(bestScore)) {
						// 勝ち(負け)だと判定したら、最大の幅で探索を試してみる。
						alpha = -ScoreInfinite;
						beta = ScoreInfinite;
					}
					else if (beta <= bestScore) {
						beta += delta;
						delta += delta / 2;
					}
					else {
						ourCarriage.m_signals.m_failedLowAtRoot = true;
						ourCarriage.m_signals.m_stopOnPonderHit = false;

						alpha -= delta;
						delta += delta / 2;
					}

					assert(-ScoreInfinite <= alpha && beta <= ScoreInfinite);
				}

				UtilMoveStack::InsertionSort(ourCarriage.m_rootMoves.begin(), ourCarriage.m_rootMoves.begin() + ourCarriage.m_pvIdx + 1);

				if (
					(
						ourCarriage.m_pvIdx + 1 == ourCarriage.m_pvSize ||
						// 思考時間が3秒経過するまで、読み筋を出力しないぜ☆！（＾ｑ＾）
						3000 < ourCarriage.m_stopwatch.GetElapsed()
					)
					// 将棋所のコンソールが詰まるのを防ぐ。
					&& (depth < 10 || lastInfoTime + 200 < ourCarriage.m_stopwatch.GetElapsed()))
				{
					lastInfoTime = ourCarriage.m_stopwatch.GetElapsed();
					SYNCCOUT << ourCarriage.PvInfoToUSI(pos, depth, alpha, beta) << SYNCENDL;
				}
			}

			//if (skill.enabled() && skill.timeToPick(depth)) {
			//	skill.pickMove();
			//}

			if (
				ourCarriage.m_limits.IsBrandnewTimeMgr() // 反復深化探索に潜るために真であることが必要☆
				&&
				!ourCarriage.m_signals.m_stopOnPonderHit
			) {
				bool stop = false;

				// 深さが 5 ～ 49 で、PVサイズが 1 のとき。
				if (4 < depth && depth < 50 && ourCarriage.m_pvSize == 1) {
					ourCarriage.m_timeMgr.SetPvInstability(ourCarriage.GetBestMovePlyChanges(), prevBestMovePlyChanges);
				}

				// 次のイテレーションを回す時間が無いなら、ストップ
				if (
					!ourCarriage.m_timeMgr.IsTimeOk_CanIterativeDeeping(ourCarriage.m_stopwatch.GetElapsed())
					) {
					stop = true;
				}

				if (2 < depth && ourCarriage.GetBestMovePlyChanges()) {
					bestMoveNeverChanged = false;
				}

				// 最善手が、ある程度の深さまで同じであれば、
				// その手が突出して良い手なのだろう。
				if (
					12 <= depth
					&& !stop
					&& bestMoveNeverChanged
					&& ourCarriage.m_pvSize == 1
					// ここは確実にバグらせないようにする。
					&& -ScoreInfinite + 2 * PieceScore::m_capturePawn <= bestScore
					&& (
						ourCarriage.m_rootMoves.size() == 1
						||
						// または、まだ反復深化探索していい時間が残ってるなら。
						ourCarriage.m_timeMgr.IsTimeOk_CanIterativeDeeping(ourCarriage.m_stopwatch.GetElapsed())
					)
				) {
					const ScoreIndex rBeta = bestScore - 2 * PieceScore::m_capturePawn;
					(flashlight + 1)->m_staticEvalRaw.m_p[0][0] = ScoreNotEvaluated;
					(flashlight + 1)->m_excludedMove = ourCarriage.m_rootMoves[0].m_pv_[0];
					(flashlight + 1)->m_skipNullMove = true;

					//────────────────────────────────────────────────────────────────────────────────
					// さあ、探索に潜るぜ～☆！（＾ｑ＾）　２回目のぐるんぐるんだぜ～☆ ノンＰＶ～☆
					//────────────────────────────────────────────────────────────────────────────────
					const ScoreIndex s = g_NODETYPE_PROGRAMS[NodeType::N02_NonPV]->GoToTheAdventure_new(
						ourCarriage, pos, flashlight + 1, rBeta - 1, rBeta, (depth - 3) * OnePly, true);

					(flashlight + 1)->m_skipNullMove = false;
					(flashlight + 1)->m_excludedMove = g_MOVE_NONE;

					if (s < rBeta) {
						stop = true;
					}
				}

				if (stop) {
					if (ourCarriage.m_limits.m_canPonder) {
						ourCarriage.m_signals.m_stopOnPonderHit = true;
					}
					else {
						ourCarriage.m_signals.m_stop = true;
					}
				}
			}
		}
		skill.swapIfEnabled(&ourCarriage);
		SYNCCOUT << ourCarriage.PvInfoToUSI(pos, depth - 1, alpha, beta) << SYNCENDL;
	}
};
