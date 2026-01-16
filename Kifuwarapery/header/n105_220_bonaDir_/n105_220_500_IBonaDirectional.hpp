#pragma once
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class IBonaDirectionable
{


public:


	/// <summary>
	/// インターフェースのメソッド
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	virtual void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const = 0;
};
