#include "../../header/n105_100_color___/n105_100_100_color.hpp"
#include "../../header/n105_120_square__/n105_120_250_squareDelta.hpp"
#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../header/n160_board___/n160_180_knightAttackBb.hpp"
#include "../../header/n160_board___/n160_230_setMaskBb.hpp"
#include "../../header/n161_sqDistan/n161_500_squareDistance.hpp"
#include "../../header/n163_sqDistan/n163_600_utilSquareDistance.hpp"
#include "../../header/n351_bonaDir_/n351_500_bonaDirArray.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="squareDistance"></param>
void UtilSquareDistance::InitSquareDistance(SquareDistance& squareDistance) {
	for (Square sq0 = I9; sq0 < SquareNum; ++sq0) {
		for (Square sq1 = I9; sq1 < SquareNum; ++sq1) {
			g_bonaDirArray[g_squareRelation.GetSquareRelation(sq0, sq1)]->InitializeSquareDistance(squareDistance, sq0, sq1);
		}
	}
}
