#include <sstream>
#include "engine_optionable.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="f"></param>
/// <param name="pGameEngineStore"></param>
EngineOptionable::EngineOptionable(
	const char* v,
	std::function<void(const EngineOptionable&)> f,
	MuzGameEngineStorageModel* pGameEngineStore)
		: m_type_("string"), m_min_(0), m_max_(0), m_onChange_(f), m_pGameEngineStore_(pGameEngineStore)
{
	m_defaultValue_ = m_currentValue_ = v;
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="f"></param>
/// <param name="pGameEngineStore"></param>
EngineOptionable::EngineOptionable(
	const bool v,
	std::function<void(const EngineOptionable&)> f,
	MuzGameEngineStorageModel* pGameEngineStore)
		: m_type_("check"), m_min_(0), m_max_(0), m_onChange_(f), m_pGameEngineStore_(pGameEngineStore)
{
	m_defaultValue_ = m_currentValue_ = (v ? "true" : "false");
}


/// <summary>
/// 
/// </summary>
/// <param name="f"></param>
/// <param name="pGameEngineStore"></param>
EngineOptionable::EngineOptionable(
	std::function<void(const EngineOptionable&)> f,
	MuzGameEngineStorageModel* pGameEngineStore)
		: m_type_("button"), m_min_(0), m_max_(0), m_onChange_(f), m_pGameEngineStore_(pGameEngineStore)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="newValue"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <param name="f"></param>
/// <param name="pGameEngineStore"></param>
EngineOptionable::EngineOptionable(
	const int v,
	const int min,
	const int max,
	std::function<void(const EngineOptionable&)> f,
	MuzGameEngineStorageModel* pGameEngineStore)
		: m_type_("spin"), m_min_(min), m_max_(max), m_onChange_(f), m_pGameEngineStore_(pGameEngineStore)
{
	std::ostringstream ss;
	ss << v;
	m_defaultValue_ = m_currentValue_ = ss.str();
}


/// <summary>
/// 値のセット、またはボタンの押下☆（＾ｑ＾）
/// </summary>
/// <param name="newValue"></param>
/// <returns></returns>
EngineOptionable& EngineOptionable::operator = (const std::string& newValue)
{
	assert(!m_type_.empty());

	if (
		(m_type_ != "button" && newValue.empty())	// 値が無いのに、ボタンじゃなかった
        || (m_type_ == "check" && newValue != "true" && newValue != "false")	// チェックボックスなのに、値が "true" でも "false" でもなかった
        || (m_type_ == "spin" && (atoi(newValue.c_str()) < m_min_ || m_max_ < atoi(newValue.c_str()))))	// スピンなのに、値が最小値～最大値の範囲外だった
	{ return *this; }

    bool isDirty = false;

	// ボタンなら
	if (m_type_ == "button")
	{
        isDirty = true;
	}
	// （ボタンじゃなければ）値の更新
	else
	{
		m_currentValue_ = newValue;
        isDirty = m_currentValue_ != newValue;	// 変更前の値と変更後の値が違うときだけ、変更通知を呼び出すようにするぜ☆（＾ｑ＾）
	}

	// 変更通知、またはボタン押下の通知
    // FIXME: 変更前の値、変更後の値を渡すようにするか（＾～＾）？
	if (isDirty && m_onChange_ != nullptr) {
		m_onChange_(*this);
	}

	return *this;
}
