#pragma once
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../src/lib_gui/engine_optionable.hpp"
#include "../../src/lib_gui/engine_option_collection.hpp"


class GameEngineStorageOurCarriage;


/// <summary>
///		<pre>
/// エンジン・オプション☆（＾～＾）
///		</pre
/// </summary>
class EngineOption : public EngineOptionable {


public:


	EngineOption(Fn* = nullptr, GameEngineStorageOurCarriage* s = nullptr);
	EngineOption(const char* v, Fn* = nullptr, GameEngineStorageOurCarriage* s = nullptr);
	EngineOption(const bool  v, Fn* = nullptr, GameEngineStorageOurCarriage* s = nullptr);
	EngineOption(const int   v, const int min, const int max, Fn* = nullptr, GameEngineStorageOurCarriage* s = nullptr);


//private:
	

};
