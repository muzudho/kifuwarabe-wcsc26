#pragma once
#include "n885_310_adventureBattlefieldQsearchAbstract.hpp"
#include "n885_320_adventureBattlefieldQsearchPv.hpp"
#include "n885_330_adventureBattlefieldQsearchNonPv.hpp"


/// <summary>
/// 
/// </summary>
class HitchhikerQsearchPrograms {


public:


	/// <summary>
	/// 
	/// </summary>
	static const HitchhikerQsearchPv m_hitchhikerQsearchPv;


	/// <summary>
	/// 
	/// </summary>
	static const HitchhikerQsearchNonPv m_hitchhikerQsearchNonPv;


	/// <summary>
	/// 
	/// </summary>
	static const AdventureBattlefieldQsearchAbstract* m_pHitchhikerQsearchPrograms[3];
};


/// <summary>
/// 
/// </summary>
extern HitchhikerQsearchPrograms g_hitchhikerQsearchPrograms;
