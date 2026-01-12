#include "../../header/n886_repeType/n886_070_rtAbstract.hpp"
#include "../../header/n886_repeType/n886_100_rtNot.hpp"
#include "../../header/n886_repeType/n886_110_rtDraw.hpp"
#include "../../header/n886_repeType/n886_120_rtWin.hpp"
#include "../../header/n886_repeType/n886_130_rtLose.hpp"
#include "../../header/n886_repeType/n886_140_rtSuperior.hpp"
#include "../../header/n886_repeType/n886_150_rtInferior.hpp"
#include "../../header/n886_repeType/n886_500_rtArray.hpp"


/// <summary>
/// 千日手タイプ群☆
/// </summary>
const RepetitionTypeNot RepetitionTypeModels::m_NOT_REPETETION;
const RepetitionTypeDraw RepetitionTypeModels::m_DRAW;
const RepetitionTypeWin RepetitionTypeModels::m_WIN;
const RepetitionTypeLose RepetitionTypeModels::m_LOSE;
const RepetitionTypeSuperior RepetitionTypeModels::m_SUPERIOR;
const RepetitionTypeInferior RepetitionTypeModels::m_INFERIOR;


/// <summary>
/// 
/// </summary>
const RepetitionTypeAbstract* RepetitionTypeModels::m_ARRAY[6] = {
	&RepetitionTypeModels::m_NOT_REPETETION,
	&RepetitionTypeModels::m_DRAW,
	&RepetitionTypeModels::m_WIN,
	&RepetitionTypeModels::m_LOSE,
	&RepetitionTypeModels::m_SUPERIOR,
	&RepetitionTypeModels::m_INFERIOR,
};


/// <summary>
/// 一覧。配列含む。
/// </summary>
RepetitionTypeModels g_repetitionTypes;
