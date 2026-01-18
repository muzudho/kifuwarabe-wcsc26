#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n680_egOption/n680_230_engineOptionable.hpp"
#include "../n680_egOption/n680_240_engineOptionsMap.hpp"
#include "../n885_searcher/n885_040_ourCarriage.hpp"


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
	void start_50a500b_mainloop(int argc, char* argv[], OurCarriage& searcher);
};