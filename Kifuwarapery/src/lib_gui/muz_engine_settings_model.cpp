#include "muz_engine_settings_model.hpp"


// ========================================
// 演算子
// ========================================


/// <summary>
/// ２つの文字列の並び順の比較☆（＾～＾）
/// </summary>
/// <param name="s1"></param>
/// <param name="s2"></param>
/// <returns></returns>
bool MuzCaseInsensitiveLessModel::operator () (const std::string& s1, const std::string& s2) const {
	for (size_t i = 0; i < s1.size() && i < s2.size(); ++i) {
		const int c1 = tolower(s1[i]);
		const int c2 = tolower(s2[i]);

		if (c1 != c2) { return c1 < c2; }
	}

	return s1.size() < s2.size();
}


/// <summary>
/// 演算子
/// </summary>
/// <param name="os"></param>
/// <param name="engineOptionCollection"></param>
/// <returns></returns>
std::ostream& operator << (std::ostream& os, const MuzEngineSettingsModel& engineOptionCollection) {
	for (auto& elem : engineOptionCollection.m_map) {
		const IMuzEngineOptionableModel& option = elem.second;
		os << "\noption name " << elem.first << " type " << option.GetType();
		if (option.GetType() != "button") {
			os << " default " << option.GetDefaultValue();
		}


		//os << "\noption name " << elem.first;
		//
		//if (option.GetType() != "button") {
		//	os << " " << option.ToUSICode();
		//}
		//else {
		//	os << " type " << option.GetType();
		//}



		if (option.GetType() == "spin") {
			os << " min " << option.GetMin() << " max " << option.GetMax();
		}
	}
	return os;
}


// ========================================
// メソッド
// ========================================


/// <summary>
/// エンジン・オプションを登録するぜ☆（＾～＾）
/// </summary>
/// <param name="key"></param>
/// <param name="option"></param>
void MuzEngineSettingsModel::Put(const std::string key, IMuzEngineOptionableModel option)
{
	(this->m_map)[key] = option;
}
