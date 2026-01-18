#include "../../header/n755_sword___/n755_110_SwordPv.hpp"
#include "../../header/n887_nodeKind/n887_140_adventurePlainNodekindSplitedNodePv.hpp"


const SwordPv g_SWORD_PV;


/// <summary>
/// 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
/// </summary>
/// <param name="ownerSplitedNode"></param>
/// <param name="ourCarriage"></param>
/// <param name="pos"></param>
/// <param name="pFlashlight"></param>
void SwordPv::startSearch_asSplitedNode(
	SplitedNode& ownerSplitedNode, 
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight
	) const {
	//────────────────────────────────────────────────────────────────────────────────
	// 探索☆？（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	// スプリットポイントは検索を開始するぜ☆（＾ｑ＾）
	g_NODEKIND_SPLITEDNODE_PV.explorePlain_10i(
		ourCarriage,
		pos,
		pFlashlight + 1,
		ownerSplitedNode.m_alpha,
		ownerSplitedNode.m_beta,
		ownerSplitedNode.m_depth,
		ownerSplitedNode.m_cutNode
		);
}
