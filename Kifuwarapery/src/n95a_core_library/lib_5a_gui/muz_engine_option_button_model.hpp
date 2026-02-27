#pragma once
#include "muz_engine_option_abstract_model.hpp"


/// <summary>
/// エンジン・オプション　＞　ボタン
/// </summary>
class MuzEngineOptionButtonModel : public MuzEngineOptionAbstractModel
{


public:


    // ========================================
    // 生成／破棄
    // ========================================


    /// <summary>
    /// 生成☆（＾ｑ＾）
    /// </summary>
    /// <param name="onChanged"></param>
    MuzEngineOptionButtonModel(
        std::function<void(const MuzEngineOptionAbstractModel&)> onChanged = nullptr);


    // ========================================
    // 演算子
    // ========================================


    /// <summary>
    /// 代入演算子☆
    /// </summary>
    /// <param name="v"></param>
    /// <returns></returns>
    MuzEngineOptionAbstractModel& operator = (const std::string& v);


    // ========================================
    // その他のメソッド
    // ========================================


    /// <summary>
    /// USIコード化☆（＾～＾）
    /// </summary>
    /// <returns></returns>
    std::string ToUSICode() const;// override;
};

