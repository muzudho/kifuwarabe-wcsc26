#include "../../header/n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../../header/n887_nodeKind/n887_100_adventurePlainNodekindRoot.hpp"
#include "../../header/n887_nodeKind/n887_110_adventurePlainNodekindMeticulousMonkey.hpp"
#include "../../header/n887_nodeKind/n887_120_adventurePlainNodekindEasyGoingMonkey.hpp"
#include "../../header/n887_nodeKind/n887_130_adventurePlainNodekindSplitedNodeRoot.hpp"
#include "../../header/n887_nodeKind/n887_140_adventurePlainNodekindSplitedNodeMeticulousMonkey.hpp"
#include "../../header/n887_nodeKind/n887_150_adventurePlainNodekindSplitedNodeEasyGoingMonkey.hpp"
#include "../../header/n887_nodeKind/n887_500_adventurePlainNodekindPrograms.hpp"


/// <summary>
///		<pre>
/// サーチ☆
/// 主に、反復深化探索の中で呼び出される☆
/// 
///		- 配列長６も要らんのでは（＾～＾）？ ［一番乗りする猿］［几帳面な猿］［大雑把な性格の猿］の３つで十分では（＾～＾）？
///		</pre>
/// </summary>
AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[6] = {
	&g_NODEKIND_ROOT,									// [0]
    &g_NODEKIND_METICULOUS_MONKEY,						// [1] 使ってない（＾～＾）？ 静止探索にも使うぜ☆！（＾ｑ＾）
	&g_NODEKIND_EASY_GOING_MONKEY,						// [2] 使ってない（＾～＾）？ 静止探索にも使うぜ☆！（＾ｑ＾）
	&g_NODEKIND_MONKEYSPLITEDPLACE_ROOT,				// [3] 使ってない（＾～＾）？ 
	&g_NODEKIND_MONKEYSPLITEDPLACE_METICULOUS_MONKEY,	// [4]
	&g_NODEKIND_MONKEYSPLITEDPLACE_EASY_GOING_MONKEY	// [5]
};
