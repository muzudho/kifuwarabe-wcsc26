#pragma once
#include "muz_engine_optionable_model.hpp"


/// <summary>
/// エンジン・オプション　＞　チェックボックス
/// </summary>
class MuzEngineOptionCheckboxModel : public MuzEngineOptionableModel
{


public:


	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="v"></param>
	/// <param name="onChanged"></param>
	MuzEngineOptionCheckboxModel(
		const bool  v,
		std::function<void(const MuzEngineOptionableModel&)> onChanged = nullptr);


	/// <summary>
	/// 代入演算子☆
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	MuzEngineOptionableModel& operator = (const std::string& v);


};

