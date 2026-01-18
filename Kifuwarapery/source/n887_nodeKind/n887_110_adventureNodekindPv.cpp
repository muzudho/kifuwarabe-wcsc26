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
#include "../../header/n887_nodeKind/n887_110_adventurePlainNodekindPv.hpp"
#include "../../header/n887_nodeKind/n887_500_adventurePlainNodekindPrograms.hpp"


using namespace std;
extern const InFrontMaskBb g_inFrontMaskBb;
extern AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[];
//extern RepetitionTypeModels g_repetitionTypes;
AdventureNodekindPv g_NODEKIND_PV;


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
ScoreNumber AdventureNodekindPv::explorePlain_10a520b500c500d500e500f500g_entry(
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight,//サーチスタック
	ScoreNumber alpha,
	ScoreNumber beta,
	const Depth depth,
	const bool cutNode) const
{


	assert(-ScoreInfinite <= alpha && alpha < beta && beta <= ScoreInfinite);
	this->explorePlain_10a520b500c500d500e500f500g100h800i_assert(
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
	bool isPVMove;
	bool singularExtensionNode;
	bool captureOrPawnPromotion;
	bool dangerous;
	bool doFullDepthSearch;
	int moveCount;
	int playedMoveCount;
	Move bananaTtMove;
	ScoreNumber bananaTtScore;
	//DeliciousBanana ttDeliciousBanana;

	// step1
	// initialize node
	Monkey* pThisThread = pos.getHandleMonkey();
	moveCount = playedMoveCount = 0;
	inCheck = pos.inCheck();

	bool isGotoSplitPointStart = false;


	// ヌル指し手セット


	this->explorePlain_10a520b500c500d500e500f500g200h150i_setMoveNone(
		bestScore,
		&pFlashlight,
		threatMove,
		bestMove);


	this->explorePlain_10a520b500c500d500e500f500g200h200i_updateMaxPly(
		&pThisThread,
		pFlashlight);


	// step2: 千日手による探索打切りの判断
	//		- maxPly を更新するケースもある。
	auto p = this->explorePlain_10a520b500c500d500e500f500g200h250i_isStopByRepetetion(
		//isReturnWithScore,
		//returnScore,
		pos,
		ourCarriage,
		&pFlashlight);


	bool isReturnWithScore = p.first;
	ScoreNumber returnScore = p.second;
	if (isReturnWithScore) { return returnScore; }


	this->explorePlain_10a520b500c500d500e500f500g200h300i_returnWithScore(
		isReturnWithScore,
		returnScore,
		&pFlashlight,
		alpha,
		beta
		);
	if (isReturnWithScore) { return returnScore; }


	pos.setNodesVisited(pos.getNodesVisited() + 1);


	// ttScore と ttMove でデリシャス・バナナ（＾～＾）！
	{
		DeliciousBanana ttDeliciousBanana = this->explorePlain_10a520b500c500d500e500f500g200h405i_getTtDeliciousBanana(
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


	std::tie(isReturnWithScore, returnScore) = this->explorePlain_10a520b500c500d500e500f500g200h450i_returnWithScore(
		&pFlashlight,
		ourCarriage,
		pTtEntry,
		depth,
		bananaTtScore,
		beta,
		bananaTtMove);
	if (isReturnWithScore) { return returnScore; }

	this->explorePlain_10a520b500c500d500e500f500g200h500i_returnWithValue(
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
	this->explorePlain_10a520b500c500d500e500f500g200h550i_evalScore(
		isGotoIidStart,
		ourCarriage,
		eval,
		&pFlashlight,
		pos,
		inCheck,
		pTtEntry,
		bananaTtScore,
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
	this->explorePlain_10a520b500c500d500e500f500g200h800i_internalIterativeDeepening(
		depth,
		bananaTtMove,
		inCheck,
		beta,
		&pFlashlight,
		ourCarriage,
		pos,
		alpha,
		&pTtEntry,//セットされるぜ☆
		posKey
		);


//split_point_start:
	NextmoveEvent nextMoveEvent(
		pos,
		bananaTtMove,
		depth,
		ourCarriage.m_history,
		pFlashlight,
		this->explorerPlain_10a520b500c500d500e500f500g200h850i_getBeta(beta)//PVノードか、そうでないかで初期値を変えるぜ☆（＾ｑ＾）
		);
	
	
	const CheckInfo checkInfo(pos);


	this->explorePlain_10a520b500c500d500e500f500g200h900i_beforeLoopSplitPointStart(
		bananaTtMove,
		depth,
		score,
		bestScore,
		singularExtensionNode,
		excludedMove,
		pTtEntry//pv,nonPv の２つで、nullptrはダメ☆
		);


	// Loop through moves
	while (
		!(
			// スプリット・ポイントかどうかで、取ってくる指し手が変わる☆
			move = this->explorePlain_10a520b500c500d500e500f500g200h950i_getNextMove(nextMoveEvent)
			).IsNone()
		) {


		// 指さずに探索する前


		if (move == excludedMove) { continue; }// ムーブが一致していれば、次のループへ☆


		bool isContinue = false;


		this->explorePlain_10a520b500c500d500e500f500g300h500i_loopHeader(
			isContinue,
			pos,
			move,
			checkInfo,
			moveCount,
			&pSplitedNode);
		if (isContinue) { continue; }


		this->explorePlain_10a520b500c500d500e500f500g300h900i_loopHeader(
			extension,
			captureOrPawnPromotion,
			move,
			givesCheck,
			checkInfo,
			pos,
			dangerous);


		// 指さずに探索処理


		this->explorePlain_10a520b500c500d500e500f500g400h500i_recursiveSearch(
			ourCarriage,
			givesCheck,
			pos,
			move,
			extension,
			singularExtensionNode,
			bananaTtMove,
			bananaTtScore,
			checkInfo,
			depth,
			&pFlashlight,
			score,
			cutNode,
			beta,
			newDepth);

		this->explorePlain_n400n600_continue(
			isContinue,
			pos,
			move,
			checkInfo,
			moveCount);
		if (isContinue) { continue; }


		// 本筋かどうか判定するぜ（＾～＾）
		isPVMove = this->explorePlain_10a520b500c500d500e500f500g400h700i_isPvMove(moveCount);


		this->explorePlain_10a520b500c500d500e500f500g400h800i_setMove(
			move,
			&pFlashlight);
		if (isContinue) { continue; }


		this->explorePlain_10a520b500c500d500e500f500g400h900i_memoryVariationMove(
			captureOrPawnPromotion,
			playedMoveCount,
			movesSearched,
			move);


		// ドゥムーブ処理


		this->explorerPlain_10a520b500c500d500e500f500g500h100i_doMove(
			pos,
			move,
			st,
			checkInfo,
			givesCheck,
			&pFlashlight);


		// ドゥムーブ後処理


		// 探索処理


		this->explorePlain_10a520b500c500d500e500f500g500h600i_nonPVRecursiveSearch(
			ourCarriage,
			doFullDepthSearch,
			score,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight,
			alpha,
			cutNode);


		// 探索後処理


		this->explorePlain_10a520b500c500d500e500f500g600h900i_betaLargeRecursiveSearch(
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


		this->explorePlain_10a520b500c500d500e500f500g700h100i_undoMove(
			pos,
			move);


		// アンドゥ後処理


		assert(-ScoreInfinite < score && score < ScoreInfinite);


		if (ourCarriage.m_signals.m_isIterationDeepingStop || pThisThread->isUselessSplitedNode()) { return score; }


		// アップデートα処理


		bool isBreak = false;
		this->explorePlain_10a520b500c500d500e500f500g700h700i_updateAlpha(
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


		this->explorePlain_10a520b500c500d500e500f500g700h750i_forkNewMonkey(
			isBreak,
			ourCarriage,
			depth,
			&pThisThread,
			bestScore,
			beta,
			pos,
			&pFlashlight,
			alpha,
			bestMove,
			threatMove,
			moveCount,
			nextMoveEvent,
			cutNode);
		if (isBreak) { break; }
	}


	// ループ後処理


	if (this->explorePlain_10a520b500c500d500e500f500g800h400i_isReturn()) { return bestScore; }


	// 木の戻り際で何かあればここで処理（＾～＾）


	this->explorePlain_10a520b500c500d500e500f500g800h500i_workAtReturn(
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
