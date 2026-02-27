#include "muz_engine_option_textbox_model.hpp"


// ========================================
// 生成／破棄
// ========================================


/// <summary>
///     <pre>
/// 生成☆（＾～＾）
///     </pre>
/// </summary>
/// <param name="v"></param>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
MuzEngineOptionTextboxModel::MuzEngineOptionTextboxModel(
    const std::string text,
    std::function<void(const MuzEngineOptionAbstractModel&)> onChanged)
    : MuzEngineOptionAbstractModel(text, onChanged)
{
}


// ========================================
// 演算子
// ========================================


/// <summary>
/// 値のセット☆（＾ｑ＾）
/// </summary>
/// <param name="newValue"></param>
/// <returns></returns>
MuzEngineOptionAbstractModel& MuzEngineOptionTextboxModel::operator = (const std::string& newValue)
{
	//assert(!m_type_.empty());

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


// ========================================
// その他のメソッド
// ========================================


/// <summary>
/// USIコード化☆（＾～＾）
/// </summary>
/// <returns></returns>
std::string MuzEngineOptionTextboxModel::ToUSICode() const
{
	return std::format("type {} default {}", this->GetType(), this->GetDefaultValue());
}
