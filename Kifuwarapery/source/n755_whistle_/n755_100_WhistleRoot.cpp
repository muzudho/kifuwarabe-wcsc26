#include "../../header/n755_whistle_/n755_100_WhistleRoot.hpp"
#include "../../header/n887_nodeKind/n887_130_adventurePlainNodekindSplitedNodeRoot.hpp"


const WhistleRoot g_WHISTLE_ROOT;


/// <summary>
///		<pre>
///		- スプリット・ポイントでの探索開始？
///		- 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
///		</pre>
/// </summary>
/// <param name="ownerMonkeySplitedPlace"></param>
/// <param name="ourCarriage"></param>
/// <param name="pos"></param>
/// <param name="pFlashlight"></param>
void WhistleRoot::blowWhistle_asMonkeySplitedPlace(
	MonkeySplitedPlace& ownerMonkeySplitedPlace,
	MuzGameEngineStorage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight) const
{

	//────────────────────────────────────────────────────────────────────────────────
	// 探索☆？（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	// スプリットポイントは検索を開始するぜ☆（＾ｑ＾）
	g_NODEKIND_MONKEYSPLITEDPLACE_ROOT.explorePlain_10i(
		ourCarriage,
		pos,
		pFlashlight + 1,
		ownerMonkeySplitedPlace.m_alpha,
		ownerMonkeySplitedPlace.m_beta,
		ownerMonkeySplitedPlace.m_depth,
		ownerMonkeySplitedPlace.m_cutNode
		);
}
