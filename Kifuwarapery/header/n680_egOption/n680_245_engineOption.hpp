#pragma once

#include "../../header/n080_common__/n080_100_common.hpp"
#include "../../header/n680_egOption/n680_230_engineOptionable.hpp"
#include "../../header/n680_egOption/n680_240_engineOptionsMap.hpp"


class Rucksack;


/// <summary>
/// エンジン・オプション☆
/// </summary>
class EngineOption : public EngineOptionable {


public:


	EngineOption(Fn* = nullptr, Rucksack* s = nullptr);
	EngineOption(const char* v, Fn* = nullptr, Rucksack* s = nullptr);
	EngineOption(const bool  v, Fn* = nullptr, Rucksack* s = nullptr);
	EngineOption(const int   v, const int min, const int max, Fn* = nullptr, Rucksack* s = nullptr);


//private:
	

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	friend std::ostream& operator << (std::ostream&, const EngineOptionsMap&);
};
