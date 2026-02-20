#include "../../src/lib_toybox_base/color.hpp"
#include "../../src/lib_toybox_base/square_delta.hpp"
#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../src/lib_bitboard/init180_knightAttackBb.hpp"
#include "../../src/lib_bitboard/n160_230_setMaskBb.hpp"
#include "../../header/n161_sqDistan/n161_500_squareDistance.hpp"
#include "../../header/n163_sqDistan/n163_600_utilSquareDistance.hpp"
#include "../../header/n351_bonaDir_/n351_500_bonaDirArray.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="squareDistance"></param>
void UtilSquareDistance::initialize_10a280b_squareDistance(SquareDistance& squareDistance) {
	for (Square sq0 = I9; sq0 < SquareNum; ++sq0) {
		for (Square sq1 = I9; sq1 < SquareNum; ++sq1) {
			g_bonaDirArray[g_squareRelation.GetSquareRelation(sq0, sq1)]->InitializeSquareDistance(squareDistance, sq0, sq1);
		}
	}
}
