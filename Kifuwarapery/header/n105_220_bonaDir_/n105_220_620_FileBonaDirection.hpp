#pragma once
#include <cstdlib>	// abs()
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_250_squareDelta.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class FileBonaDirection : public IBonaDirectionable
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
		squareDistance.SetDistanceKind(
			sq0,
			sq1,
			abs(static_cast<int>(sq0 - sq1) / static_cast<int>(SquareDelta::DeltaN))
		);
	}
};


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern FileBonaDirection g_fileBonaDirection;
