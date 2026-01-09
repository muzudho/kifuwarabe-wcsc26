#pragma once


#include "n886_070_rtAbstract.hpp"
#include "n886_100_rtNot.hpp"
#include "n886_110_rtDraw.hpp"
#include "n886_120_rtWin.hpp"
#include "n886_130_rtLose.hpp"
#include "n886_140_rtSuperior.hpp"
#include "n886_150_rtInferior.hpp"


/// <summary>
/// 千日手タイプ配列☆
/// </summary>
class RepetitionTypeArray {


public:


	/// <summary>
	/// 千日手ではない
	/// </summary>
	static const RepetitionTypeNot m_repetitionTypeNot;

	/// <summary>
	/// 引き分け
	/// </summary>
	static const RepetitionTypeDraw m_repetitionTypeDraw;

	/// <summary>
	/// 勝ち
	/// </summary>
	static const RepetitionTypeWin m_repetitionTypeWin;

	/// <summary>
	/// 負け
	/// </summary>
	static const RepetitionTypeLose m_repetitionTypeLose;

	/// <summary>
	/// 上の方？
	/// </summary>
	static const RepetitionTypeSuperior m_repetitionTypeSuperior;

	/// <summary>
	/// 下の方？
	/// </summary>
	static const RepetitionTypeInferior m_repetitionTypeInferior;

	/// <summary>
	/// 配列
	/// </summary>
	static const RepetitionTypeAbstract* m_repetitionTypeArray[6];
};


/// <summary>
/// 
/// </summary>
extern RepetitionTypeArray g_repetitionTypeArray;
