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
/// <param name="engineSettings"></param>
/// <returns></returns>
std::ostream& operator << (std::ostream& os, const MuzEngineSettingsModel& engineSettings) {
	for (auto& elem : engineSettings.m_map) {
		const MuzEngineOptionAbstractModel& option = elem.second;
		os << "\noption name " << elem.first << " " << option.ToUSICode();
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
void MuzEngineSettingsModel::Put(const std::string key, MuzEngineOptionAbstractModel option)
{
	(this->m_map)[key] = option;
}
