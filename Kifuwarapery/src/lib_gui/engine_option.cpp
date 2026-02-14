#include <ostream>
#include "engine_option.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"


/// <summary>
///     <pre>
/// テキストボックス用
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
EngineOption::EngineOption(
    const char* v,
    std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> onChanged,
    MuzGameEngineStorageModel* pGameEngineStore) : EngineOptionable(v, onChanged, pGameEngineStore)
{
}


/// <summary>
///     <pre>
/// チェックボックス用
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
EngineOption::EngineOption(
    const bool v,
    std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> onChanged,
    MuzGameEngineStorageModel* pGameEngineStore) : EngineOptionable(v, onChanged, pGameEngineStore)
{
}


/// <summary>
///     <pre>
/// ボタン用
///     </pre>
/// </summary>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
EngineOption::EngineOption(
    std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> onChanged,
    MuzGameEngineStorageModel* pGameEngineStore) : EngineOptionable(onChanged, pGameEngineStore)
{
}


/// <summary>
///     <pre>
/// スピンボックス用
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
EngineOption::EngineOption(
    const int v,
    const int min,
    const int max,
    std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> onChanged,
    MuzGameEngineStorageModel* pGameEngineStore) : EngineOptionable(v, min, max, onChanged, pGameEngineStore)
{
}

