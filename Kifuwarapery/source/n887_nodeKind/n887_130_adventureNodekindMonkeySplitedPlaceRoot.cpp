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
#include "../../src/game_engine_layer/game_engine_storage.hpp"
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


AdventureNodekindMonkeySplitedPlaceRoot g_NODEKIND_MONKEYSPLITEDPLACE_ROOT;


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
Sweetness AdventureNodekindMonkeySplitedPlaceRoot::explorePlain_10i(
	GameEngineStorageOurCarriage& ourCarriage,
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
	// [NOTE_1010]: αは　β－１　なのかだぜ（＾～＾）？
	this->explorePlain_10i1010j_alphaIsBetaMinusOne(
		alpha,
		beta);
	assert(Depth0 < depth);

	// 途中で goto を使用している為、先に全部の変数を定義しておいた方が安全。
	Move movesSearched[64];
	StateInfo st;
	const TTEntry* pTtEntry = nullptr;//(^q^)トランスポジション・テーブル・エントリー☆？
	MonkeySplitedPlace* pMonkeySplitedPlace = nullptr;//(^q^)
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
	bool willFullDepthSearch;
	int moveCount;
	int playedMoveCount;
	Move ttMove;
	Sweetness ttSweetness;
	std::unique_ptr<Move> pTtMove;  // 宣言だけ（デフォルトnull）

	// initialize node
	Monkie* pHandleMonkey = pos.getHandleMonkey();	// 局面に対応する猿
	moveCount = playedMoveCount = 0;
	inCheck = pos.inCheck();


	bool isGotoSplitPointStart = false;

	// [NOTE_1020]: ノードの初期化する
	this->explorePlain_10i1020j_initializeNode(
		ttMove,
		ttSweetness,
		isGotoSplitPointStart,
		moveCount,
		playedMoveCount,
		inCheck,
		pos,
		&pMonkeySplitedPlace,
		&pFlashlight,
		bestMove,
		threatMove,
		bestSweetness,
		excludedMove);
	if (isGotoSplitPointStart) { goto split_point_start; }

	// [NOTE_1030]: 指し手の初期化する
	this->explorePlain_10i1030j_clearMove(
		bestSweetness,
		&pFlashlight,
		threatMove,
		bestMove);

	// [NOTE_1040]: （必要なら）最大Plyを更新
	this->explorePlain_10i1040j_updateMaxPly(
		&pHandleMonkey,
		pFlashlight);


	bool isReturnWithSweetness = false;
	Sweetness returnSweetness = Sweetness::SweetnessNone;

	pos.setNodesSearched(pos.getNodesSearched() + 1);

	// トランスポジション・テーブルの指し手の［評価値］取得
	ttSweetness = this->explorePlain_10i1100j_getTtSweetness(
		excludedMove,
		&pFlashlight,
		posKey,
		pos,
		&pTtEntry,//セットされる☆
		ourCarriage);
	// トランスポジション・テーブルの指し手の［指し手］取得
	pTtMove = this->explorePlain_10i1110j_getTtMove(
		ourCarriage,
		pTtEntry,
		pos);
	ttMove = *pTtMove.get();	// コピー作成

	// キラームーブは調べない

	// なんか［評価値］をどうにかしてる
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
	/*
	if (isGotoIidStart) {
		goto iid_start;
	}
	*/


//iid_start:
	// 内側の反復深化探索☆？（＾ｑ＾）
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


split_point_start:
	NextmoveEvent nextmoveEvent(
		pos,
		ttMove,
		depth,
		ourCarriage.m_history,
		pFlashlight,
		this->getBeta_10i1310j(beta)//PVノードか、そうでないかで初期値を変えるぜ☆（＾ｑ＾）
		);

	// 王手の情報か（＾～＾）？
	const CheckInfo checkInfo(pos);

	// ［ようこその終了地点］（＾～＾）
	this->explorePlain_10i1320j_atWelcomeEnd(
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


	while (
		!(
			// スプリット・ポイントかどうかで、取ってくる指し手が変わる☆
			move = this->getNextMove_10i2010j(nextmoveEvent)
			).IsNone()
	)
	{


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
			&pMonkeySplitedPlace);
		if (isContinue) { continue; }


		this->explorePlain_10i2030j_isRootMoveEnd(
			isContinue,
			ourCarriage,
			move);
		if (isContinue) { continue; }


		this->explorerPlain_10i2040j_displayInfo(
			ourCarriage,
			moveCount);


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
			&pMonkeySplitedPlace,
			newDepth,
			&pFlashlight,
			beta,
			checkInfo,
			isPVMove,
			playedMoveCount,
			movesSearched);
		if (isContinue) { continue; }


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


		this->explorePlain_10i2999j_recursiveSearch(
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
			&pMonkeySplitedPlace,
			sweetness,
			pos,
			willFullDepthSearch);


		// ----------------------------------------
		// ３．　ただいま　開始
		// ----------------------------------------


		this->explorePlain_10i3010j_updateAlpha(
			willFullDepthSearch,
			alpha,
			&pMonkeySplitedPlace);

		// もし全深さ探索するんだったら、［大雑把な性格の猿］が評価値を取得するぜ（＾ｑ＾）
		this->explorePlain_10i3020j_getSweetnessByEasyGoingMonkeyIfWillFullDepthSearch(
			ourCarriage,
			willFullDepthSearch,
			sweetness,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight,
			alpha,
			cutNode);

		this->explorerPlain_10i3030j_getSweetnessIfMeticulous(
			ourCarriage,
			isPVMove,
			alpha,
			sweetness,
			beta,
			newDepth,
			givesCheck,
			pos,
			&pFlashlight);


		// 一手戻す


		this->explorerPlain_10i3040j_undoMove(
			pos,
			move);


		// 一手戻した後


		assert(-SweetnessInfinite < sweetness && sweetness < SweetnessInfinite);


		this->explorePlain_10i3050j_getAlpha(
			&pMonkeySplitedPlace,
			bestSweetness,
			alpha);


		if (ourCarriage.m_signals.m_stop || pHandleMonkey->IsUselessNode()) { return sweetness; }


		this->explorerPlain_10i3060j_bestMovePlyChanges(
			ourCarriage,
			move,
			isPVMove,
			alpha,
			sweetness,
			pos);


		bool isBreak = false;
		this->explorePlain_10i3070j_getBestUpdateAlpha(
			isBreak,
			ourCarriage,
			move,
			isPVMove,
			alpha,
			sweetness,
			pos,
			bestSweetness,
			&pMonkeySplitedPlace,
			bestMove,
			beta);


		if (isBreak) { break; }


		// ----------------------------------------
		// ３．　ただいま　終了
		// ----------------------------------------


	}


	// ----------------------------------------
	// ４．　さよなら　開始
	// ----------------------------------------


	if (this->isReturnBeforeLastProcess_10i4010j()) { return bestSweetness; }


	// あれば、ここで帰り際の処理（＾～＾）


	// ----------------------------------------
	// ４．　さよなら　終了
	// ----------------------------------------


	return bestSweetness;
}
