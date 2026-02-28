#pragma once

#include "color.hpp"
#include <string_view>

/// <summary>
/// 手番
/// </summary>
class MuzTurnModel
{


    // ========================================
    // フィールド
    // ========================================


private:
    /// <summary>
    /// 手番の色
    /// </summary>
    Color color_;


    // ========================================
    // アクセッサー
    // ========================================


public:
    /// <summary>
    /// 手番の色を取得
    /// </summary>
    /// <returns></returns>
    Color get_color() const { return this->color_; }


    /// <summary>
    /// 手番の色をセット
    /// </summary>
    /// <param name="turn"></param>
    void set_color(const Color color) { this->color_ = color; }


    bool is_black() const { return this->color_ == Color::Black; }


    bool is_white() const { return this->color_ == Color::White; }


    // ========================================
    // 主要メソッド
    // ========================================


    /// <summary>
    ///     - 旧名： `ParseTurn`
    /// </summary>
    bool from_string(std::string_view turn_str);
};
