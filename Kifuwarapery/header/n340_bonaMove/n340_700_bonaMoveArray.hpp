#pragma once
#include "../n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../n340_bonaMove/n340_500_IBonaMovable.hpp"
#include "n340_610_miscBonaMove.hpp"
#include "n340_620_fileBonaMove.hpp"
#include "n340_630_rankBonaMove.hpp"
#include "n340_640_diagonalNESWBonaMove.hpp"
#include "n340_650_diagonalNWSEBonaMove.hpp"
#include "n340_700_bonaMoveArray.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern IBonaDirectionable* g_bonaDirectionArray[6];


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern IBonaMovable* g_bonaMoveArray[6];
