#pragma once

#include "../n480_tt______/n480_280_tTEntry.hpp"


/// <summary>
/// 
/// </summary>
const int g_clusterSize = CacheLineSize / sizeof(TTEntry);
static_assert(0 < g_clusterSize, "");


/// <summary>
/// 
/// </summary>
struct TTCluster {
	/// <summary>
	/// 
	/// </summary>
	TTEntry m_data[g_clusterSize];
};
