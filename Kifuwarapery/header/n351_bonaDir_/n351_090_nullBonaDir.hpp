#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n161_sqDistan/n161_500_squareDistance.hpp"
#include "../n340_bonaDir_/n162_070_bonaDirAbstract.hpp"
#include "../n220_position/n220_650_position.hpp"


/// <summary>
/// 
/// </summary>
class NullBonaDir : public BonaDirAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const {
		UNREACHABLE;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="position"></param>
	/// <param name="from"></param>
	/// <param name="ksq"></param>
	/// <param name="us"></param>
	void Do2Move(Position& position, Square from, const Square ksq, const Color us) const {
		UNREACHABLE;
	}
};


/// <summary>
/// 
/// </summary>
extern NullBonaDir g_nullBonaDir;
