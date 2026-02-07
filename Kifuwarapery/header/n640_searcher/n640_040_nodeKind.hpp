#pragma once


/// <summary>
///		<pre>
/// ノードの探索の仕方の種類
/// 
///		- 探索で使う（＾～＾）
///		- PV はしっかり探索するぜ☆（＾ｑ＾） 几帳面（Meticulous）
/// 	- NonPV は手抜き探索するぜ☆（＾ｑ＾） 衝動的（Impulsive）、大雑把（Easy-going ）
///		</pre>
/// </summary>
enum NodeKind {
	Root,
	Meticulous,						// 旧名： `PVNode`
    EasyGoing,						// 旧名： `NonPVNode`
    MonkeySplitedPlaceRoot,			// 旧名： `SplitPointRoot`
	MonkeySplitedPlaceMeticulous,	// 旧名： `SplitPointPV`
    MonkeySplitedPlaceEasyGoing		// 旧名： `SplitPointNonPV`
};
