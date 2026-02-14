#pragma once
#include "i_muz_engine_optionable_model.hpp"


/// <summary>
/// エンジン・オプション　＞　チェックボックス
/// </summary>
class MuzEngineOptionCheckboxModel : public IMuzEngineOptionableModel
{


public:


	// ========================================
	// 生成／破棄
	// ========================================


	/// <summary>
    /// 生成☆（＾ｑ＾）
	/// </summary>
	/// <param name="v"></param>
	/// <param name="onChanged"></param>
	MuzEngineOptionCheckboxModel(
		const bool  v,
		std::function<void(const IMuzEngineOptionableModel&)> onChanged = nullptr);


	// ========================================
	// 生成／破棄
	// ========================================


	/// <summary>
	/// 代入演算子☆
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	IMuzEngineOptionableModel& operator = (const std::string& v);


};

