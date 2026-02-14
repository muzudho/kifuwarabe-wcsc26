#pragma once
#include "i_muz_engine_optionable_model.hpp"


/// <summary>
/// エンジン・オプション　＞　テキストボックス
/// </summary>
class MuzEngineOptionTextboxModel : public IMuzEngineOptionableModel
{


public:


    // ========================================
    // 生成／破棄
    // ========================================


    /// <summary>
    /// 生成☆（＾ｑ＾）
    /// </summary>
    /// <returns></returns>
    MuzEngineOptionTextboxModel(
        const char* v, std::function<void(const IMuzEngineOptionableModel&)> onChanged = nullptr);


    // ========================================
    // 演算子
    // ========================================


    /// <summary>
    /// 代入演算子☆
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    IMuzEngineOptionableModel& operator = (const std::string& v);


    // ========================================
    // その他のメソッド
    // ========================================


    /// <summary>
    /// USIコード化☆（＾～＾）
    /// </summary>
    /// <returns></returns>
    std::string ToUSICode() const;// override;
};

