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
