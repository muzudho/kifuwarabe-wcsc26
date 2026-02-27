#pragma once
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"// &参照は使えない。*参照は使える。
#include "../../src/n55a_game_engine/muz_game_engine_storage_model.hpp"


/// <summary>
/// 千日手タイプ
/// </summary>
class RepetitionTypeAbstract {


public:


	/// <summary>
	/// 千日手による探索打切りの判断
	/// </summary>
	/// <param name="pSearcher"></param>
	/// <param name="pFlashlightBox"></param>
	virtual std::pair<bool, Sweetness> IsStop(
		const MuzGameEngineStorageModel* pSearcher,
		const Flashlight* pFlashlightBox) const = 0;
};

