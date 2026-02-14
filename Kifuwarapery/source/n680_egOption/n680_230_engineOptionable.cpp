#include <sstream>
#include "../../header/n680_egOption/n680_230_engineOptionable.hpp"
#include "../../src/game_engine_layer/game_engine_storage.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOptionable::EngineOptionable(const char* v, Fn* f, OurCarriage* s) :
	m_type_("string"), m_min_(0), m_max_(0), m_onChange_(f), m_searcher_(s)
{
	m_defaultValue_ = m_currentValue_ = v;
}


/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOptionable::EngineOptionable(const bool v, Fn* f, OurCarriage* s) :
	m_type_("check"), m_min_(0), m_max_(0), m_onChange_(f), m_searcher_(s)
{
	m_defaultValue_ = m_currentValue_ = (v ? "true" : "false");
}


/// <summary>
/// 
/// </summary>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOptionable::EngineOptionable(Fn* f, OurCarriage* s) :
	m_type_("button"), m_min_(0), m_max_(0), m_onChange_(f), m_searcher_(s)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOptionable::EngineOptionable(const int v, const int min, const int max, Fn* f, OurCarriage* s)
	: m_type_("spin"), m_min_(min), m_max_(max), m_onChange_(f), m_searcher_(s)
{
	std::ostringstream ss;
	ss << v;
	m_defaultValue_ = m_currentValue_ = ss.str();
}


/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <returns></returns>
EngineOptionable& EngineOptionable::operator = (const std::string& v) {
	assert(!m_type_.empty());

	if ((m_type_ != "button" && v.empty())
		|| (m_type_ == "check" && v != "true" && v != "false")
		|| (m_type_ == "spin" && (atoi(v.c_str()) < m_min_ || m_max_ < atoi(v.c_str()))))
	{ return *this; }

	if (m_type_ != "button") {
		m_currentValue_ = v;
	}

	if (m_onChange_ != nullptr) {
		(*m_onChange_)(m_searcher_, *this);
	}

	return *this;
}
