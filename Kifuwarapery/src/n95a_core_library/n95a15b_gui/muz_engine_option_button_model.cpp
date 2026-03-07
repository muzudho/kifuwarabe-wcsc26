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
    std::function<void(const MuzEngineOptionAbstractModel&)> onChanged)
    : MuzEngineOptionAbstractModel("button", 0, 0, onChanged)
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
MuzEngineOptionAbstractModel& MuzEngineOptionButtonModel::operator = (const std::string& newValue)
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
    return std::format("type {}", this->GetType());
}
