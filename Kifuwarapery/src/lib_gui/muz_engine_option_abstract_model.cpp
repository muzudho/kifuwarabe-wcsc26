#include "muz_engine_option_abstract_model.hpp"
#include <sstream>


// ========================================
// 生成／破棄
// ========================================


/// <summary>
/// TODO: 汎用に作った（＾～＾）
/// </summary>
/// <param name="onChanged"></param>
MuzEngineOptionAbstractModel::MuzEngineOptionAbstractModel(
	std::string type,
	int min,
	int max,
	std::function<void(const MuzEngineOptionAbstractModel&)> onChanged)
	: m_type_(type), m_min_(min), m_max_(max), m_onChanged_(onChanged)
{
}


/// <summary>
/// XXX: これを消すとコンパイルエラー。匿名関数で使ってる（＾～＾）？
/// </summary>
/// <param name="onChanged"></param>
MuzEngineOptionAbstractModel::MuzEngineOptionAbstractModel(
	std::function<void(const MuzEngineOptionAbstractModel&)> onChanged)
	: m_type_("button"), m_min_(0), m_max_(0), m_onChanged_(onChanged)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="onChanged"></param>
MuzEngineOptionAbstractModel::MuzEngineOptionAbstractModel(
	const char* v,
	std::function<void(const MuzEngineOptionAbstractModel&)> onChanged)
		: m_type_("string"), m_min_(0), m_max_(0), m_onChanged_(onChanged)
{
	m_defaultValue_ = m_currentValue_ = v;
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="f"></param>
MuzEngineOptionAbstractModel::MuzEngineOptionAbstractModel(
	const bool v,
	std::function<void(const MuzEngineOptionAbstractModel&)> onChanged)
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
MuzEngineOptionAbstractModel::MuzEngineOptionAbstractModel(
	const int v,
	const int min,
	const int max,
	std::function<void(const MuzEngineOptionAbstractModel&)> onChanged)
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
MuzEngineOptionAbstractModel& MuzEngineOptionAbstractModel::operator = (const std::string& newValue)
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
std::string MuzEngineOptionAbstractModel::ToUSICode() const
{
	return "";
}
