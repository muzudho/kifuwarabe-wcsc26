#include "muz_engine_optionable_model.hpp"
#include <sstream>


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="onChanged"></param>
MuzEngineOptionableModel::MuzEngineOptionableModel(
	const char* v,
	std::function<void(const MuzEngineOptionableModel&)> onChanged)
		: m_type_("string"), m_min_(0), m_max_(0), m_onChanged_(onChanged)
{
	m_defaultValue_ = m_currentValue_ = v;
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="f"></param>
MuzEngineOptionableModel::MuzEngineOptionableModel(
	const bool v,
	std::function<void(const MuzEngineOptionableModel&)> onChanged)
		: m_type_("check"), m_min_(0), m_max_(0), m_onChanged_(onChanged)
{
	m_defaultValue_ = m_currentValue_ = (v ? "true" : "false");
}


/// <summary>
/// 
/// </summary>
/// <param name="onChanged"></param>
/// <param name="pGameEngineStore"></param>
MuzEngineOptionableModel::MuzEngineOptionableModel(
	std::function<void(const MuzEngineOptionableModel&)> onChanged)
		: m_type_("button"), m_min_(0), m_max_(0), m_onChanged_(onChanged)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <param name="onChanged"></param>
MuzEngineOptionableModel::MuzEngineOptionableModel(
	const int v,
	const int min,
	const int max,
	std::function<void(const MuzEngineOptionableModel&)> onChanged)
		: m_type_("spin"), m_min_(min), m_max_(max), m_onChanged_(onChanged)
{
	std::ostringstream ss;
	ss << v;
	m_defaultValue_ = m_currentValue_ = ss.str();
}


/// <summary>
/// 値のセット☆（＾ｑ＾）
/// </summary>
/// <param name="newValue"></param>
/// <returns></returns>
MuzEngineOptionableModel& MuzEngineOptionableModel::operator = (const std::string& newValue)
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
