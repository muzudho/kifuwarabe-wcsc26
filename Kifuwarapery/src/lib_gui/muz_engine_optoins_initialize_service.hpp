#pragma once


#include "../../src/lib_gui/engine_option_collection.hpp"


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
		EngineOptionable::Fn* pHandleHashSizeChanged,
		EngineOptionable::Fn* pHandleHashCleared,
		EngineOptionable::Fn* pHandleEvalDirChanged,
		EngineOptionable::Fn* pMaxThreadsPerSplitPointChanged,
		EngineOptionable::Fn* pHandleThreadsChanged,
		EngineOptionable::FnVoidInt* pGetCpuCoreCount);
};
