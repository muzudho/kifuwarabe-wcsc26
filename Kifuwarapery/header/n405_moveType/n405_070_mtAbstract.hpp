#pragma once

#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n220_position/n220_650_position.hpp"


/// <summary>
/// 
/// </summary>
class MoveTypeAbstract {


public:


	/// <summary>
	/// インターフェースのメソッド
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="all"></param>
	/// <returns></returns>
	virtual DeliciousBanana* GenerateMove(DeliciousBanana* moveStackList, const Position& pos, bool all=false) const = 0;
};
