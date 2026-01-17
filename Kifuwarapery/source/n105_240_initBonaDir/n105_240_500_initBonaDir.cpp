#include "../../header/n105_100_color___/n105_100_100_color.hpp"
#include "../../header/n105_120_square__/n105_120_250_squareDelta.hpp"
#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../header/n130_100_boardBb_/n160_180_knightAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_230_setMaskBb.hpp"
#include "../../header/n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_700_BonaDirectionArray.hpp"
#include "../../header/n105_240_initBonaDir/n105_240_500_initBonaDir.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="squareDistance"></param>
void UtilSquareDistance::initSquareDistance_app10(SquareDistance& squareDistance) {
	for (Square sq0 = I9; sq0 < SquareNum; ++sq0) {
		for (Square sq1 = I9; sq1 < SquareNum; ++sq1) {
			// ボナンザの［向き］を利用
			g_bonaDirectionArray[g_squareRelation.GetSquareRelation(sq0, sq1)]->InitializeSquareDistance(squareDistance, sq0, sq1);
		}
	}
}
