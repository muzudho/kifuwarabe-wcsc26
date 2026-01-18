#pragma once


#include "../n680_egOption/n680_240_engineOptionsMap.hpp"


class OurCarriage;


/// <summary>
/// エンジン・オプション設定
/// </summary>
class EngineOptionSetup {


public:


	/// <summary>
    /// 最初の設定（初期化）を行うぜ☆（＾▽＾）
	/// </summary>
	/// <param name="pMap"></param>
	/// <param name="s"></param>
	void initialize_10a500b100c( EngineOptionsMap* pMap, OurCarriage* s);
};
