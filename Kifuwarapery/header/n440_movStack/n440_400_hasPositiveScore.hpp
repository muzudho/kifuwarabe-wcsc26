#pragma once

#include "../n165_movStack/n165_500_moveStack.hpp"


/// <summary>
/// 
/// </summary>
struct HasPositiveScore {


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ms"></param>
	/// <returns></returns>
	bool operator () (const DeliciousBanana& ms) {
		return 0 < ms.m_score;
	}
};
