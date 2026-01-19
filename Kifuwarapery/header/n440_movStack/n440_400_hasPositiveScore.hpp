#pragma once

#include "../n165_movStack/n165_500_moveStack.hpp"


/// <summary>
/// 
/// </summary>
struct HasPositiveSweetness {


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ms"></param>
	/// <returns></returns>
	bool operator () (const MoveStack& ms) {
		return 0 < ms.m_sweetness;
	}
};
