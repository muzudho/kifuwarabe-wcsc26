#pragma once
#include "../../src/lib_gui/engine_option_collection.hpp"
#include <functional>


class MuzGameEngineStorageModel;


/// <summary>
/// エンジン・オプション設定
/// </summary>
class MuzEngineOptionsInitializeService {


public:


	/// <summary>
    /// 最初の設定（初期化）を行うぜ☆（＾▽＾）
	/// </summary>
	/// <param name="pMap"></param>
	/// <param name="s"></param>
	void initialize_10a510b_engineOptions(
		EngineOptionCollection* pMap,
		MuzGameEngineStorageModel* s,
		std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> pHandleHashSizeChanged,
		std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> pHandleHashCleared,
		std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> pHandleEvalDirChanged,
		std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> pMaxThreadsPerSplitPointChanged,
		std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> pHandleThreadsChanged,
		EngineOptionable::FnVoidInt* pGetCpuCoreCount);
};
