#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n340_bonaDir_/n340_500_bonaDirAbstract.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class NullBonaDir : public BonaDirAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const
	{
		UNREACHABLE;
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="position"></param>
	/// <param name="from"></param>
	/// <param name="ksq"></param>
	/// <param name="us"></param>
	/// <returns>checkerBB</returns>
	void Do2Move(Position& position, Square from, const Square ksq, const Color us) const
	{
		UNREACHABLE;
	}
};


/// <summary>
/// 
/// </summary>
extern NullBonaDir g_nullBonaDir;
