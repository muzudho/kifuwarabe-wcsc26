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
/// エンジン・オプションのマップ☆（＾～＾）
/// 
/// FIXME: マップを継承するのではなく、マップをメンバーに持つべきかもしれない☆（＾～＾）
///		</pre>
/// </summary>
struct EngineOptionsMap : public std::map<std::string, EngineOptionable, CaseInsensitiveLess> {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	bool IsLegalOption(const std::string name) {
		return this->find(name) != std::end(*this);
	}


	/// <summary>
	/// エンジン・オプションを登録するぜ☆（＾～＾）
	/// </summary>
	/// <param name="key"></param>
	/// <param name="option"></param>
	void Put(const std::string key, EngineOptionable option);
};
