#pragma once


/// <summary>
///		<pre>
/// ノードの探索の仕方の種類
/// 
///		- 探索で使う（＾～＾）
///		</pre>
/// </summary>
enum NodeKind {
	N00_Root,
	N01_PV,
	N02_NonPV,
	SplitedNodeRoot,
	SplitedNodePV,
	SplitedNodeNonPV
};
