#include "muz_engine_option_button_model.hpp"


/// <summary>
///     <pre>
/// ボタン用
///     </pre>
/// </summary>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
MuzEngineOptionButtonModel::MuzEngineOptionButtonModel(
    std::function<void(const MuzEngineOptionableModel&)> onChanged)
    : MuzEngineOptionableModel(onChanged)
{
}


/// <summary>
/// 値のセット、またはボタンの押下☆（＾ｑ＾）
/// </summary>
/// <param name="newValue"></param>
/// <returns></returns>
MuzEngineOptionableModel& MuzEngineOptionButtonModel::operator = (const std::string& newValue)
{
	assert(!m_type_.empty());

    // ボタンなら、変更通知をする
	m_onChanged_(*this);

	return *this;
}
