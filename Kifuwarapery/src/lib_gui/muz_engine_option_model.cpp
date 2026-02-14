#include "muz_engine_option_model.hpp"


/// <summary>
///     <pre>
/// テキストボックス用
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
MuzEngineOptionModel::MuzEngineOptionModel(
    const char* v,
    std::function<void(const MuzEngineOptionableModel&)> onChanged)
    : MuzEngineOptionableModel(v, onChanged)
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
MuzEngineOptionModel::MuzEngineOptionModel(
    const bool v,
    std::function<void(const MuzEngineOptionableModel&)> onChanged)
    : MuzEngineOptionableModel(v, onChanged)
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
MuzEngineOptionModel::MuzEngineOptionModel(
    const int v,
    const int min,
    const int max,
    std::function<void(const MuzEngineOptionableModel&)> onChanged)
    : MuzEngineOptionableModel(v, min, max, onChanged)
{
}

