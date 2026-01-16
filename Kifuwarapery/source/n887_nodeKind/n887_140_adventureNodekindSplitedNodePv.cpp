#include <iostream>
#include <algorithm>
#include "../../header/n210_score___/n119_200_pieceScore.hpp"
#include "../../header/n160_boardBb_/n160_106_inFrontMaskBb.hpp"
#include "../../header/n160_boardBb_/n160_220_queenAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_230_setMaskBb.hpp"
#include "../../header/n220_position/n220_100_repetitionType.hpp"
#include "../../header/n220_position/n220_640_utilAttack.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n220_position/n220_665_utilMoveStack.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n223_move____/n223_300_moveAndScoreIndex.hpp"
#include "../../header/n223_move____/n223_500_flashlight.hpp"
#include "../../header/n250_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n250_pieceTyp/n350_500_ptPrograms.hpp"
#include "../../header/n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../../header/n520_evaluate/n520_700_evaluation09.hpp"
#include "../../header/n560_timeMgr_/n560_500_timeManager.hpp"
#include "../../header/n600_book____/n600_500_book.hpp"
#include "../../header/n640_searcher/n640_040_nodeKind.hpp"
#include "../../header/n640_searcher/n640_440_splitedNode.hpp" // Searcherと持ち合い
#include "../../header/n640_searcher/n640_500_reductions.hpp"
#include "../../header/n640_searcher/n640_510_futilityMargins.hpp"
#include "../../header/n640_searcher/n640_520_futilityMoveCounts.hpp"
#include "../../header/n680_egOption/n680_240_engineOptionsMap.hpp"
#include "../../header/n680_egOption/n680_300_engineOptionSetup.hpp"
#include "../../header/n760_thread__/n760_400_herosPub.hpp"

#include "../../header/n800_learn___/n800_100_stopwatch.hpp"
#include "../../header/n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"

#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"
#include "../../header/n885_searcher/n885_310_adventureBattlefieldQsearchAbstract.hpp"
#include "../../header/n885_searcher/n885_340_adventureBattlefieldQsearchPrograms.hpp"
#include "../../header/n885_searcher/n885_480_adventureSwampNyugyoku.hpp"
#include "../../header/n885_searcher/n885_490_adventureMountainIterativeDeepeningLoop.hpp"
#include "../../header/n885_searcher/n885_510_adventureContinent.hpp"
#include "../../header/n886_repeType/n886_100_rtNot.hpp"
#include "../../header/n886_repeType/n886_110_rtDraw.hpp"
#include "../../header/n886_repeType/n886_120_rtWin.hpp"
#include "../../header/n886_repeType/n886_130_rtLose.hpp"
#include "../../header/n886_repeType/n886_140_rtSuperior.hpp"
#include "../../header/n886_repeType/n886_150_rtInferior.hpp"
#include "../../header/n886_repeType/n886_500_rtArray.hpp"
#include "../../header/n887_nodeKind/n887_140_adventurePlainNodekindSplitedNodePv.hpp"
#include "../../header/n887_nodeKind/n887_500_adventurePlainNodekindPrograms.hpp"


using namespace std;


extern const InFrontMaskBb g_inFrontMaskBb;
extern AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[];
//extern RepetitionTypeModels g_repetitionTypes;


