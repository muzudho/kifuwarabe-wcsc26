#include "muz_engine_option_textbox_model.hpp"


/// <summary>
///     <pre>
/// 生成
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
MuzEngineOptionTextboxModel::MuzEngineOptionTextboxModel(
    const char* v,
    std::function<void(const MuzEngineOptionableModel&)> onChanged)
    : MuzEngineOptionableModel(v, onChanged)
{
}


/// <summary>
/// 値のセット☆（＾ｑ＾）
/// </summary>
/// <param name="newValue"></param>
/// <returns></returns>
MuzEngineOptionableModel& MuzEngineOptionTextboxModel::operator = (const std::string& newValue)
{
	assert(!m_type_.empty());

	if (
		newValue.empty())	// ボタンじゃないのに、値が無かった
	{
		return *this;
	}

	// 値の更新
	m_currentValue_ = newValue;
	auto isDirty = m_currentValue_ != newValue;	// 変更前の値と変更後の値が違うときだけ、変更通知を呼び出すようにするぜ☆（＾ｑ＾）

	// 変更通知
	if (isDirty && m_onChanged_ != nullptr) {
		m_onChanged_(*this);
	}

	return *this;
}
