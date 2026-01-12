#include "../../header/n885_searcher/n885_310_adventureBattlefieldQsearchAbstract.hpp"
#include "../../header/n885_searcher/n885_320_adventureBattlefieldQsearchPv.hpp"
#include "../../header/n885_searcher/n885_330_adventureBattlefieldQsearchNonPv.hpp"
#include "../../header/n885_searcher/n885_340_hitchhikerQsearchPrograms.hpp"


const HitchhikerQsearchPv HitchhikerQsearchPrograms::m_hitchhikerQsearchPv;
const HitchhikerQsearchNonPv HitchhikerQsearchPrograms::m_hitchhikerQsearchNonPv;


/// <summary>
/// 静止探索プログラム配列
/// </summary>
const AdventureBattlefieldQsearchAbstract* HitchhikerQsearchPrograms::m_pHitchhikerQsearchPrograms[3] = {
	nullptr,
	&HitchhikerQsearchPrograms::m_hitchhikerQsearchPv,
	&HitchhikerQsearchPrograms::m_hitchhikerQsearchNonPv
};
