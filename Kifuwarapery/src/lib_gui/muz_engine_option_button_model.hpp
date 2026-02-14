#pragma once
#include "i_muz_engine_optionable_model.hpp"


/// <summary>
/// エンジン・オプション　＞　ボタン
/// </summary>
class MuzEngineOptionButtonModel : public IMuzEngineOptionableModel
{


public:


    /// <summary>
    /// 生成
    /// </summary>
    /// <param name="onChanged"></param>
    MuzEngineOptionButtonModel(
        std::function<void(const IMuzEngineOptionableModel&)> onChanged = nullptr);


    /// <summary>
    /// 代入演算子☆
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    IMuzEngineOptionableModel& operator = (const std::string& v);
};

