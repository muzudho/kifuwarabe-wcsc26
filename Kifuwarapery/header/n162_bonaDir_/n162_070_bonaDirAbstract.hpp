#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../../src/lib_toybox_base/square.hpp"
#include "../n161_sqDistan/n161_500_squareDistance.hpp"
#include "../n220_position/n220_650_position.hpp" //FIXME:


//class Position;


/// <summary>
/// 
/// </summary>
class BonaDirAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	virtual void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="position"></param>
	/// <param name="from"></param>
	/// <param name="ksq"></param>
	/// <param name="us"></param>
	virtual void Do2Move(Position& position, Square from, const Square ksq, const Color us) const = 0;
};
