#pragma once

#include "color.hpp"
#include <string_view>
#include <optional>

/// <summary>
/// 手番
/// </summary>
class MuzTurnModel
{


    // ========================================
    // 生成／破棄
    // ========================================


public:
    /// <summary>
    ///     <pre>
    /// 文字列から手番を取得。
    /// 
    ///     - エラーの時はヌル・オプションを返す。
    ///     </pre>
    /// </summary>
    static std::optional<MuzTurnModel> from_string(std::string_view turn_str);

    MuzTurnModel(Color color = Color::Null);


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


    void clear() { this->color_ = Color::Null; }

    bool update_from_string(std::string_view turn_str);


    // ========================================
    // サブルーチン
    // ========================================


private:
    /// <summary>
    ///     <pre>
    /// 文字列から手番を取得。
    /// 
    ///     - エラーの時はヌル・オプションを返す。
    ///     </pre>
    /// </summary>
    static std::optional<Color> parse(std::string_view turn_str);
};
