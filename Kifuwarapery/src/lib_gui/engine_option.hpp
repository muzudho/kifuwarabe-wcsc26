#pragma once
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../src/lib_gui/engine_optionable.hpp"
#include "../../src/lib_gui/engine_option_collection.hpp"


class MuzGameEngineStorageModel;


/// <summary>
///		<pre>
/// エンジン・オプション☆（＾～＾）
///		</pre
/// </summary>
class EngineOption : public EngineOptionable {


public:


	EngineOption(std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> = nullptr, MuzGameEngineStorageModel* s = nullptr);
	EngineOption(const char* v, std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> = nullptr, MuzGameEngineStorageModel* s = nullptr);
	EngineOption(const bool  v, std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> = nullptr, MuzGameEngineStorageModel* s = nullptr);
	EngineOption(const int   v, const int min, const int max, std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> = nullptr, MuzGameEngineStorageModel* s = nullptr);


//private:
	

};
