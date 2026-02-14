#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n680_egOption/n680_230_engineOptionable.hpp"
#include "../n680_egOption/n680_240_engineOptionsMap.hpp"
#include "../../src/game_engine_layer/game_engine_storage.hpp"


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
	/// <param name="searcher"></param>
	void mainloop_50a500b(int argc, char* argv[], OurCarriage& searcher);
};