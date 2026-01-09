#pragma once


#include "../n119_score___/n119_090_scoreIndex.hpp"
#include "n886_070_rtAbstract.hpp"

#include "../n223_move____/n223_500_flashlight.hpp"// &参照は使えない。*参照は使える。
#include "../n885_searcher/n885_040_rucksack.hpp"


/// <summary>
/// 千日手タイプ：引き分け☆
/// </summary>
class RepetitionTypeDraw : public RepetitionTypeAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isReturn"></param>
	/// <param name="resultScore"></param>
	/// <param name="pSearcher"></param>
	/// <param name="pFlashlightBox"></param>
	void CheckStopAndMaxPly(
		bool& isReturn, ScoreIndex& resultScore, const Rucksack* pSearcher, Flashlight* pFlashlightBox
	) const override {
		isReturn = true;
		resultScore = ScoreDraw;
		return;
	}
};

