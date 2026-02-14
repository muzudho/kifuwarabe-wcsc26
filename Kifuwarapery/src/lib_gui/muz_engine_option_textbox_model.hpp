#pragma once
#include "i_muz_engine_optionable_model.hpp"


/// <summary>
/// エンジン・オプション　＞　テキストボックス
/// </summary>
class MuzEngineOptionTextboxModel : public IMuzEngineOptionableModel
{


public:


    /// <summary>
    /// テキストボックス用
    /// </summary>
    /// <returns></returns>
    MuzEngineOptionTextboxModel(
        const char* v, std::function<void(const IMuzEngineOptionableModel&)> onChanged = nullptr);


    /// <summary>
    /// 代入演算子☆
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    IMuzEngineOptionableModel& operator = (const std::string& v);

};

