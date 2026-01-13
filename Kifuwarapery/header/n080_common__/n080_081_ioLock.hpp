#pragma once
#include "../n080_common__/n080_080_putb.hpp"


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
