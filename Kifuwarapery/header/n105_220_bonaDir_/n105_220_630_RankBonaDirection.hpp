#pragma once
#include <cstdlib>	// abs()
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_250_squareDelta.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n250_pieceTyp/n350_040_ptEvent.hpp"
#include "../n250_pieceTyp/n350_500_ptPrograms.hpp"
#include "../n340_bonaMove/n340_500_IBonaMovable.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class RankBonaDirection : public IBonaDirectionable
{


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const
	{
		squareDistance.SetValue(sq0, sq1,
			abs(static_cast<int>(sq0 - sq1) / static_cast<int>(SquareDelta::DeltaE))
		);
	}
};


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern RankBonaDirection g_rankBonaDirection;
