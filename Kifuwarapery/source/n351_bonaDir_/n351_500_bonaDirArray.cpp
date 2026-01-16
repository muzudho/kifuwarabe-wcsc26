#include "../../header/n340_bonaDir_/n340_500_IBonaDirectional.hpp"
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
