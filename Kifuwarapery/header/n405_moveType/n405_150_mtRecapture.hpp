#pragma once

#include "../n165_movStack/n165_300_moveType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n374_genMove_/n374_350_PieceMovesGenerator.hpp"
#include "n405_070_mtAbstract.hpp"


/// <summary>
/// 
/// </summary>
class MoveTypeRecapture : public MoveTypeAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="all"></param>
	/// <returns></returns>
	MoveStack* GenerateMove(MoveStack* moveStackList, const Position& pos, bool all = false
		) const override {
		return moveStackList;
	}
};
