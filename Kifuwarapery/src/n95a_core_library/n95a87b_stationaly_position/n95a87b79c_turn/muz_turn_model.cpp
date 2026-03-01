#include "muz_turn_model.hpp"


// ========================================
// 生成／破棄
// ========================================


std::optional<MuzTurnModel> MuzTurnModel::from_string(std::string_view turn_str)
{
    auto result = MuzTurnModel::parse(turn_str);
    return MuzTurnModel(result.value());
}


MuzTurnModel::MuzTurnModel(Color color)
{
    this->color_ = color;
}


// ========================================
// 主要メソッド
// ========================================


bool MuzTurnModel::update_from_string(std::string_view turn_str)
{
    auto result = MuzTurnModel::parse(turn_str);
    if (result) {
        this->color_ = result.value();
        return true;
    }
    else {
        return false;
    }
}


// ========================================
// サブルーチン
// ========================================


/// <summary>
///     <pre>
/// 文字列から手番を取得。
/// 
///     - エラーの時はヌル・オプションを返す。
///     </pre>
/// </summary>
std::optional<Color> MuzTurnModel::parse(std::string_view turn_str)
{
    if (turn_str == "b") return Color::Black;
    if (turn_str == "w") return Color::White;
    return std::nullopt;
}
