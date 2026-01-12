#include "../../header/n885_searcher/n885_310_adventureBattlefieldQsearchAbstract.hpp"
#include "../../header/n885_searcher/n885_320_adventureBattlefieldQsearchPv.hpp"
#include "../../header/n885_searcher/n885_330_adventureBattlefieldQsearchNonPv.hpp"
#include "../../header/n885_searcher/n885_340_adventureBattlefieldQsearchPrograms.hpp"


const AdventureBattlefieldQsearchPv AdventureBattlefieldQsearchPrograms::m_adventureBattlefieldQsearchPv;
const AdventureBattlefieldQsearchNonPv AdventureBattlefieldQsearchPrograms::m_adventureBattlefieldQsearchNonPv;


/// <summary>
/// 静止探索プログラム配列
/// </summary>
const AdventureBattlefieldQsearchAbstract* AdventureBattlefieldQsearchPrograms::m_pAdventureBattlefieldQsearchPrograms[3] = {
	nullptr,
	&AdventureBattlefieldQsearchPrograms::m_adventureBattlefieldQsearchPv,
	&AdventureBattlefieldQsearchPrograms::m_adventureBattlefieldQsearchNonPv
};