AdventureNodekindSplitedNodePv g_NODEKIND_SPLITEDNODE_PV;


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
ScoreIndex AdventureNodekindSplitedNodePv::ExplorePlain(
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight,//サーチスタック
	ScoreIndex alpha,
	ScoreIndex beta,
	const Depth depth,
	const bool cutNode
	) const {

	assert(-ScoreInfinite <= alpha && alpha < beta && beta <= ScoreInfinite);
	this->AssertBeforeStep1(
		alpha,
		beta
		);
	assert(Depth0 < depth);

	// 途中で goto を使用している為、先に全部の変数を定義しておいた方が安全。
	Move movesSearched[64];
	StateInfo st;
	const TTEntry* pTtEntry = nullptr;//(^q^)トランスポジション・テーブル・エントリー☆？
	SplitedNode* pSplitedNode = nullptr;//(^q^)
	Key posKey;
	Move ttMove;
	Move move;
	Move excludedMove;
	Move bestMove;
	Move threatMove;
	Depth newDepth;
	Depth extension;
	ScoreIndex bestScore;
	ScoreIndex score;
	ScoreIndex ttScore;
	ScoreIndex eval;
	bool inCheck;
	bool givesCheck;
	bool isPVMove;
	bool singularExtensionNode;
	bool captureOrPawnPromotion;
	bool dangerous;
	bool doFullDepthSearch;
	int moveCount;
	int playedMoveCount;

	// step1
	// initialize node
	Soldier* pThisThread = pos.GetThisThread();
	moveCount = playedMoveCount = 0;
	inCheck = pos.InCheck();

	bool isGotoSplitPointStart = false;
	this->ExplorerPlainStep1a1InitializeNode(
		isGotoSplitPointStart,
		pos,
		&pSplitedNode,
		&pFlashlight,
		bestMove,
		threatMove,
		bestScore,
		ttMove,
		excludedMove,
		ttScore);
	if (isGotoSplitPointStart) { goto split_point_start; }

	this->ExplorerPlainStep1bSetMoveNone(
		bestScore,
		&pFlashlight,
		threatMove,
		bestMove);
	this->ExplorerPlainStep1cUpdateMaxPly(
		&pThisThread,
		pFlashlight);

	// step2: 千日手による探索打切りの判断
	{
		auto p = this->ExplorerPlainStep2_IsStopByRepetetion(
			//isReturnWithScore,
			//returnScore,
			pos,
			ourCarriage,
			&pFlashlight
		);
		bool isReturnWithScore = p.first;
		ScoreIndex returnScore = p.second;
		if (isReturnWithScore) { return returnScore; }
	}

	bool isReturnWithScore = false;
	ScoreIndex returnScore = ScoreNone;

	// step3
	this->ExplorerPlainStep3(
		isReturnWithScore,
		returnScore,
		&pFlashlight,
		alpha,
		beta
		);
	if (isReturnWithScore) { return returnScore; }

	pos.SetNodesSearched(pos.GetNodesSearched() + 1);

	// step4
	this->ExplorerPlainStep4(
		excludedMove,
		&pFlashlight,
		posKey,
		pos,
		&pTtEntry,//セットされる☆
		ourCarriage,
		ttScore
		);
	this->ExplorerPlainStep4x(
		ttMove,
		ourCarriage,
		pTtEntry,
		pos
		);
	this->ExplorerPlainStep4y(
		isReturnWithScore,
		returnScore,
		ourCarriage,
		pTtEntry,
		depth,
		ttScore,
		beta,
		&pFlashlight,
		ttMove
		);
	if (isReturnWithScore) { return returnScore; }

	this->ExplorerPlainStep4z(
		isReturnWithScore,
		returnScore,
		ourCarriage,
		inCheck,
		move,
		pos,
		&pFlashlight,
		bestScore,
		posKey,
		depth,
		bestMove
		);
	if (isReturnWithScore) { return returnScore; }

	// step5
	bool isGotoIidStart = false;//NonPVのとき使う☆
	this->ExplorerPlainStep5(
		isGotoIidStart,
		ourCarriage,
		eval,
		&pFlashlight,
		pos,
		inCheck,
		pTtEntry,
		ttScore,
		posKey,
		move
		);
	/*
	if (isGotoIidStart) {
		goto iid_start;
	}
	*/

	// 内側の反復深化探索☆？（＾ｑ＾）
//iid_start:
	// step10
	this->ExplorerPlainStep10_InternalIterativeDeepening(
		depth,
		ttMove,
		inCheck,
		beta,
		&pFlashlight,
		ourCarriage,
		pos,
		alpha,
		&pTtEntry,//セットされるぜ☆
		posKey
		);

split_point_start:
	NextmoveEvent mp(
		pos,
		ttMove,
		depth,
		ourCarriage.m_history,
		pFlashlight,
		this->GetBetaAtStep11(beta)//PVノードか、そうでないかで初期値を変えるぜ☆（＾ｑ＾）
		);
	const CheckInfo ci(pos);

	this->ExplorerPlainStep11a_BeforeLoop_SplitPointStart(
		ttMove,
		depth,
		score,
		bestScore,
		singularExtensionNode,
		excludedMove,
		pTtEntry//pv,nonPv の２つで、nullptrはダメ☆
		);

	// step11
	// Loop through moves
	while (
		!(
			// スプリット・ポイントかどうかで、取ってくる指し手が変わる☆
			move = this->GetNextMove_AtStep11(mp)
			).IsNone()
		) {

		// DoStep11b
		if (move == excludedMove) { continue; }	// ムーブが一致していれば、次のループへ☆

		bool isContinue = false;

		this->ExplorerPlainStep11c_LoopHeader(
			isContinue,
			pos,
			move,
			ci,
			moveCount,
			&pSplitedNode
			);
		if (isContinue) { continue; }

		this->ExplorerPlainStep11f_LoopHeader(
			extension,
			captureOrPawnPromotion,
			move,
			givesCheck,
			ci,
			pos,
			dangerous
			);

		// step12
		this->ExplorerPlainStep12(
			ourCarriage,
			givesCheck,
			pos,
			move,
			extension,
			singularExtensionNode,
			ttMove,
			ttScore,
			ci,
			depth,
			&pFlashlight,
			score,
			cutNode,
			beta,
			newDepth
			);

		// 本筋かどうか判定するぜ（＾～＾）
		isPVMove = this->ExplorerPlainStep13c1IsPvMove(moveCount);

		this->ExplorerPlainStep13c2SetMove(
			move,
			&pFlashlight);
		if (isContinue) { continue; }

		// step14
		this->ExplorerPlainStep14(
			pos,
			move,
			st,
			ci,
			givesCheck,
			&pFlashlight
			);

		// step15
		this->ExplorerPlainStep15(
			ourCarriage,
			depth,
			isPVMove,
			captureOrPawnPromotion,
			move,
			ttMove,
			&pFlashlight,
			moveCount,
			cutNode,
			newDepth,
			alpha,
			&pSplitedNode,
			score,
			pos,
			doFullDepthSearch
			);

		// step16
		this->ExplorerPlainStep16a(
			doFullDepthSearch,
			alpha,
			&pSplitedNode
			);
		this->ExplorerPlainStep16b_NonPVAtukai(
			ourCarriage,
			doFullDepthSearch,
			score,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight,
			alpha,
			cutNode
			);
		this->ExplorerPlainStep16c(
			ourCarriage,
			isPVMove,
			alpha,
			score,
			beta,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight
			);

		// step17
		this->ExplorerPlainStep17(
			pos,
			move
			);

		assert(-ScoreInfinite < score && score < ScoreInfinite);

		// step18
		this->ExplorerPlainStep18a(
			&pSplitedNode,
			bestScore,
			alpha
			);

		if (ourCarriage.m_signals.m_stop || pThisThread->IsUselessNode()) { return score; }

		bool isBreak = false;
		this->ExplorerPlainStep18c(
			isBreak,
			ourCarriage,
			move,
			isPVMove,
			alpha,
			score,
			pos,
			bestScore,
			&pSplitedNode,
			bestMove,
			beta
			);
		if (isBreak) { break; }
	}

	if (this->GetReturnBeforeStep20()) { return bestScore; }

	return bestScore;
}
