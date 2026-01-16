#include "../../header/n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../../header/n105_220_bonaDir_/n105_220_600_NullBonaDirection.hpp"
#include "../../header/n340_bonaMove/n340_500_IBonaMovable.hpp"
#include "../../header/n351_bonaDir_/n351_090_nullBonaDir.hpp"
#include "../../header/n351_bonaDir_/n351_100_direcMisc.hpp"
#include "../../header/n351_bonaDir_/n351_120_direcFile.hpp"
#include "../../header/n351_bonaDir_/n351_130_direcRank.hpp"
#include "../../header/n351_bonaDir_/n351_140_direcDiagNESW.hpp"
#include "../../header/n351_bonaDir_/n351_150_direcDiagNWSE.hpp"
#include "../../header/n351_bonaDir_/n351_500_bonaDirArray.hpp"


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
