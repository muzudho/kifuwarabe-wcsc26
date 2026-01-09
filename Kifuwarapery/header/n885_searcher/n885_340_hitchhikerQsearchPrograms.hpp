#pragma once


#include "n885_310_hitchhikerQsearchAbstract.hpp"
#include "n885_320_hitchhikerQsearchPv.hpp"
#include "n885_330_hitchhikerQsearchNonPv.hpp"


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
	static const HitchhikerQsearchAbstract* m_pHitchhikerQsearchPrograms[3];
};


/// <summary>
/// 
/// </summary>
extern HitchhikerQsearchPrograms g_hitchhikerQsearchPrograms;
