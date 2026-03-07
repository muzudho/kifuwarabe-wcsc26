#pragma once
#include <map>
#include <string>
#include "muz_engine_option_abstract_model.hpp"
#include "muz_engine_option_textbox_model.hpp"
#include <ostream>      // std::ostream のため（普通は iostream で入ってる）
#include <vector>
#include <map>


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
	std::map<std::string, std::unique_ptr<MuzEngineOptionAbstractModel>, MuzCaseInsensitiveLessModel> m_mapUnique; // XXX: 勉強中


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
	const MuzEngineOptionAbstractModel& GetOptionByKey(const std::string key) const
	{
        // first はキー、second は値。例外は投げない。
        return this->m_map.find(key)->second;
		//return this->m_map.at(key);	// 例外を投げる
    }
	// XXX: 勉強中
	MuzEngineOptionAbstractModel& GetOptionUniqueByKey(const std::string& key) const
	{
		auto it = this->m_mapUnique.find(key);
		return *it->second;
	}


	std::vector<std::string> GetAllOptionKeys() const
	{
		std::vector<std::string> keys;
		keys.reserve(this->m_map.size());  // パフォーマンスのため（任意）

		for (const auto& [key, _] : this->m_map) {
			keys.push_back(key);
		}

		return keys;
	}


	/// <summary>
	/// テキストボックス型のエンジン・オプション設定☆（＾～＾）
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	void SetTextboxOption(const std::string key, std::string text)
	{
		this->m_map[key] = new MuzEngineOptionTextboxModel(text);
	}
};
