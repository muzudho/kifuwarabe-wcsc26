#pragma once


/// <summary>
///		<pre>
/// ノードの探索の仕方の種類
/// 
///		- 探索で使う（＾～＾）
///         - `g_NODEKIND_PROGRAMS` の添え字に使うぜ☆（＾ｑ＾）
///         - `AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchByMonkeyPersonalities` の添え字にも使うぜ☆（＾ｑ＾）
///		- PV はしっかり探索するぜ☆（＾ｑ＾） 几帳面（Meticulous）
/// 	- NonPV は手抜き探索するぜ☆（＾ｑ＾） 衝動的（Impulsive）、大雑把（Easy-going ）
///		</pre>
/// </summary>
enum NodeKind {
	Root,                           // 旧名： `RootNode` - 最初の反復深化探索をする猿（＾～＾）
    AlphaBeta,                      // 旧名： `AlphaBetaNode` - 使ってない（＾～＾）？
    Quiescence,                     // 旧名： `QsearchNode` - 使ってない（＾～＾）？
    NullMove,                       // 旧名： `NullMoveNode` - 使ってない（＾～＾）？
	Meticulous,						// 旧名： `PVNode`
    EasyGoing,						// 旧名： `NonPVNode`
    MonkeySplitedPlaceRoot,			// 旧名： `SplitPointRoot` - 使ってない（＾～＾）？
	MonkeySplitedPlaceMeticulous,	// 旧名： `SplitPointPV` - 使ってない（＾～＾）？
    MonkeySplitedPlaceEasyGoing		// 旧名： `SplitPointNonPV` - 使ってない（＾～＾）？
};
