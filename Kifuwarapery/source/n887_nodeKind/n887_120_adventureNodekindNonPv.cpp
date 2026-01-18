#include <iostream>
#include <algorithm>
#include "../../header/n119_score___/n119_200_pieceScore.hpp"
#include "../../header/n160_board___/n160_106_inFrontMaskBb.hpp"
#include "../../header/n160_board___/n160_220_queenAttackBb.hpp"
#include "../../header/n160_board___/n160_230_setMaskBb.hpp"
#include "../../header/n220_position/n220_100_repetitionType.hpp"
#include "../../header/n220_position/n220_640_utilAttack.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n220_position/n220_665_utilMoveStack.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n223_move____/n223_300_moveAndScoreIndex.hpp"
#include "../../header/n223_move____/n223_500_flashlight.hpp"
#include "../../header/n350_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n350_pieceTyp/n350_500_ptPrograms.hpp"
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
#include "../../header/n760_thread__/n760_400_monkiesPub.hpp"
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
#include "../../header/n887_nodeKind/n887_120_adventurePlainNodekindNonPv.hpp"
#include "../../header/n887_nodeKind/n887_500_adventurePlainNodekindPrograms.hpp"


using namespace std;
extern const InFrontMaskBb g_inFrontMaskBb;
extern AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[];
//extern RepetitionTypeModels g_repetitionTypes;
AdventureNodekindNonPv g_NODEKIND_NON_PV;


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
ScoreIndex AdventureNodekindNonPv::explorePlain_10i(
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight,//サーチスタック
	ScoreIndex alpha,
	ScoreIndex beta,
	const Depth depth,
	const bool cutNode) const
{


	assert(-ScoreInfinite <= alpha && alpha < beta && beta <= ScoreInfinite);
	this->explorePlain_10i100j100k_assertAtFirst(
		alpha,
		beta);
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
	bool isPVMove;	// 本筋の指し手かどうかかなあ（＾～＾）？
	bool singularExtensionNode;
	bool captureOrPawnPromotion;
	bool dangerous;
	bool doFullDepthSearch;
	int moveCount;
	int playedMoveCount;


	// step1
	// initialize node
	Monkie* pHandleMonkey = pos.getHandleMonkey();	// 局面に対応する猿
	moveCount = playedMoveCount = 0;
	inCheck = pos.inCheck();

	bool isGotoSplitPointStart = false;


	this->explorePlain_10i200j120k_clearMove(
		bestScore,
		&pFlashlight,
		threatMove,
		bestMove);


	// step2: 千日手による探索打切りの判断
	auto p = this->explorePlain_10i200j160k_isStopByRepetetion(
		//isReturnWithScore,
		//returnScore,
		pos,
		ourCarriage,
		&pFlashlight);


	bool isReturnWithScore = p.first;
	ScoreIndex returnScore = p.second;
	if (isReturnWithScore) { return returnScore; }


	this->explorePlain_10i200j180k_checkAlpha(
		isReturnWithScore,
		returnScore,
		&pFlashlight,
		alpha,
		beta);
	if (isReturnWithScore) { return returnScore; }


	pos.setNodesSearched(pos.getNodesSearched() + 1);


	this->explorePlain_10i200j200k_getTtScore(
		excludedMove,
		&pFlashlight,
		posKey,
		pos,
		&pTtEntry,//セットされる☆
		ourCarriage,
		ttScore);
	this->explorePlain_10i200j220k_getTtMove(
		ttMove,
		ourCarriage,
		pTtEntry,
		pos);


	this->explorePlain_10i200j240k_killerMove(
		isReturnWithScore,
		returnScore,
		ourCarriage,
		pTtEntry,
		depth,
		ttScore,
		beta,
		&pFlashlight,
		ttMove);
	if (isReturnWithScore) { return returnScore; }


	this->explorePlain_10i200j260k_ttMove(
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
		bestMove);
	if (isReturnWithScore) { return returnScore; }


	bool isGotoIidStart = false;//NonPVのとき使う☆
	this->explorePlain_10i200j280k_evelScore(
		isGotoIidStart,
		ourCarriage,
		eval,
		&pFlashlight,
		pos,
		inCheck,
		pTtEntry,
		ttScore,
		posKey,
		move);
	if (isGotoIidStart) { goto iid_start; }


	this->ExplorerPlainStep6_NonPV(
		isReturnWithScore,
		returnScore,
		ourCarriage,
		depth,
		eval,
		beta,
		ttMove,
		pos,
		&pFlashlight);
	if (isReturnWithScore) { return returnScore; }


	this->ExplorerPlainStep7(
		isReturnWithScore,
		returnScore,
		&pFlashlight,
		depth,
		beta,
		eval);
	if (isReturnWithScore) { return returnScore; }


	this->ExplorerPlainStep8_NonPV(
		isReturnWithScore,
		returnScore,
		ourCarriage,
		&pFlashlight,
		depth,
		beta,
		eval,
		pos,
		st,
		alpha,
		cutNode,
		threatMove);
	if (isReturnWithScore) { return returnScore; }


	this->ExplorerPlainStep9(
		isReturnWithScore,
		ourCarriage,
		depth,
		&pFlashlight,
		beta,
		move,
		pos,
		ttMove,
		st,
		score,
		cutNode);
	if (isReturnWithScore) { return score; }


	// 内側の反復深化探索☆？（＾ｑ＾）
iid_start:
	this->explorerPlain_10i300j100k_internalIterativeDeepening(
		depth,
		ttMove,
		inCheck,
		beta,
		&pFlashlight,
		ourCarriage,
		pos,
		alpha,
		&pTtEntry,//セットされるぜ☆
		posKey);


//split_point_start:
	NextmoveEvent nextmoveEvent(
		pos,
		ttMove,
		depth,
		ourCarriage.m_history,
		pFlashlight,
		this->getBeta_10i300j150k(beta)//PVノードか、そうでないかで初期値を変えるぜ☆（＾ｑ＾）
		);
	const CheckInfo checkInfo(pos);


	this->explorePlain_10i300j200k_beforeLoopSplitPointStart(
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
			move = this->getNextMove_10i400j100k(nextmoveEvent)
			).IsNone()
		) {


		// DoStep11b
		if (move == excludedMove) { continue; }	// ムーブが一致していれば、次のループへ☆


		bool isContinue = false;


		this->explorePlain_10i400j120k_resetScore(
			isContinue,
			pos,
			move,
			checkInfo,
			moveCount,
			&pSplitedNode);
		if (isContinue) { continue; }


		this->explorePlain_10i400j140k_resetState(
			extension,
			captureOrPawnPromotion,
			move,
			givesCheck,
			checkInfo,
			pos,
			dangerous);


		this->explorerPlain_10i400j160k_recursiveSearchA(
			ourCarriage,
			givesCheck,
			pos,
			move,
			extension,
			singularExtensionNode,
			ttMove,
			ttScore,
			checkInfo,
			depth,
			&pFlashlight,
			score,
			cutNode,
			beta,
			newDepth);


		// 無駄枝狩り☆（＾▽＾）非PVだけ行う☆！
		this->ExplorerPlainStep13a_FutilityPruning(
			isContinue,
			ourCarriage,
			captureOrPawnPromotion,
			inCheck,
			dangerous,
			bestScore,
			move,
			ttMove,
			depth,
			moveCount,
			threatMove,
			pos,
			&pSplitedNode,
			newDepth,
			&pFlashlight,
			beta);
		if (isContinue) { continue; }


		this->explorePlain_10i400j180k_isContinue(
			isContinue,
			pos,
			move,
			checkInfo,
			moveCount);
		if (isContinue) { continue; }


		this->explorePlain_10i400j180k_updateCurrentMove(
			isContinue,
			ourCarriage,
			captureOrPawnPromotion,
			inCheck,
			dangerous,
			bestScore,
			move,
			ttMove,
			depth,
			moveCount,
			threatMove,
			pos,
			&pSplitedNode,
			newDepth,
			&pFlashlight,
			beta,
			checkInfo,
			isPVMove,
			playedMoveCount,
			movesSearched);
		if (isContinue) { continue; }


		this->explorerPlain_10i400j200k_updateMoveSearched(
			captureOrPawnPromotion,
			playedMoveCount,
			movesSearched,
			move);


		this->explorePlain_10i500j100k_doMove(
			pos,
			move,
			st,
			checkInfo,
			givesCheck,
			&pFlashlight);


		this->explorePlain_10i500j500k_recursiveSearch(
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
			doFullDepthSearch);


		this->explorePlain_10i600j120k_getScoreNonPV(
			ourCarriage,
			doFullDepthSearch,
			score,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight,
			alpha,
			cutNode);


		this->explorerPlain_10i600j160k_undoMove(
			pos,
			move);


		assert(-ScoreInfinite < score && score < ScoreInfinite);


		if (ourCarriage.m_signals.m_stop || pHandleMonkey->IsUselessNode()) { return score; }


		this->explorerPlain_10i700j115k_bestMovePlyChanges(
			ourCarriage,
			move,
			isPVMove,
			alpha,
			score,
			pos);


		bool isBreak = false;
		this->explorePlain_10i700j120k_getBestUpdateAlpha(
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


		this->explorePlain_10i700j140k_forkNewMonkey(
			isBreak,
			ourCarriage,
			depth,
			&pHandleMonkey,
			bestScore,
			beta,
			pos,
			&pFlashlight,
			alpha,
			bestMove,
			threatMove,
			moveCount,
			nextmoveEvent,
			cutNode);
		if (isBreak) { break; }
	}


	if (this->isReturnBeforeLastProcess_10i800j100k()) { return bestScore; }


	// あれば、ここで帰り際の処理（＾～＾）
	this->explorePlain_10i800j200k_backwardProcess(
		moveCount,
		excludedMove,
		ourCarriage,
		alpha,
		&pFlashlight,
		bestScore,
		playedMoveCount,
		beta,
		posKey,
		depth,
		bestMove,
		inCheck,
		pos,
		movesSearched);


	return bestScore;
}
