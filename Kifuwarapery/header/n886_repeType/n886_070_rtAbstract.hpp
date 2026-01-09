#pragma once


#include "../n119_score___/n119_090_scoreIndex.hpp"

#include "../n223_move____/n223_500_flashlight.hpp"// &参照は使えない。*参照は使える。
#include "../n885_searcher/n885_040_rucksack.hpp"


/// <summary>
/// 千日手タイプ
/// </summary>
class RepetitionTypeAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isReturn"></param>
	/// <param name="resultScore"></param>
	/// <param name="pSearcher"></param>
	/// <param name="pFlashlightBox"></param>
	virtual void CheckStopAndMaxPly(
		bool& isReturn, ScoreIndex& resultScore, const Rucksack* pSearcher, Flashlight* pFlashlightBox) const = 0;
};

