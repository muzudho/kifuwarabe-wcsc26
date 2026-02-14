#pragma once
#include <map>
#include <string>
#include "../../src/lib_gui/engine_optionable.hpp"


/// <summary>
/// ２つの文字列の並び順の比較☆（＾～＾）
/// </summary>
struct CaseInsensitiveLess {
	bool operator() (const std::string&, const std::string&) const;
};


/// <summary>
///		<pre>
/// エンジン・オプションのコレクション☆（＾～＾）
///		</pre>
/// </summary>
struct EngineOptionCollection {


public:


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
	void Put(const std::string key, EngineOptionable option);


    /// <summary>
    /// オプションのマップ☆（＾～＾）
    /// </summary>
    std::map<std::string, EngineOptionable, CaseInsensitiveLess> m_map;


	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	friend std::ostream& operator << (std::ostream&, const EngineOptionCollection&);
};
