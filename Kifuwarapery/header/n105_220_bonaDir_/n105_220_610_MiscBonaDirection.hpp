#pragma once
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../n130_100_boardBb_/n160_180_knightAttackBb.hpp"			// FIXME: 参照順序
#include "../n130_100_boardBb_/n160_230_setMaskBB.hpp"				// FIXME: 参照順序


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
		squareDistance.SetValue(sq0, sq1, 0);
		if (
			g_setMaskBb.IsSet(&g_knightAttackBb.GetControllBb(Black, sq0), sq1) ||
			g_setMaskBb.IsSet(&g_knightAttackBb.GetControllBb(White, sq0), sq1)
			)
		{
			squareDistance.SetValue(sq0, sq1, 1);
		}
	}
};


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern MiscBonaDirection g_miscBonaDirection;
