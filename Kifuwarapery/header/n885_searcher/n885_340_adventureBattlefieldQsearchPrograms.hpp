#pragma once
#include "n885_310_adventureBattlefieldQsearchAbstract.hpp"
#include "n885_320_adventureBattlefieldQsearchPv.hpp"
#include "n885_330_adventureBattlefieldQsearchNonPv.hpp"


/// <summary>
/// ［猿の性格］別、静止探索プログラム配列
/// </summary>
class AdventureBattlefieldQsearchByMonkeyPersonalitiesModel
{


public:


	/// <summary>
	/// ［几帳面な猿］の静止探索。
	/// </summary>
	static const AdventureBattlefieldQsearchPv m_adventureBattlefieldQsearchByMeticulousMonkey;


	/// <summary>
	/// ［大雑把な性格の猿］の静止探索。
	/// </summary>
	static const AdventureBattlefieldQsearchNonPv m_adventureBattlefieldQsearchByEasyGoingMonkey;


	/// <summary>
    /// ［猿の性格］別、静止探索プログラム配列
	/// </summary>
	static const AdventureBattlefieldQsearchAbstract* m_pAdventureBattlefieldQsearchByMonkeyPersonalities[3];
};


/// <summary>
/// 使ってない（＾～＾）？ static だからリンクエラー回避のために置いてあるだけ☆？（＾～＾）
/// </summary>
extern AdventureBattlefieldQsearchByMonkeyPersonalitiesModel g_adventureBattlefieldQsearchByMonkeyPersonalities;
