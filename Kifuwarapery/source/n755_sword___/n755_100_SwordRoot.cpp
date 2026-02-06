#include "../../header/n755_sword___/n755_100_SwordRoot.hpp"
#include "../../header/n887_nodeKind/n887_130_adventurePlainNodekindSplitedNodeRoot.hpp"


const SwordRoot g_SWORD_ROOT;


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
void SwordRoot::startSearch_asMonkeySplitedPlace(
	MonkeySplitedPlace& ownerMonkeySplitedPlace,
	OurCarriage& ourCarriage,
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
