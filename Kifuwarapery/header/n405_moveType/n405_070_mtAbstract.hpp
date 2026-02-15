#pragma once

#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"


/// <summary>
/// 
/// </summary>
class MoveTypeAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="all"></param>
	/// <returns></returns>
	virtual MoveStack* GenerateMove(MoveStack* moveStackList, const Position& pos, bool all=false) const = 0;
};
