#include "muz_turn_model.hpp"


// ========================================
// 主要メソッド
// ========================================


bool MuzTurnModel::from_string(std::string_view turn_str)
{
    if (turn_str == "b") { color_ = Color::Black; return true; }
    if (turn_str == "w") { color_ = Color::White; return true; }
    return false;
}
