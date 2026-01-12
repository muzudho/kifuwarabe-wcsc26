#pragma once
#include "../n119_score___/n119_090_scoreIndex.hpp"
#include "../n119_score___/n119_100_utilScore.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"// &参照は使えない。*参照は使える。
#include "../n885_searcher/n885_040_ourCarriage.hpp"
#include "n886_070_rtAbstract.hpp"


/// <summary>
/// 千日手タイプ：負け
/// </summary>
class RepetitionTypeLose : public RepetitionTypeAbstract {


public:


	/// <summary>
	/// 停止の判断
	/// </summary>
	/// <param name="isReturn"></param>
	/// <param name="resultScore"></param>
	/// <param name="pSearcher"></param>
	/// <param name="pFlashlightBox"></param>
	void IsStop(
		bool& isReturn,
		ScoreIndex& resultScore,
		const OurCarriage* pSearcher,
		const Flashlight* pFlashlightBox) const override
	{
		isReturn = true;
		resultScore = UtilScore::MatedIn(pFlashlightBox->m_ply);
	}
};

