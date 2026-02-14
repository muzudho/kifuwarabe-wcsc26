#include "muz_engine_option_button_model.hpp"


// ========================================
// 生成／破棄
// ========================================


/// <summary>
///     <pre>
/// 生成☆（＾ｑ＾）
///     </pre>
/// </summary>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
MuzEngineOptionButtonModel::MuzEngineOptionButtonModel(
    std::function<void(const IMuzEngineOptionableModel&)> onChanged)
    : IMuzEngineOptionableModel(onChanged)
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
IMuzEngineOptionableModel& MuzEngineOptionButtonModel::operator = (const std::string& newValue)
{
	//assert(!m_type_.empty());

    // ボタンなら、変更通知をする
	m_onChanged_(*this);

	return *this;
}


// ========================================
// その他のメソッド
// ========================================


/// <summary>
/// USIコード化☆（＾～＾）
/// </summary>
/// <returns></returns>
std::string MuzEngineOptionButtonModel::ToUSICode() const
{

#if __cplusplus >= 202002L
    return std::format("type {} default {}", this->GetType(), this->GetDefaultValue());
#else
    std::ostringstream oss;
    oss << "type " << this->GetType() << " default " << this->GetDefaultValue();
    return oss.str();
#endif

}
