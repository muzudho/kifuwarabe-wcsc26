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
#include "../../header/n887_nodeKind/n887_100_adventurePlainNodekindRoot.hpp"
#include "../../header/n887_nodeKind/n887_500_adventurePlainNodekindPrograms.hpp"


using namespace std;
extern const InFrontMaskBb g_inFrontMaskBb;
extern AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[];
//extern RepetitionTypeModels g_repetitionTypes;
AdventureNodekindRoot g_NODEKIND_ROOT;


/// <summary>
/// 平地を探索だ
/// </summary>
/// <param name="ourCarriage"></param>
/// <param name="pos"></param>
/// <param name="pFlashlight"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <param name="depth"></param>
/// <param name="cutNode"></param>
/// <returns></returns>
ScoreIndex AdventureNodekindRoot::explorePlain_n10(
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight,//サーチスタック
	ScoreIndex alpha,
	ScoreIndex beta,
	const Depth depth,
	const bool cutNode) const
{

	assert(-ScoreInfinite <= alpha && alpha < beta && beta <= ScoreInfinite);
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

	// 対応付く猿（探索スレッド）
	Monkey* pHandleMonkey = pos.GetHandleMonkey();
	moveCount
		= playedMoveCount
			= 0;
	inCheck = pos.InCheck();	// 王手されているか（＾～＾）？

	//bool isGotoSplitPointStart = false;

	// 指し手をクリアーする（＾～＾）？
	this->explorePlain_n80_setMoveNone(
		bestScore,
		&pFlashlight,
		threatMove,
		bestMove);

	// ［本筋ノードでの最大手数］という情報を更新（＾～＾）
	this->explorePlain_n90_updateMaxPly(
		&pHandleMonkey,
		pFlashlight);

	//bool isReturnWithScore = false;
	//ScoreIndex returnScore = ScoreIndex::ScoreNone;

	// ［訪問ノード数］という情報を設定（＾～＾）
	pos.SetNodesVisited(pos.GetNodesVisited() + 1);

	// トランスポジション・テーブルのスコアを取得した（＾～＾）？
	this->explorePlain_n100_getTtScore(
		excludedMove,
		&pFlashlight,
		posKey,
		pos,
		&pTtEntry,	//セットされる☆
		ourCarriage,
		ttScore);	//セットされる☆

	// なんか ttMove を取得した（＾～＾）？
	this->explorePlain_n110_getTtMove(
		ttMove,
		ourCarriage,
		pTtEntry,
		pos);
	// ttScore と ttMove でデリシャス・バナナ（＾～＾）！

	// step5
	bool isGotoIidStart = false;//NonPVのとき使う☆

	// なんか評価した（＾～＾）？
	this->explorePlain_n120_eval(
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
	/*
	if (isGotoIidStart) {
		goto iid_start;
	}
	*/


	// 内側の反復深化探索☆？（＾ｑ＾）
//iid_start:
	// step10

	// なんか再帰的に探索してる（＾～＾）
	this->explorePlain_n130_internalIterativeDeepening(
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
	NextmoveEvent nextMoveEvent(
		pos,
		ttMove,
		depth,
		ourCarriage.m_history,
		pFlashlight,
		this->getBeta_n140(beta)//PVノードか、そうでないかで初期値を変えるぜ☆（＾ｑ＾）
		);

	// 王手情報（＾～＾）？
	const CheckInfo checkInfo(pos);

	// なんかセットしてる（＾～＾）
	this->explorePlain_n150_beforeLoop_splitPointStart(
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
			move = this->getNextMove_n160(nextMoveEvent)
			).IsNone()
		) {

		// DoStep11b
		if (move == excludedMove) { continue; }	// ムーブが一致していれば、次のループへ☆

		bool isContinue = false;

		this->explorePlain_n180_loopHeader(
			isContinue,
			pos,
			move,
			checkInfo,
			moveCount,
			&pSplitedNode
			);
		if (isContinue) { continue; }

		this->explorePlain_n200_loopHeader(
			isContinue,
			ourCarriage,
			move
			);
		if (isContinue) { continue; }

		this->explorePlain_n220_loopHeader(
			ourCarriage,
			moveCount
			);

		this->explorePlain_n240_loopHeader(
			extension,
			captureOrPawnPromotion,
			move,
			givesCheck,
			checkInfo,
			pos,
			dangerous);


		#ifndef SHRINK_EXPLORE_PLAIN_260_RECURSIVE_SEARCH
			// なんか分からんが再帰探索（＾～＾）
			this->explorePlain_n260_recursiveSearch(
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
		#endif // !SHRINK_EXPLORE_PLAIN_260_RECURSIVE_SEARCH


		// 本筋かどうか判定するぜ（＾～＾）
		isPVMove = this->explorePlain_n280_isPvMove(moveCount);


		// 現在の指し手を覚えた（＾～＾）
		this->explorePlain_n300_setMove(
			move,
			&pFlashlight);
		if (isContinue) { continue; }


		// 探索した変化を覚えてる（＾～＾）？
		this->explorePlain_n320_memoryVariationMove(
			captureOrPawnPromotion,
			playedMoveCount,
			movesSearched,
			move);


		// １手指すぜ（＾～＾）
		this->explorerPlain_n340_doMove(
			pos,
			move,
			st,
			checkInfo,
			givesCheck,
			&pFlashlight);


		#ifndef SHRINK_EXPLORE_PLAIN_360_RECURSIVE_SEARCH
			// なんか分からんが再帰探索（＾～＾）
			this->explorePlain_n360_recursiveSearch(
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
		#endif


		#ifndef SHRINK_EXPLORE_PLAIN_NON_PV_RECURSIVE_SEARCH
			// NonPV扱いで再帰するみたいなんだがなんだこれだぜ☆（＾～＾）？
			this->explorePlain_n380_nonPVRecursiveSearch(
				ourCarriage,
				doFullDepthSearch,
				score,
				newDepth,
				givesCheck,
				pos,
				&pFlashlight,
				alpha,
				cutNode);
		#endif


		#ifndef SHRINK_EXPLORE_PLAIN_LARGE_BETA_RECURSIVE_SEARCH
			// 大きなβ値のときの深掘りか（＾～＾）？
			this->explorePlain_n400_betaLargeRecursiveSearch(
				ourCarriage,
				isPVMove,
				alpha,
				score,
				beta,
				newDepth,
				givesCheck,
				pos,
				&pFlashlight);
		#endif // !SHRINK_EXPLORE_PLAIN_LARGE_BETA_RECURSIVE_SEARCH


		this->explorePlain_n420_undoMove(
			pos,
			move);


		assert(-ScoreInfinite < score && score < ScoreInfinite);


		// ［反復深化探索］を止める信号が立っていたり、カットオフされた使われていないノードのとき
		if (ourCarriage.m_signals.m_isIterationDeepingStop || pHandleMonkey->IsUselessSplitedNode()) { return score; }


		this->explorePlain_n440_findRootNode(
			ourCarriage,
			move,
			isPVMove,
			alpha,
			score,
			pos);


		bool isBreak = false;


		// α値更新
		this->explorePlain_n460_updateAlpha(
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


		#ifndef SHRINK_EXPLORE_PLAIN_FORK_NEW_MONKEY
			// さらに枝に別の猿を走らせる。
			this->explorePlain_n480_forkNewMonkey(
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
				nextMoveEvent,
				cutNode);
			if (isBreak) { break; }
		#endif


	}

	if (this->getReturn_beforeN500()) { return bestScore; }

	// step20
	this->explorePlain_n500(
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
		movesSearched
		);

	return bestScore;
}
