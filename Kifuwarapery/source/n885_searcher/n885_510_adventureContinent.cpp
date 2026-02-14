#include <iostream>
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
#include "../../header/n350_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n350_pieceTyp/n350_500_ptPrograms.hpp"
#include "../../header/n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../../header/n520_evaluate/n520_700_evaluation09.hpp"
#include "../../header/n560_timeMgr_/n560_500_timeManager.hpp"
#include "../../header/n600_book____/n600_500_book.hpp"
#include "../../header/n640_searcher/n640_040_nodeKind.hpp"
#include "../../header/n640_searcher/n640_440_splitedNode.hpp"
#include "../../header/n640_searcher/n640_500_reductions.hpp"
#include "../../header/n640_searcher/n640_510_futilityMargins.hpp"
#include "../../header/n640_searcher/n640_520_futilityMoveCounts.hpp"
#include "../../src/lib_gui/engine_option_collection.hpp"
#include "../../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../../header/n800_learn___/n800_100_stopwatch.hpp"
#include "../../header/n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"
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
#include "../../header/n887_nodeKind/n887_500_adventurePlainNodekindPrograms.hpp"//FIXME:


using namespace std;
extern const InFrontMaskBb g_inFrontMaskBb;
extern AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[];
//extern RepetitionTypeModels g_repetitionTypes;


/// <summary>
///		<pre>
/// 思考するぜ☆（＾ｑ＾）大陸を馬車で大冒険する気分（＾▽＾）
/// 
///		- `Captain::StartWorkerThread` などから呼び出されるぜ（＾～＾）
///		</pre>
/// </summary>
/// <param name="captainsRucksack">キャプテンの持っているＳｅａｒｃｈｅｒ☆</param>
void AdventureContinent::ExploreContinent(
	MuzGameEngineStorageModel& captainsRucksack)
{
	Position& pos = captainsRucksack.m_rootPosition;

	bool isMoveTime0Clear = false;
	captainsRucksack.m_timeMgr.Initialize(
		isMoveTime0Clear,
		captainsRucksack.m_limits,
		pos.GetGamePly(),
		pos.GetTurn(),
		&captainsRucksack
		);
	if (isMoveTime0Clear) {
		captainsRucksack.m_limits.ZeroClearMoveTime();
	}
	SYNCCOUT << "info string limits move time = " << captainsRucksack.m_limits.GetMoveTime() << SYNCENDL;//旧表示はなかった☆


	//────────────────────────────────────────────────────────────────────────────────
	// 入玉勝ちかを調べるぜ☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
#if !defined(LEARN)
	if (AdventureContinent::IsNyugyokuWin(pos)) {
		//────────────────────────────────────────────────────────────────────────────────
		// 探索☆？（＾ｑ＾）
		//────────────────────────────────────────────────────────────────────────────────
		AdventureSwampNyugyoku::ExploreSwamp(captainsRucksack,pos);
		return;
	}
#endif

	//────────────────────────────────────────────────────────────────────────────────
	// 入玉勝ちじゃなかったぜ☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	static Book book;
	std::uniform_int_distribution<int> dist(
		captainsRucksack.m_engineOptionCollection.m_map["Min_Book_Ply"], captainsRucksack.m_engineOptionCollection.m_map["Max_Book_Ply"]);

	const Ply book_ply = dist(g_randomTimeSeed);

	pos.setNodesSearched(0);

#if defined LEARN
	captainsRucksack.m_ownerHerosPub[0]->m_searching = true;
#else
	captainsRucksack.m_tt.setSize(captainsRucksack.m_engineOptionCollection.m_map["USI_Hash"]); // operator int() 呼び出し。

	SYNCCOUT << "info string book_ply " << book_ply << SYNCENDL;
	if (
		// 定跡が使える手数のとき☆（＾ｑ＾）？
		captainsRucksack.m_engineOptionCollection.m_map["OwnBook"] &&
		pos.GetGamePly() <= book_ply
	) {
		const DeliciousBanana bookBanana = book.GetProbe(
			pos, captainsRucksack.m_engineOptionCollection.m_map["Book_File"], captainsRucksack.m_engineOptionCollection.m_map["Best_Book_Move"]);

		if (
			!bookBanana.m_move.IsNone()
			&&
			std::find(
				captainsRucksack.m_rootMoves.begin(),
				captainsRucksack.m_rootMoves.end(),
				bookBanana.m_move
			) != captainsRucksack.m_rootMoves.end()
		){
			std::swap(captainsRucksack.m_rootMoves[0], *std::find(captainsRucksack.m_rootMoves.begin(),
				captainsRucksack.m_rootMoves.end(),
				bookBanana.m_move));
			SYNCCOUT << "info"
				<< " score " << captainsRucksack.sweetnessToUSI(bookBanana.m_sweetness)
				<< " pv " << bookBanana.m_move.ToUSI()
				<< SYNCENDL;

			goto finalize;
		}
	}

	// 全スレッドの初期化か何か☆？
	captainsRucksack.m_pub.WakeUp(&captainsRucksack);

	// 下級戦士の寿命（ミリ秒）を設定するぜ☆
	captainsRucksack.m_pub.GetCurrSubordinate()->m_lifetimeMilliseconds =
		(
			captainsRucksack.m_limits.IsBrandnewTimeMgr() ? // 反復深化をしたい☆？（＾ｑ＾）
			// する場合
			std::min(100,
				std::max(
					captainsRucksack.m_timeMgr.GetSubordinateLifeTime(),
					captainsRucksack.TimerResolution
				))
			:
			// できない場合☆
			captainsRucksack.m_limits.m_visitedNodesNum ?
				2 * captainsRucksack.TimerResolution :
				100
			);

	captainsRucksack.m_pub.GetCurrSubordinate()->NotifyOne();

#if defined INANIWA_SHIFT
	detectInaniwa(GetPos);
#endif
#if defined BISHOP_IN_DANGER
	detectBishopInDanger(GetPos);
#endif
#endif


	//────────────────────────────────────────────────────────────────────────────────
	// 反復深化探索を始めるぜ☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────

	AdventureMountainIterativeDeepeningLoop::ExploreMountain(captainsRucksack, pos);//ExecuteIterativeDeepeningLoop(pos);

#if defined LEARN
#else
	captainsRucksack.m_pub.GetCurrSubordinate()->m_lifetimeMilliseconds = 0; // timer を止める。
	captainsRucksack.m_pub.SleepMonkies();

finalize:

	SYNCCOUT << "info nodes " << pos.getNodesSearched()
		<< " time " << captainsRucksack.m_stopwatch.GetElapsed() << SYNCENDL;

	if (!captainsRucksack.m_signals.m_stop && (captainsRucksack.m_limits.m_canPonder || captainsRucksack.m_limits.m_isInfinite)) {
		captainsRucksack.m_signals.m_stopOnPonderHit = true;
		pos.getHandleMonkey()->WaitFor(captainsRucksack.m_signals.m_stop);
	}

	if (captainsRucksack.m_rootMoves[0].m_pv_[0].IsNone()) {
		SYNCCOUT << "bestmove resign" << SYNCENDL;
	}
	else {
		SYNCCOUT << "bestmove " << captainsRucksack.m_rootMoves[0].m_pv_[0].ToUSI()
			<< " ponder " << captainsRucksack.m_rootMoves[0].m_pv_[1].ToUSI()
			<< SYNCENDL;
	}
#endif
}


