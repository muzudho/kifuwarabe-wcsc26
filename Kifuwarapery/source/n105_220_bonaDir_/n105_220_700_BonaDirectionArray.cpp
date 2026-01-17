#include "../../header/n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_600_NullBonaDirection.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_610_MiscBonaDirection.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_620_FileBonaDirection.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_630_RankBonaDirection.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_640_DiagonalNESWBonaDirection.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_650_DiagonalNWSEBonaDirection.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_700_BonaDirectionArray.hpp"


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
