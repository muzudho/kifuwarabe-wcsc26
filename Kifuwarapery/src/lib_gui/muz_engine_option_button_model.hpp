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
    /// <returns></returns>
    MuzEngineOptionButtonModel(
        std::function<void(const MuzEngineOptionableModel&)> onChanged = nullptr);

};

