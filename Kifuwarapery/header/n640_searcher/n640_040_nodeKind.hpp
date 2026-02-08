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
	EarlyAdopter,                   // [0] 旧名： `RootNode` - 最初の反復深化探索をする猿（＾～＾）
    QuiescenceSearchMeticulous,     // [1] 旧名： `AlphaBetaNode` - 未使用。静止探索配列に合わせたプレースホルダー（＾～＾）
    QuiescenceSearchEasyGoing,      // [2] 旧名： `QsearchNode`, - 未使用。静止探索配列に合わせたプレースホルダー（＾～＾）
    NullMove,                       // [3] 旧名： `NullMoveNode` - ［一番乗りする猿］が探索（＾～＾）使ってない（＾～＾）？
	Meticulous,						// [4] 旧名： `PVNode` - ［几帳面な猿］が探索（＾～＾）
    EasyGoing,						// [5] 旧名： `NonPVNode` - ［大雑把な性格の猿］が探索（＾～＾）
};

/// <summary>
/// 	<pre>
/// 静止探索で使う猿の性格の種類
/// 
///     - `AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchByMonkeyPersonalities` の添え字に使うぜ☆（＾ｑ＾）
///     </pre>
/// </summary>
enum MonkeyPersonalitiesForQuiescenceSearch {
    QsearchEarlyAdopter,
    QsearchMeticulous,
    QsearchEasyGoing,
};