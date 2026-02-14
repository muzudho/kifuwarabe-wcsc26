#pragma once

#include <map>
#include <string>
#include "../../src/lib_gui/engine_optionable.hpp"


/// <summary>
/// 
/// </summary>
struct CaseInsensitiveLess {
	bool operator() (const std::string&, const std::string&) const;
};


/// <summary>
/// 
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
	/// 
	/// </summary>
	/// <param name="key"></param>
	/// <param name="value"></param>
	void Put(const std::string key, EngineOptionable value);
};
