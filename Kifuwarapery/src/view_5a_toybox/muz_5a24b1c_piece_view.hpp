#pragma once

#include "../lib_5a_toybox_2b_board/piece.hpp"
#include <string>

class MuzPieceView
{
public:


    // ========================================
    // 主要メソッド
    // ========================================


    /// <summary>
    /// 駒を文字列に変換して表示するぜ（＾～＾）
    /// </summary>
    static std::string pretty(const Piece piece);
};
