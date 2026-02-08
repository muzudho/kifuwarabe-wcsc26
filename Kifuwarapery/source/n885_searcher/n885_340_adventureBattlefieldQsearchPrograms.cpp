#include "../../header/n885_searcher/n885_310_adventureBattlefieldQsearchAbstract.hpp"
#include "../../header/n885_searcher/n885_320_adventureBattlefieldQsearchPv.hpp"
#include "../../header/n885_searcher/n885_330_adventureBattlefieldQsearchNonPv.hpp"
#include "../../header/n885_searcher/n885_340_adventureBattlefieldQsearchPrograms.hpp"


const AdventureBattlefieldQsearchPv AdventureBattlefieldQsearchByMonkeyPersonalitiesModel::m_adventureBattlefieldQsearchByMeticulousMonkey;
const AdventureBattlefieldQsearchNonPv AdventureBattlefieldQsearchByMonkeyPersonalitiesModel::m_adventureBattlefieldQsearchByEasyGoingMonkey;


/// <summary>
/// ［猿の性格］別、静止探索プログラム配列
/// </summary>
const AdventureBattlefieldQsearchAbstract* AdventureBattlefieldQsearchByMonkeyPersonalitiesModel::m_pAdventureBattlefieldQsearchByMonkeyPersonalities[3] = {
	nullptr,
	&AdventureBattlefieldQsearchByMonkeyPersonalitiesModel::m_adventureBattlefieldQsearchByMeticulousMonkey,
	&AdventureBattlefieldQsearchByMonkeyPersonalitiesModel::m_adventureBattlefieldQsearchByEasyGoingMonkey
};
