#pragma once
#include "i_muz_engine_optionable_model.hpp"


/// <summary>
/// エンジン・オプション　＞　スピンボックス
/// </summary>
class MuzEngineOptionSpinboxModel : public IMuzEngineOptionableModel
{


public:


    /// <summary>
    /// スピンボックス用
    /// </summary>
    /// <returns></returns>
    MuzEngineOptionSpinboxModel(
        const int   v,
        const int min,
        const int max,
        std::function<void(const IMuzEngineOptionableModel&)> onChanged = nullptr);


    /// <summary>
    /// 代入演算子☆
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    IMuzEngineOptionableModel& operator = (const std::string& v);

};

