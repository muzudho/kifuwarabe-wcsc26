#include "../../header/n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_600_NullBonaDirection.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_610_MiscBonaDirection.hpp"

#include "../../header/n340_bonaMove/n340_620_fileBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_630_rankBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_640_diagonalNESWBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_650_diagonalNWSEBonaMove.hpp"
#include "../../header/n340_bonaMove/n340_700_bonaMoveArray.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
IBonaDirectionable* g_bonaDirectionArray[6] = {
	&g_miscBonaDirection,
	&g_nullBonaDirection,
	&g_fileBonaDirection,
	&g_rankBonaDirection,
	&g_diagonalNESWBonaDirection,
	&g_diagonalNWSEBonaDirection
};
