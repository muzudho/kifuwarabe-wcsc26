#pragma once
#include "../../src/lib_gui/muz_engine_option_collection_model.hpp"
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
		MuzEngineOptionCollectionModel* pMap,
		std::function<void(const IMuzEngineOptionableModel&)> onHashSizeChanged,
		std::function<void(const IMuzEngineOptionableModel&)> onHashCleared,
		std::function<void(const IMuzEngineOptionableModel&)> onEvalDirChanged,
		std::function<void(const IMuzEngineOptionableModel&)> onMaxThreadsPerSplitPointChanged,
		std::function<void(const IMuzEngineOptionableModel&)> onThreadsChanged,
		std::function<int()> getCPUCoreCount);
};
