#pragma once
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../../src/game_engine_layer/game_engine_storage.hpp"
#include "n886_070_rtAbstract.hpp" // &参照は使えない。*参照は使える。


/// <summary>
/// 千日手タイプ
/// </summary>
class RepetitionTypeInferior : public RepetitionTypeAbstract {


public:


	/// <summary>
	/// 千日手による探索打切りの判断
	/// </summary>
	/// <param name="pSearcher"></param>
	/// <param name="pFlashlightBox"></param>
	std::pair<bool, Sweetness> IsStop(
		const OurCarriage* pSearcher,
		const Flashlight* pFlashlightBox) const override
	{
		if (pFlashlightBox->m_ply != 2) {
			return std::make_pair(true, SweetnessMatedInMaxPly);
		}

		return std::make_pair(false, SweetnessNone);
	}
};

