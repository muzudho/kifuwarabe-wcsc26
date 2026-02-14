#pragma once
#include <map>
#include <string>
#include "muz_engine_option_abstract_model.hpp"
#include <ostream>      // std::ostream のため（普通は iostream で入ってる）


/// <summary>
/// ２つの文字列の並び順の比較☆（＾～＾）
/// </summary>
struct MuzCaseInsensitiveLessModel {
	bool operator() (const std::string&, const std::string&) const;
};


/// <summary>
///		<pre>
/// エンジン・オプションのコレクション☆（＾～＾）
///		</pre>
/// </summary>
struct MuzEngineSettingsModel {


public:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// オプションのマップ☆（＾～＾）
	/// </summary>
	std::map<std::string, MuzEngineOptionAbstractModel, MuzCaseInsensitiveLessModel> m_map;


	// ========================================
	// 演算子
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	friend std::ostream& operator << (std::ostream&, const MuzEngineSettingsModel&);


	// ========================================
	// メソッド
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	bool IsLegalOption(const std::string name) {
		//return this->find(name) != std::end(*this);
		return this->m_map.find(name) != std::end(this->m_map);
	}


	/// <summary>
	/// エンジン・オプションを登録するぜ☆（＾～＾）
	/// </summary>
	/// <param name="key"></param>
	/// <param name="option"></param>
	void Put(const std::string key, MuzEngineOptionAbstractModel option);


	/// <summary>
	/// エンジン・オプション取得☆（＾～＾）
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	MuzEngineOptionAbstractModel& GetOption(const std::string key) {
		return this->m_map[key];
    }


	std::vector<std::string> GetAllOptionKeys() const
	{
		std::vector<std::string> keys;
		keys.reserve(this->m_map.size());  // パフォーマンスのため（任意）

		for (const auto& pair : this->m_map) {
			keys.push_back(pair.first);
		}

		return keys;
	}
};
