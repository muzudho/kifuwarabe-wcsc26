#pragma once


/// <summary>
///		<pre>
/// ノードの探索の仕方の種類
/// 
///     - `g_NODEKIND_PROGRAMS` の添え字に使うぜ☆（＾ｑ＾）
///     - 静止探索（Quiescence Search）で使う猿の性格の種類とマージした（＾～＾）
///         - `AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchByMonkeyPersonalities` の添え字に使うぜ☆（＾ｑ＾）
///		- PV はしっかり探索するぜ☆（＾ｑ＾） 几帳面（Meticulous）
/// 	- NonPV は手抜き探索するぜ☆（＾ｑ＾） 大雑把（Easy-going ）
///		</pre>
/// </summary>
enum MonkeyPersonalities {
	EarlyAdopter,                   // [0] 旧名： `RootNode`	- 最初の反復深化探索をする猿（＾～＾）
	Meticulous,						// [1] 旧名： `PVNode`		- ［几帳面な猿］が探索（＾～＾）
    EasyGoing,						// [2] 旧名： `NonPVNode`	- ［大雑把な性格の猿］が探索（＾～＾）
};
