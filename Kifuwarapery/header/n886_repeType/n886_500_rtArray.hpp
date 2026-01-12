#pragma once
#include "n886_070_rtAbstract.hpp"
#include "n886_100_rtNot.hpp"
#include "n886_110_rtDraw.hpp"
#include "n886_120_rtWin.hpp"
#include "n886_130_rtLose.hpp"
#include "n886_140_rtSuperior.hpp"
#include "n886_150_rtInferior.hpp"


/// <summary>
/// 千日手タイプの定数（定インスタンス？）の配列☆
/// </summary>
class RepetitionTypeModels {


public:


	/// <summary>
	/// 千日手ではない
	/// </summary>
	static const RepetitionTypeNot m_NOT_REPETETION;

	/// <summary>
	/// 引き分け
	/// </summary>
	static const RepetitionTypeDraw m_DRAW;

	/// <summary>
	/// 勝ち
	/// </summary>
	static const RepetitionTypeWin m_WIN;

	/// <summary>
	/// 負け
	/// </summary>
	static const RepetitionTypeLose m_LOSE;

	/// <summary>
	/// 上の方？
	/// </summary>
	static const RepetitionTypeSuperior m_SUPERIOR;

	/// <summary>
	/// 下の方？
	/// </summary>
	static const RepetitionTypeInferior m_INFERIOR;

	/// <summary>
	/// 配列
	/// </summary>
	static const RepetitionTypeAbstract* m_ARRAY[6];
};


/// <summary>
/// 千日手タイプの一覧。配列含む。
/// </summary>
extern RepetitionTypeModels g_repetitionTypes;
