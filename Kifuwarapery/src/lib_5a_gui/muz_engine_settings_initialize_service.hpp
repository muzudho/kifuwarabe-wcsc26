#pragma once
#include "muz_engine_settings_model.hpp"
#include <functional>


class MuzGameEngineStorageModel;


/// <summary>
/// エンジン設定
/// </summary>
class MuzEngineSettingsInitializeService {


public:


	// ========================================
	// イベントハンドラ
	// ========================================


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
		MuzEngineSettingsModel* pMap,
		std::function<void(const MuzEngineOptionAbstractModel&)> onHashSizeChanged,
		std::function<void(const MuzEngineOptionAbstractModel&)> onHashCleared,
		std::function<void(const MuzEngineOptionAbstractModel&)> onEvalDirChanged,
		std::function<void(const MuzEngineOptionAbstractModel&)> onMaxThreadsPerSplitPointChanged,
		std::function<void(const MuzEngineOptionAbstractModel&)> onThreadsChanged,
		std::function<int()> getCPUCoreCount);
};
