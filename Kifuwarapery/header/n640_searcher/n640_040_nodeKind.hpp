#pragma once


/// <summary>
///		<pre>
/// ノードの探索の仕方の種類
/// 
///     - `g_NODEKIND_PROGRAMS` の添え字に使うぜ☆（＾ｑ＾）
///		- PV はしっかり探索するぜ☆（＾ｑ＾） 几帳面（Meticulous）
/// 	- NonPV は手抜き探索するぜ☆（＾ｑ＾） 大雑把（Easy-going ）
///		</pre>
/// </summary>
enum MonkeyPersonalities {
	EarlyAdopter,                   // [0] 旧名： `RootNode` - 最初の反復深化探索をする猿（＾～＾）
	Meticulous,						// [1] 旧名： `PVNode` - ［几帳面な猿］が探索（＾～＾）
    EasyGoing,						// [2] 旧名： `NonPVNode` - ［大雑把な性格の猿］が探索（＾～＾）
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
    QsearchMeticulous,      // 旧名： `AlphaBetaNode`
    QsearchEasyGoing,       // 旧名： `QsearchNode`
};