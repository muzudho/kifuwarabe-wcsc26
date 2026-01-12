#include "../../header/n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../../header/n887_nodeType/n887_100_adventurePlainNodekindRoot.hpp"
#include "../../header/n887_nodeType/n887_110_adventurePlainNodekindPv.hpp"
#include "../../header/n887_nodeType/n887_120_adventurePlainNodekindNonPv.hpp"
#include "../../header/n887_nodeType/n887_130_adventurePlainNodekindSplitedNodeRoot.hpp"
#include "../../header/n887_nodeType/n887_140_adventurePlainNodekindSplitedNodePv.hpp"
#include "../../header/n887_nodeType/n887_150_adventurePlainNodekindSplitedNodeNonPv.hpp"
#include "../../header/n887_nodeType/n887_500_adventurePlainNodekindPrograms.hpp"


/// <summary>
/// サーチ☆
/// 主に、反復深化探索の中で呼び出される☆
/// </summary>
AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[6] = {
	&g_NODETYPE_ROOT,
	&g_NODETYPE_PV,
	&g_NODETYPE_NON_PV,
	&g_NODETYPE_SPLITEDNODE_ROOT,
	&g_NODETYPE_SPLITEDNODE_PV,
	&g_NODETYPE_SPLITEDNODE_NON_PV
};
