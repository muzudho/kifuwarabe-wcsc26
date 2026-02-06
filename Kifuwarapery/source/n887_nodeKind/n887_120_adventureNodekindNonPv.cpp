#include <iostream>
#include <algorithm>
#include "../../header/n119_500_sweetnes/n119_200_PieceSweetness.hpp"
#include "../../header/n160_board___/n160_106_inFrontMaskBb.hpp"
#include "../../header/n160_board___/n160_220_queenAttackBb.hpp"
#include "../../header/n160_board___/n160_230_setMaskBb.hpp"
#include "../../header/n220_position/n220_100_repetitionType.hpp"
#include "../../header/n220_position/n220_640_utilAttack.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n220_position/n220_665_utilMoveStack.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n223_move____/n223_300_DeliciousBanana.hpp"
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
Sweetness AdventureNodekindNonPv::explorePlain_10i(
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight,//サーチスタック
	Sweetness alpha,
	Sweetness beta,
	const Depth depth,
	const bool cutNode) const
{


	// ----------------------------------------
	// １．　ようこそ　開始
	// ----------------------------------------


	assert(-SweetnessInfinite <= alpha && alpha < beta && beta <= SweetnessInfinite);
	this->explorePlain_10i1010j_assertAtFirst(
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
	Sweetness bestSweetness;
	Sweetness sweetness;
	Sweetness eval;
	bool inCheck;
	bool givesCheck;
	bool isPVMove;	// 本筋の指し手かどうかかなあ（＾～＾）？
	bool singularExtensionNode;
	bool captureOrPawnPromotion;
	bool dangerous;
	bool doFullDepthSearch;
	int moveCount;
	int playedMoveCount;
	Move ttMove;
	Sweetness ttSweetness;
	std::unique_ptr<Move> pTtMove;  // 宣言だけ（デフォルトnull）


	// step1
	// initialize node
	Monkie* pHandleMonkey = pos.getHandleMonkey();	// 局面に対応する猿
	moveCount = playedMoveCount = 0;
	inCheck = pos.inCheck();

	bool isGotoSplitPointStart = false;


	this->explorePlain_10i1030j_clearMove(
		bestSweetness,
		&pFlashlight,
		threatMove,
		bestMove);


	// step2: 千日手による探索打切りの判断
	auto p = this->explorePlain_10i1080j_isStopByRepetetion(
		//isReturnWithSweetness,
		//returnSweetness,
		pos,
		ourCarriage,
		&pFlashlight);


	bool isReturnWithSweetness = p.first;
	Sweetness returnSweetness = p.second;
	if (isReturnWithSweetness) { return returnSweetness; }


	this->explorePlain_10i1090j_checkAlpha(
		isReturnWithSweetness,
		returnSweetness,
		&pFlashlight,
		alpha,
		beta);
	if (isReturnWithSweetness) { return returnSweetness; }


	pos.setNodesSearched(pos.getNodesSearched() + 1);


	ttSweetness = this->explorePlain_10i1100j_getTtSweetness(
		excludedMove,
		&pFlashlight,
		posKey,
		pos,
		&pTtEntry,//セットされる☆
		ourCarriage);
	pTtMove = this->explorePlain_10i1110j_getTtMove(
		ourCarriage,
		pTtEntry,
		pos);
	ttMove = *pTtMove.get();	// コピー作成


	this->explorePlain_10i1180j_killerMove(
		ttMove,
		ttSweetness,
		isReturnWithSweetness,
		returnSweetness,
		ourCarriage,
		pTtEntry,
		depth,
		beta,
		&pFlashlight);
	if (isReturnWithSweetness) { return returnSweetness; }


	// 一手詰めならそのバナナ採用☆（＾～＾）
	this->explorePlain_10i1190j_returnIfMateMoveIn1Ply(
		isReturnWithSweetness,
		bestMove,
		returnSweetness,
		ourCarriage,
		inCheck,
		move,
		pos,
		&pFlashlight,
		bestSweetness,
		posKey,
		depth);
	if (isReturnWithSweetness) { return returnSweetness; }


	bool isGotoIidStart = false;//NonPVのとき使う☆
	this->explorePlain_10i1200j_evelSweetness(
		isGotoIidStart,
		ourCarriage,
		eval,
		&pFlashlight,
		pos,
		inCheck,
		pTtEntry,
		ttSweetness,
		posKey,
		move);
	if (isGotoIidStart) { goto iid_start; }


	this->explorePlain_10i1260j_nonPV(
		isReturnWithSweetness,
		returnSweetness,
		ourCarriage,
		depth,
		eval,
		beta,
		ttMove,
		pos,
		&pFlashlight);
	if (isReturnWithSweetness) { return returnSweetness; }


	this->explorePlain_10i1270j_nonPV(
		isReturnWithSweetness,
		returnSweetness,
		&pFlashlight,
		depth,
		beta,
		eval);
	if (isReturnWithSweetness) { return returnSweetness; }


	this->explorePlain_10i1280j_nonPV(
		isReturnWithSweetness,
		returnSweetness,
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
	if (isReturnWithSweetness) { return returnSweetness; }


	this->explorePlain_10i1290j_nonPV(
		isReturnWithSweetness,
		ourCarriage,
		depth,
		&pFlashlight,
		beta,
		move,
		pos,
		ttMove,
		st,
		sweetness,
		cutNode);
	if (isReturnWithSweetness) { return sweetness; }


	// 内側の反復深化探索☆？（＾ｑ＾）
iid_start:
	this->explorerPlain_10i1300j_internalIterativeDeepening(
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
		this->getBeta_10i1310j(beta)//PVノードか、そうでないかで初期値を変えるぜ☆（＾ｑ＾）
		);
	const CheckInfo checkInfo(pos);


	this->explorePlain_10i1320j_beforeLoopSplitPointStart(
		ttMove,
		depth,
		sweetness,
		bestSweetness,
		singularExtensionNode,
		excludedMove,
		pTtEntry//pv,nonPv の２つで、nullptrはダメ☆
		);


	// ----------------------------------------
	// １．　ようこそ　終了
	// ----------------------------------------


	// Loop through moves
	while (
		!(
			// スプリット・ポイントかどうかで、取ってくる指し手が変わる☆
			move = this->getNextMove_10i2010j(nextmoveEvent)
			).IsNone()
		) {


		// ----------------------------------------
		// ２．　いってきます　開始
		// ----------------------------------------


		if (move == excludedMove) { continue; }	// ムーブが一致していれば、次のループへ☆


		bool isContinue = false;


		this->explorePlain_10i2020j_resetSweetness(
			isContinue,
			pos,
			move,
			checkInfo,
			moveCount,
			&pSplitedNode);
		if (isContinue) { continue; }


		this->explorePlain_10i2050j_resetState(
			extension,
			captureOrPawnPromotion,
			move,
			givesCheck,
			checkInfo,
			pos,
			dangerous);


		this->explorerPlain_10i2060j_recursiveSearchA(
			ourCarriage,
			givesCheck,
			pos,
			move,
			extension,
			singularExtensionNode,
			ttMove,
			ttSweetness,
			checkInfo,
			depth,
			&pFlashlight,
			sweetness,
			cutNode,
			beta,
			newDepth);


		// 無駄枝狩り☆（＾▽＾）非PVだけ行う☆！
		this->explorePlain_10i2070j_futilityPruning(
			isContinue,
			ourCarriage,
			captureOrPawnPromotion,
			inCheck,
			dangerous,
			bestSweetness,
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


		this->explorePlain_10i2080_isContinue(
			isContinue,
			pos,
			move,
			checkInfo,
			moveCount);
		if (isContinue) { continue; }


		this->explorePlain_10i2090j_updateCurrentMove(
			isContinue,
			ourCarriage,
			captureOrPawnPromotion,
			inCheck,
			dangerous,
			bestSweetness,
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


		this->explorerPlain_10i2100j_updateMoveSearched(
			captureOrPawnPromotion,
			playedMoveCount,
			movesSearched,
			move);


		// 一手指す


		this->explorePlain_10i2110j_doMove(
			pos,
			move,
			st,
			checkInfo,
			givesCheck,
			&pFlashlight);


		// 一手指した後


		// ----------------------------------------
		// ２．　いってきます　終了
		// ----------------------------------------


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
			sweetness,
			pos,
			doFullDepthSearch);


		// ----------------------------------------
		// ３．　ただいま　開始
		// ----------------------------------------


		this->explorePlain_10i600j120k_getSweetnessNonPV(
			ourCarriage,
			doFullDepthSearch,
			sweetness,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight,
			alpha,
			cutNode);


		// 一手戻す


		this->explorerPlain_10i600j160k_undoMove(
			pos,
			move);


		// 一手戻した後


		assert(-SweetnessInfinite < sweetness && sweetness < SweetnessInfinite);


		if (ourCarriage.m_signals.m_stop || pHandleMonkey->IsUselessNode()) { return sweetness; }


		this->explorerPlain_10i700j115k_bestMovePlyChanges(
			ourCarriage,
			move,
			isPVMove,
			alpha,
			sweetness,
			pos);


		bool isBreak = false;
		this->explorePlain_10i700j120k_getBestUpdateAlpha(
			isBreak,
			ourCarriage,
			move,
			isPVMove,
			alpha,
			sweetness,
			pos,
			bestSweetness,
			&pSplitedNode,
			bestMove,
			beta);
		if (isBreak) { break; }


		this->explorePlain_10i700j140k_forkNewMonkey(
			isBreak,
			ourCarriage,
			depth,
			&pHandleMonkey,
			bestSweetness,
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


		// ----------------------------------------
		// ３．　ただいま　終了
		// ----------------------------------------


	}


	// ----------------------------------------
	// ４．　さよなら　開始
	// ----------------------------------------


	if (this->isReturnBeforeLastProcess_10i800j100k()) { return bestSweetness; }


	// あれば、ここで帰り際の処理（＾～＾）
	this->explorePlain_10i800j200k_backwardProcess(
		moveCount,
		excludedMove,
		ourCarriage,
		alpha,
		&pFlashlight,
		bestSweetness,
		playedMoveCount,
		beta,
		posKey,
		depth,
		bestMove,
		inCheck,
		pos,
		movesSearched);


	// ----------------------------------------
	// ４．　さよなら　終了
	// ----------------------------------------


	return bestSweetness;
}
