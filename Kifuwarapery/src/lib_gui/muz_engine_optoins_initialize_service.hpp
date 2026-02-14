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
		int max_legal_moves,
		int sweetnessInfinite,
		int sweetnessMate0Ply,
		int maxThreads,
		EngineOptionCollection* pMap,
		std::function<void(const EngineOptionable&)> onHashSizeChanged,
		std::function<void(const EngineOptionable&)> onHashCleared,
		std::function<void(const EngineOptionable&)> onEvalDirChanged,
		std::function<void(const EngineOptionable&)> onMaxThreadsPerSplitPointChanged,
		std::function<void(const EngineOptionable&)> onThreadsChanged,
		std::function<int()> getCPUCoreCount);
};
