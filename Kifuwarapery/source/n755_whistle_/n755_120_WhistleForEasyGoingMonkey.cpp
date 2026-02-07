#include "../../header/n755_whistle_/n755_120_WhistleForEasyGoingMonkey.hpp"
#include "../../header/n887_nodeKind/n887_150_adventurePlainNodekindSplitedNodeEasyGoingMonkey.hpp"


const WhistleForEasyGoingMonkey g_WHISTLE_FOR_EASY_GOING_MONKEY;


/// <summary>
///		<pre>
///		- スプリット・ポイントでの探索開始？
///		- 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
///		</pre>/// </summary>
/// <param name="ownerMonkeySplitedPlace"></param>
/// <param name="ourCarriage"></param>
/// <param name="pos"></param>
/// <param name="pFlashlight"></param>
void WhistleForEasyGoingMonkey::blowWhistle_asMonkeySplitedPlace(
	MonkeySplitedPlace& ownerMonkeySplitedPlace, 
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight) const
{
	//────────────────────────────────────────────────────────────────────────────────
	// 探索☆？（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	// スプリットポイントは検索を開始するぜ☆（＾ｑ＾）
	g_NODEKIND_MONKEYSPLITEDPLACE_EASY_GOING_MONKEY.explorePlain_10i(
		ourCarriage,
		pos,
		pFlashlight + 1,
		ownerMonkeySplitedPlace.m_alpha,
		ownerMonkeySplitedPlace.m_beta,
		ownerMonkeySplitedPlace.m_depth,
		ownerMonkeySplitedPlace.m_cutNode
		);
}
