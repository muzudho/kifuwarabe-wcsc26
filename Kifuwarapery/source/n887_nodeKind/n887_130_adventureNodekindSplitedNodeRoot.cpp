#include <iostream>
#include <algorithm>
#include "../../header/n210_score___/n119_200_pieceScore.hpp"
#include "../../header/n130_100_boardBb_/n160_106_inFrontMaskBb.hpp"
#include "../../header/n130_100_boardBb_/n160_220_queenAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_230_setMaskBb.hpp"
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
#include "../../header/n760_thread__/n760_400_MonkiesPub.hpp"
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
#include "../../header/n887_nodeKind/n887_130_adventurePlainNodekindSplitedNodeRoot.hpp"
#include "../../header/n887_nodeKind/n887_500_adventurePlainNodekindPrograms.hpp"


using namespace std;


extern const InFrontMaskBb g_inFrontMaskBb;
extern AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[];
//extern RepetitionTypeModels g_repetitionTypes;


AdventureNodekindSplitedNodeRoot g_NODEKIND_SPLITEDNODE_ROOT;


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
ScoreNumber AdventureNodekindSplitedNodeRoot::explorePlain_n10(
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight,//サーチスタック
	ScoreNumber alpha,
	ScoreNumber beta,
	const Depth depth,
	const bool cutNode) const
{


	assert(-ScoreInfinite <= alpha && alpha < beta && beta <= ScoreInfinite);
	this->explorePlain_n100n800_assert(
		alpha,
		beta);
	assert(Depth0 < depth);


	// 途中で goto を使用している為、先に全部の変数を定義しておいた方が安全。
	Move movesSearched[64];
	StateInfo st;
	const TTEntry* pTtEntry = nullptr;//(^q^)トランスポジション・テーブル・エントリー☆？
	SplitedNode* pSplitedNode = nullptr;//(^q^)
	Key posKey;
	Move move;
	Move excludedMove;
	Move bestMove;
	Move threatMove;
	Depth newDepth;
	Depth extension;
	ScoreNumber bestScore;
	ScoreNumber score;
	ScoreNumber eval;
	bool inCheck;
	bool givesCheck;
	bool isPVMove;	// 本筋の指し手かどうかかなあ（＾～＾）？
	bool singularExtensionNode;
	bool captureOrPawnPromotion;
	bool dangerous;
	bool doFullDepthSearch;
	int moveCount;
	int playedMoveCount;
	Move bananaTtMove;
	ScoreNumber bananaTtScore;
	DeliciousBanana ttDeliciousBanana;

	// step1
	// initialize node
	Monkey* pThisThread = pos.GetHandleMonkey();
	moveCount = playedMoveCount = 0;
	inCheck = pos.InCheck();


	bool isGotoSplitPointStart = false;
	this->explorePlain_n100n900_splitPointStart(
		isGotoSplitPointStart,
		pos,
		&pSplitedNode,
		&pFlashlight,
		bestMove,
		threatMove,
		bestScore,
		bananaTtMove,
		excludedMove,
		bananaTtScore);
	if (isGotoSplitPointStart) { goto split_point_start; }


	// ヌル指し手セット


	this->explorePlain_n200n150_setMoveNone(
		bestScore,
		&pFlashlight,
		threatMove,
		bestMove);


	this->explorePlain_n200n200_updateMaxPly(
		&pThisThread,
		pFlashlight);


	bool isReturnWithScore = false;
	ScoreNumber returnScore = ScoreNumber::ScoreNone;

	pos.SetNodesVisited(pos.GetNodesVisited() + 1);


	// ttScore と ttMove でデリシャス・バナナ（＾～＾）！
	{
		DeliciousBanana ttDeliciousBanana = this->explorePlain_n200n405_getTtDeliciousBanana(
			excludedMove,
			&pFlashlight,
			posKey,
			pos,
			&pTtEntry,	//セットされる☆
			ourCarriage,
			pTtEntry);
		bananaTtScore = (ScoreNumber)ttDeliciousBanana.m_score;
		bananaTtMove = ttDeliciousBanana.m_move;
	}


	// step5
	bool isGotoIidStart = false;//NonPVのとき使う☆


	this->explorePlain_n200n550_eval(
		isGotoIidStart,
		ourCarriage,
		eval,
		&pFlashlight,
		pos,
		inCheck,
		pTtEntry,
		bananaTtScore,
		posKey,
		move);
	/*
	if (isGotoIidStart) {
		goto iid_start;
	}
	*/


	// 内側の反復深化探索☆？（＾ｑ＾）
//iid_start:
	this->explorePlain_n200n800_internalIterativeDeepening(
		depth,
		bananaTtMove,
		inCheck,
		beta,
		&pFlashlight,
		ourCarriage,
		pos,
		alpha,
		&pTtEntry,//セットされるぜ☆
		posKey);


	// 読み筋の分岐点かだぜ（＾～＾）？
split_point_start:
	NextmoveEvent nextMoveEvent(
		pos,
		bananaTtMove,
		depth,
		ourCarriage.m_history,
		pFlashlight,
		this->getBeta_n140(beta)		//PVノードか、そうでないかで初期値を変えるぜ☆（＾ｑ＾）
		);


	const CheckInfo ci(pos);


	this->explorePlain_n200n900_beforeLoop_splitPointStart(
		bananaTtMove,
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
			move = this->getNextMove_n160(nextMoveEvent)
			).IsNone()
	) {


		// 指さずに探索する前


		if (move == excludedMove) { continue; }	// ムーブが一致していれば、次のループへ☆


		bool isContinue = false;


		this->explorePlain_n300n500_loopHeader(
			isContinue,
			pos,
			move,
			ci,
			moveCount,
			&pSplitedNode);
		if (isContinue) { continue; }


		this->explorePlain_n300n600_loopHeader(
			isContinue,
			ourCarriage,
			move);
		if (isContinue) { continue; }


		this->explorePlain_n300n700_displayInfo(
			ourCarriage,
			moveCount);


		this->explorePlain_n300n900_loopHeader(
			extension,
			captureOrPawnPromotion,
			move,
			givesCheck,
			ci,
			pos,
			dangerous);


		// 指さずに探索処理


		this->explorePlain_n400n500_recursiveSearch(
			ourCarriage,
			givesCheck,
			pos,
			move,
			extension,
			singularExtensionNode,
			bananaTtMove,
			bananaTtScore,
			ci,
			depth,
			&pFlashlight,
			score,
			cutNode,
			beta,
			newDepth);


		// 本筋かどうか判定するぜ（＾～＾）
		isPVMove = this->explorePlain_n400n700_isPvMove(moveCount);


		this->explorePlain_n400n800_setMove(
			move,
			&pFlashlight);
		if (isContinue) { continue; }


		// ドゥムーブ処理


		this->explorerPlain_n500n100_doMove(
			pos,
			move,
			st,
			ci,
			givesCheck,
			&pFlashlight);


		// ドゥムーブ後処理


		// 探索処理


		this->explorePlain_n500n500_recursiveSearch(
			ourCarriage,
			depth,
			isPVMove,
			captureOrPawnPromotion,
			move,
			bananaTtMove,
			&pFlashlight,
			moveCount,
			cutNode,
			newDepth,
			alpha,
			&pSplitedNode,
			score,
			pos,
			doFullDepthSearch);


		// 探索後処理


		this->explorePlain_n600n700_setAlpha(
			doFullDepthSearch,
			alpha,
			&pSplitedNode);


		this->explorePlain_n500n600_nonPVRecursiveSearch(
			ourCarriage,
			doFullDepthSearch,
			score,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight,
			alpha,
			cutNode);


		this->explorePlain_n600n900_betaLargeRecursiveSearch(
			ourCarriage,
			isPVMove,
			alpha,
			score,
			beta,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight);


		// アンドゥ処理


		this->explorePlain_n700n100_undoMove(
			pos,
			move);


		// アンドゥ後処理


		assert(-ScoreInfinite < score && score < ScoreInfinite);


		this->explorePlain_n700n500_setAlpha(
			&pSplitedNode,
			bestScore,
			alpha
			);


		if (ourCarriage.m_signals.m_isIterationDeepingStop || pThisThread->IsUselessSplitedNode()) { return score; }


		this->explorePlain_n700n600_findRootNode(
			ourCarriage,
			move,
			isPVMove,
			alpha,
			score,
			pos);


		// アップデートα処理


		bool isBreak = false;
		this->explorePlain_n700n700_updateAlpha(
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
			beta);
		if (isBreak) { break; }


		// アップデートα後処理


	}


	// ループ後処理


	if (this->getReturn_n800n400()) { return bestScore; }


	return bestScore;
}
