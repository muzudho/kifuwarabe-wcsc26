#pragma once
#include "n885_310_adventureBattlefieldQsearchAbstract.hpp"
#include "n885_320_adventureBattlefieldQsearchPv.hpp"
#include "n885_330_adventureBattlefieldQsearchNonPv.hpp"


/// <summary>
/// 各種静止探索
/// </summary>
class AdventureBattlefieldQsearchPrograms {


public:


	/// <summary>
	/// 本筋の静止探索。
	/// </summary>
	static const AdventureBattlefieldQsearchPv m_adventureBattlefieldQsearchPv;


	/// <summary>
	/// 変化の静止探索。
	/// </summary>
	static const AdventureBattlefieldQsearchNonPv m_adventureBattlefieldQsearchNonPv;


	/// <summary>
	/// 
	/// </summary>
	static const AdventureBattlefieldQsearchAbstract* m_pAdventureBattlefieldQsearchPrograms[3];
};


/// <summary>
/// 
/// </summary>
extern AdventureBattlefieldQsearchPrograms g_adventureBattlefieldQsearchPrograms;
