#include <ostream>
#include "../../header/n680_egOption/n680_245_engineOption.hpp"
#include "../../header/n885_searcher/n885_040_rucksack.hpp"


/// <summary>
///
/// </summary>
/// <param name="v"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(const char* v, Fn* f, Rucksack* s) : EngineOptionable(v, f, s)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(const bool v, Fn* f, Rucksack* s) : EngineOptionable(v, f, s)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(Fn* f, Rucksack* s) : EngineOptionable(f, s)
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
EngineOption::EngineOption(const int v, const int min, const int max, Fn* f, Rucksack* s) : EngineOptionable(v, min, max, f, s)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="os"></param>
/// <param name="om"></param>
/// <returns></returns>
std::ostream& operator << (std::ostream& os, const EngineOptionsMap& om) {
	for (auto& elem : om) {
		const EngineOptionable& o = elem.second;
		os << "\noption name " << elem.first << " type " << o.GetType();
		if (o.GetType() != "button") {
			os << " default " << o.GetDefaultValue();
		}

		if (o.GetType() == "spin") {
			os << " min " << o.GetMin() << " max " << o.GetMax();
		}
	}
	return os;
}

