#include "../../header/n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../../header/n340_bonaMove/n340_500_IBonaMovable.hpp"
#include "../../header/n351_bonaMove/n351_090_nullBonaMove.hpp"
#include "../../header/n351_bonaMove/n351_100_direcMisc.hpp"
#include "../../header/n351_bonaMove/n351_120_direcFile.hpp"
#include "../../header/n351_bonaMove/n351_130_direcRank.hpp"
#include "../../header/n351_bonaMove/n351_140_direcDiagNESW.hpp"
#include "../../header/n351_bonaMove/n351_150_direcDiagNWSE.hpp"
#include "../../header/n351_bonaMove/n351_500_bonaDirArray.hpp"


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
