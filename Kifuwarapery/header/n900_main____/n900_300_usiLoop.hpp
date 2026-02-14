#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../../src/lib_gui/engine_optionable.hpp"
#include "../n680_egOption/n680_240_engineOptionsMap.hpp"
#include "../../src/layer_game_engine/game_engine_storage.hpp"


/// <summary>
/// USIプロトコルのループ☆（＾ｑ＾）
/// </summary>
class UsiLoop {
public:


	/// <summary>
	/// ループ開始（＾▽＾）
	/// </summary>
	UsiLoop();


	/// <summary>
    /// メインループ☆（＾ｑ＾）
	/// </summary>
	/// <param name="argc"></param>
	/// <param name="argv"></param>
	/// <param name="m_ourCarriage"></param>
	void mainloop_50a500b(int argc, char* argv[], GameEngineStorageOurCarriage& m_ourCarriage);
};