/// <summary>
/// 入玉勝ちかどうかを判定 
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
bool AdventureContinent::IsNyugyokuWin(const Position& pos) {
	// CSA ルールでは、一 から 六 の条件を全て満たすとき、入玉勝ち宣言が出来る。

	// 一 宣言側の手番である。

	// この関数を呼び出すのは自分の手番のみとする。ponder では呼び出さない。

	const Color us = pos.GetTurn();

	// 敵陣のマスク
	const Bitboard opponentsField = (us == Black ? g_inFrontMaskBb.GetInFrontMask(Black, Rank6) : g_inFrontMaskBb.GetInFrontMask(White, Rank4));

	// 二 宣言側の玉が敵陣三段目以内に入っている。
	if (!pos.GetBbOf20(N08_King, us).AndIsNot0(opponentsField))
	{
		return false;
	}

	// 三 宣言側が、大駒5点小駒1点で計算して
	//     先手の場合28点以上の持点がある。
	//     後手の場合27点以上の持点がある。
	//     点数の対象となるのは、宣言側の持駒と敵陣三段目以内に存在する玉を除く宣言側の駒のみである。
	const Bitboard bigBB = pos.GetBbOf(N06_Rook, N14_Dragon, N05_Bishop, N13_Horse) & opponentsField & pos.GetBbOf10(us);

	const Bitboard smallBB = (pos.GetBbOf(N01_Pawn, N02_Lance, N03_Knight, N04_Silver) |
		pos.GetGoldsBB()) & opponentsField & pos.GetBbOf10(us);

	const Hand hand = pos.GetHand(us);

	const int val = (bigBB.PopCount() + hand.NumOf<HRook>() + hand.NumOf<HBishop>()) * 5
		+ smallBB.PopCount()
		+ hand.NumOf<HPawn>() + hand.NumOf<HLance>() + hand.NumOf<HKnight>()
		+ hand.NumOf<HSilver>() + hand.NumOf<HGold>();

#if defined LAW_24
	if (val < 31)
	{
		return false;
	}
#else
	if (val < (us == Black ? 28 : 27))
	{
		return false;
	}
#endif

	// 四 宣言側の敵陣三段目以内の駒は、玉を除いて10枚以上存在する。

	// 玉は敵陣にいるので、自駒が敵陣に11枚以上あればよい。
	if ((pos.GetBbOf10(us) & opponentsField).PopCount() < 11)
	{
		return false;
	}

	// 五 宣言側の玉に王手がかかっていない。
	if (pos.inCheck())
	{
		return false;
	}

	// 六 宣言側の持ち時間が残っている。

	// 持ち時間が無ければ既に負けていて　ここにはこないので、何もチェックしない（＾ｑ＾）

	return true;
}
