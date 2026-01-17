#pragma once


#include <string>
#include <sstream>
#include "../n210_score___/n119_090_scoreIndex.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n130_100_boardBb_/n160_130_lanceAttackBb.hpp"
#include "../n130_100_boardBb_/n160_150_rookAttackBb.hpp"
#include "../n130_100_boardBb_/n160_220_queenAttackBb.hpp"
#include "../n130_100_boardBb_/n160_230_setMaskBb.hpp"
#include "../n223_move____/n223_060_stats.hpp"
#include "../n250_pieceTyp/n350_040_ptEvent.hpp"
#include "../n250_pieceTyp/n350_500_ptPrograms.hpp"
#include "../n560_timeMgr_/n560_500_timeManager.hpp"
#include "../n640_searcher/n640_128_signalsType.hpp"
#include "../n640_searcher/n640_450_rootMove.hpp"
#include "../n680_egOption/n680_240_engineOptionsMap.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "../n760_thread__/n760_400_MonkiesPub.hpp"
#include "../n800_learn___/n800_100_stopwatch.hpp"
#include "n885_040_ourCarriage.hpp"	// FIXME:


using namespace std;


using History = Stats<false>;
using Gains = Stats<true>;


/// <summary>
/// 思考部。大陸を大冒険する感じ（＾▽＾）
/// </summary>
class AdventureContinent {


public:


	/// <summary>
	///		<pre>
	/// 思考するぜ☆（＾ｑ＾）大陸を馬車で大冒険する気分（＾▽＾）
	/// 
	///		- メイン・スレッドの　アイドル・ループの中で呼び出される。
	///		- （１）入玉勝ち判定
	///		- （２）反復深化探索を行うぜ☆
	///		</pre>
	/// </summary>
	/// <param name="captainsOurCarriage">キャプテンの持っている、わたしたちの馬車☆</param>
	static void	exploreContinent_n10(
		OurCarriage& captainsOurCarriage);


	/// <summary>
	/// 入玉勝ち判定
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	static bool AdventureContinent::IsNyugyokuWin(const Position& pos);
};
