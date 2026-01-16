#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../n130_100_boardBb_/n160_180_knightAttackBb.hpp"
#include "../n130_100_boardBb_/n160_230_setMaskBB.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n340_bonaMove/n340_500_IBonaMovable.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class MiscBonaMove : public IBonaMovable
{


public:


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
		assert(false); // 最適化の為のダミー
	}
};


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern MiscBonaMove g_miscBonaMove;
