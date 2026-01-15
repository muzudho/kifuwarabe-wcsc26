#pragma once

#include <cstdlib>	// abs()
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_250_squareDelta.hpp"
#include "../n160_boardBb_/n160_150_rookAttackBb.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n340_bonaDir_/n340_500_bonaDirAbstract.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class DirecFile : public BonaDirAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const
	{
		squareDistance.SetValue( sq0, sq1,
			abs(static_cast<int>(sq0 - sq1) / static_cast<int>(SquareDelta::DeltaN))
		);
	}

	/// <summary>
	/// 
	/// </summary>
	/// <param name="position"></param>
	/// <param name="from"></param>
	/// <param name="ksq"></param>
	/// <param name="us"></param>
	void Do2Move(Position& position, Square from, const Square ksq, const Color us) const
	{
		// from の位置から縦に利きを調べると相手玉と、空き王手している駒に当たっているはず。味方の駒が空き王手している駒。
		position.GetStateInfo()->m_checkersBB |=
			g_rookAttackBb.GetControllBbFile(&position.GetOccupiedBB(), from) & position.GetBbOf10(us);
	}
};


/// <summary>
/// 
/// </summary>
extern DirecFile g_direcFile;
