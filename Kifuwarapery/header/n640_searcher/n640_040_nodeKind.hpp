#pragma once


/// <summary>
///		<pre>
/// ノードの探索の仕方の種類
/// 
///		- 探索で使う（＾～＾）
///		</pre>
/// </summary>
enum NodeKind {

	/// <summary>
	///		<pre>
	/// 初手（＾～＾）
	/// 
	///		- ExploreMountain
	///		</pre>
	/// </summary>
	No0_Root,

	/// <summary>
	///		<pre>
	/// 変化以外（初手と本筋）で使われる（＾～＾）
	/// 
	///		- explorePlain_10a520b500c500d500e500f500g600h900i_betaLargeRecursiveSearch
	///		- explorePlain_10a520b500c500d500e500f500g200h800i_internalIterativeDeepening
	///		</pre>
	/// </summary>
	No1_PV,

	/// <summary>
	/// 変化で使われる（＾～＾）
	/// </summary>
	No2_NonPV,

	/// <summary>
	/// 使ってないのでは（＾～＾）？
	/// </summary>
	SplitedNodeNo0Root,

	/// <summary>
	/// 使ってないのでは（＾～＾）？
	/// </summary>
	SplitedNodeNo1PV,

	/// <summary>
	/// 使ってないのでは（＾～＾）？
	/// </summary>
	SplitedNodeNo2NonPV
};
