#pragma once
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "n886_070_rtAbstract.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"// &参照は使えない。*参照は使える。
#include "../../src/n55a_game_engine/muz_game_engine_storage_model.hpp"


/// <summary>
/// 千日手タイプ：なし
/// </summary>
class RepetitionTypeNot : public RepetitionTypeAbstract {


public:


	/// <summary>
	/// 千日手による探索打切りの判断
	/// </summary>
	/// <param name="pSearcher"></param>
	/// <param name="pFlashlightBox"></param>
	std::pair<bool, Sweetness> IsStop(
		const MuzGameEngineStorageModel* pSearcher,
		const Flashlight* pFlashlightBox) const override
	{
		//if (!pSearcher->m_signals.m_stop &&
		//	pFlashlightBox->m_ply <= g_maxPly
		//)
		//{
		//	// XXX: 何もしないの（＾～＾）？
		//}

		return std::make_pair(false, SweetnessNone);
	}
};

