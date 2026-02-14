#include <string>
#include "../../header/n680_egOption/n680_240_engineOptionsMap.hpp"


/// <summary>
/// ２つの文字列の並び順の比較☆（＾～＾）
/// </summary>
/// <param name="s1"></param>
/// <param name="s2"></param>
/// <returns></returns>
bool CaseInsensitiveLess::operator () (const std::string& s1, const std::string& s2) const {
	for (size_t i = 0; i < s1.size() && i < s2.size(); ++i) {
		const int c1 = tolower(s1[i]);
		const int c2 = tolower(s2[i]);

		if (c1 != c2) { return c1 < c2; }
	}

	return s1.size() < s2.size();
}


/// <summary>
/// エンジン・オプションを登録するぜ☆（＾～＾）
/// </summary>
/// <param name="key"></param>
/// <param name="option"></param>
void EngineOptionsMap::Put(const std::string key, EngineOptionable option)
{
	(this->m_map)[key] = option;
}


/// <summary>
/// 
/// </summary>
/// <param name="os"></param>
/// <param name="engineOptionCollection"></param>
/// <returns></returns>
std::ostream& operator << (std::ostream& os, const EngineOptionsMap& engineOptionCollection) {
	for (auto& elem : engineOptionCollection.m_map) {
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
