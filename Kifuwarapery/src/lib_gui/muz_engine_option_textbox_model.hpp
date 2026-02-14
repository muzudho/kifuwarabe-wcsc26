#pragma once
#include "muz_engine_optionable_model.hpp"


/// <summary>
/// エンジン・オプション　＞　テキストボックス
/// </summary>
class MuzEngineOptionTextboxModel : public MuzEngineOptionableModel
{


public:


    /// <summary>
    /// テキストボックス用
    /// </summary>
    /// <returns></returns>
    MuzEngineOptionTextboxModel(
        const char* v, std::function<void(const MuzEngineOptionableModel&)> onChanged = nullptr);


    /// <summary>
    /// 代入演算子☆
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    MuzEngineOptionableModel& operator = (const std::string& v);

};

