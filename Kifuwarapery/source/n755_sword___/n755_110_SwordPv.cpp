#include "../../header/n755_sword___/n755_110_SwordPv.hpp"
#include "../../header/n887_nodeKind/n887_140_adventurePlainNodekindSplitedNodePv.hpp"


//extern const NodetypeSplitedNodePv g_NODETYPE_SPLITEDNODE_PV;


const SwordPv g_SWORD_PV;


/// <summary>
/// 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
/// </summary>
/// <param name="ownerSplitedNode"></param>
/// <param name="ourCarriage"></param>
/// <param name="pos"></param>
/// <param name="pFlashlight"></param>
void SwordPv::GoSearch_AsSplitedNode(
	SplitedNode& ownerSplitedNode, 
	OurCarriage& ourCarriage,
	Position& pos,
	Flashlight* pFlashlight
	) const {
	//────────────────────────────────────────────────────────────────────────────────
	// 探索☆？（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	// スプリットポイントは検索を開始するぜ☆（＾ｑ＾）
	g_NODETYPE_SPLITEDNODE_PV.ExplorePlain(
		ourCarriage,
		pos,
		pFlashlight + 1,
		ownerSplitedNode.m_alpha,
		ownerSplitedNode.m_beta,
		ownerSplitedNode.m_depth,
		ownerSplitedNode.m_cutNode
		);
}
