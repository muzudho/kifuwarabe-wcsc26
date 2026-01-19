#pragma once
#include "../n119_score___/n119_090_ScoreValue.hpp"
#include "n886_070_rtAbstract.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"// &参照は使えない。*参照は使える。
#include "../n885_searcher/n885_040_ourCarriage.hpp"


/// <summary>
/// 千日手タイプ：なし
/// </summary>
class RepetitionTypeNot : public RepetitionTypeAbstract {


public:


	/// <summary>
	/// 千日手による探索打切りの判断
	/// </summary>
	/// <param name="isReturn"></param>
	/// <param name="resultScore"></param>
	/// <param name="pSearcher"></param>
	/// <param name="pFlashlightBox"></param>
	std::pair<bool, ScoreValue> IsStop(
		//bool& isReturn,
		//ScoreIndex& resultScore,
		const OurCarriage* pSearcher,
		const Flashlight* pFlashlightBox) const override
	{
		//if (!pSearcher->m_signals.m_stop &&
		//	pFlashlightBox->m_ply <= g_maxPly
		//)
		//{
		//	// XXX: 何もしないの（＾～＾）？
		//}

		return std::make_pair(false, ScoreNone);
	}
};

