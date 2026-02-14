#pragma once
#include "../n080_100_sysWorld/n080_100_080_putb.hpp"

using namespace std;


//────────────────────────────────────────────────────────────────────────────────
// 同期入出力
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 同期入出力
/// </summary>
enum SyncCout {
	IOLock,
	IOUnlock
};
std::ostream& operator << (std::ostream& os, SyncCout sc);
#define SYNCCOUT std::cout << IOLock
#define SYNCENDL std::endl << IOUnlock
