#include <ostream>
#include "engine_option.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"


/// <summary>
///     <pre>
/// テキストボックス用
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(const char* v, Fn* f, MuzGameEngineStorageModel* s) : EngineOptionable(v, f, s)
{
}


/// <summary>
///     <pre>
/// チェックボックス用
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(const bool v, Fn* f, MuzGameEngineStorageModel* s) : EngineOptionable(v, f, s)
{
}


/// <summary>
///     <pre>
/// ボタン用
///     </pre>
/// </summary>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(Fn* f, MuzGameEngineStorageModel* s) : EngineOptionable(f, s)
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
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(const int v, const int min, const int max, Fn* f, MuzGameEngineStorageModel* s) : EngineOptionable(v, min, max, f, s)
{
}

