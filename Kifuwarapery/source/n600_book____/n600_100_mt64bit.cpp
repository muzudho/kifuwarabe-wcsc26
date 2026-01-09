#include "../../header/n600_book____/n600_100_mt64bit.hpp"


//MT64bit g_mt64bit(std::chrono::system_clock::now().time_since_epoch().count());

/// <summary>
/// seed が固定値である必要は特に無い。
/// </summary>
MT64bit g_mt64bit;
