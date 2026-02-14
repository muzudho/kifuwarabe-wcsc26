#include "i_muz_engine_optionable_model.hpp"
#include <sstream>


// ========================================
// 生成／破棄
// ========================================


/// <summary>
/// TODO: 汎用
/// </summary>
/// <param name="onChanged"></param>
IMuzEngineOptionableModel::IMuzEngineOptionableModel(
	std::string type,
	int min,
	int max,
	std::function<void(const IMuzEngineOptionableModel&)> onChanged)
	: m_type_(type), m_min_(min), m_max_(max), m_onChanged_(onChanged)
{
}


/// <summary>
/// XXX: これを消すとコンパイルエラー
/// </summary>
/// <param name="onChanged"></param>
IMuzEngineOptionableModel::IMuzEngineOptionableModel(
	std::function<void(const IMuzEngineOptionableModel&)> onChanged)
	: m_type_("button"), m_min_(0), m_max_(0), m_onChanged_(onChanged)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="onChanged"></param>
IMuzEngineOptionableModel::IMuzEngineOptionableModel(
	const char* v,
	std::function<void(const IMuzEngineOptionableModel&)> onChanged)
		: m_type_("string"), m_min_(0), m_max_(0), m_onChanged_(onChanged)
{
	m_defaultValue_ = m_currentValue_ = v;
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="f"></param>
IMuzEngineOptionableModel::IMuzEngineOptionableModel(
	const bool v,
	std::function<void(const IMuzEngineOptionableModel&)> onChanged)
		: m_type_("check"), m_min_(0), m_max_(0), m_onChanged_(onChanged)
{
	m_defaultValue_ = m_currentValue_ = (v ? "true" : "false");
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <param name="onChanged"></param>
IMuzEngineOptionableModel::IMuzEngineOptionableModel(
	const int v,
	const int min,
	const int max,
	std::function<void(const IMuzEngineOptionableModel&)> onChanged)
		: m_type_("spin"), m_min_(min), m_max_(max), m_onChanged_(onChanged)
{
	std::ostringstream ss;
	ss << v;
	m_defaultValue_ = m_currentValue_ = ss.str();
}


// ========================================
// 演算子
// ========================================


/// <summary>
/// 値のセット☆（＾ｑ＾）
/// </summary>
/// <param name="newValue"></param>
/// <returns></returns>
IMuzEngineOptionableModel& IMuzEngineOptionableModel::operator = (const std::string& newValue)
{
	if (newValue.empty()) { return *this; }	// 値が無かった

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
std::string IMuzEngineOptionableModel::ToUSICode() const
{
	return "";
}
