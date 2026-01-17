#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class NullBonaDirection : public IBonaDirectionable
{


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	void InitializeSquareDistance(TwoSquaresDistanceKind& squareDistance, Square sq0, Square sq1) const
	{
		UNREACHABLE;
	}
};


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern NullBonaDirection g_nullBonaDirection;
