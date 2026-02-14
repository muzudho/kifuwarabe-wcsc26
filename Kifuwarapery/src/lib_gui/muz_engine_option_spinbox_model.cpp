#include "muz_engine_option_spinbox_model.hpp"


// ========================================
// 生成／破棄
// ========================================


/// <summary>
///     <pre>
/// 生成☆（＾～＾）
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
MuzEngineOptionSpinboxModel::MuzEngineOptionSpinboxModel(
    const int v,
    const int min,
    const int max,
    std::function<void(const IMuzEngineOptionableModel&)> onChanged)
    : IMuzEngineOptionableModel(v, min, max, onChanged)
{
}


// ========================================
// 生成／破棄
// ========================================


/// <summary>
/// 値のセット☆（＾ｑ＾）
/// </summary>
/// <param name="newValue"></param>
/// <returns></returns>
IMuzEngineOptionableModel& MuzEngineOptionSpinboxModel::operator = (const std::string& newValue)
{
	//assert(!m_type_.empty());

	if (
		newValue.empty()	// ボタンじゃないのに、値が無かった
		|| (atoi(newValue.c_str()) < m_min_ || m_max_ < atoi(newValue.c_str())))	// スピンなのに、値が最小値～最大値の範囲外だった
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
