#pragma once
#include "muz_engine_optionable_model.hpp"


/// <summary>
/// エンジン・オプション　＞　ボタン
/// </summary>
class MuzEngineOptionButtonModel : public MuzEngineOptionableModel
{


public:


    /// <summary>
    /// 生成
    /// </summary>
    /// <param name="onChanged"></param>
    MuzEngineOptionButtonModel(
        std::function<void(const MuzEngineOptionableModel&)> onChanged = nullptr);


    /// <summary>
    /// 代入演算子☆
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    MuzEngineOptionableModel& operator = (const std::string& v);
};

