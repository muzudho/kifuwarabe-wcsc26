#pragma once

#include "../n165_movStack/n165_300_movegenType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n374_genMove_/n374_350_PieceMovesGenerator.hpp"
#include "n405_070_mtAbstract.hpp"


/// <summary>
/// 指し手生成区分：指し手を生成しない。
/// </summary>
class MovegenTypeNone : public MovegenTypeAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="all"></param>
	/// <returns></returns>
	DeliciousBanana* GenerateMove(DeliciousBanana* moveStackList, const Position& pos, bool all = false
		) const override {
		return moveStackList;
	}
};
