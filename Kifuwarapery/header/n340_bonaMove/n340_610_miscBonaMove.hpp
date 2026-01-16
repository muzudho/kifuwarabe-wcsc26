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
class MiscBonaDirection : public IBonaDirectionable
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
		// DirecMisc な関係は全て距離 1 にしてもKPE学習には問題無いんだけれど。
		squareDistance.SetValue(sq0,sq1, 0);
		if (
			g_setMaskBb.IsSet(&g_knightAttackBb.GetControllBb(Black, sq0), sq1) ||
			g_setMaskBb.IsSet(&g_knightAttackBb.GetControllBb(White, sq0), sq1)
			)
		{
			squareDistance.SetValue( sq0, sq1, 1);
		}
	}
};


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern MiscBonaDirection g_miscBonaDirection;


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
