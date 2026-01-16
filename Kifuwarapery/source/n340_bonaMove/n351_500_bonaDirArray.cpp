#include "../../header/n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../../header/n340_bonaMove/n340_500_IBonaMovable.hpp"
#include "../../header/n340_bonaMove/n340_600_nullBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_610_miscBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_620_fileBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_630_rankBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_640_diagonalNESWBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_650_diagonalNWSEBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_700_bonaMoveArray.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
IBonaMovable* g_bonaMoveArray[6] = {
	&g_miscBonaMove,
	&g_nullBonaMove,
	&g_fileBonaMove,
	&g_rankBonaMove,
	&g_diagonalNESWBonaMove,
	&g_diagonalNWSEBonaMove
};
