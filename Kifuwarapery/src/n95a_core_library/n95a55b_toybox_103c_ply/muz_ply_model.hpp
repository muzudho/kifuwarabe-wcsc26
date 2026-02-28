#pragma once

#include "../n95a55b_toybox_105c_turn/muz_turn_model.hpp"
#include "ply.hpp"
#include <string_view>
#include <optional>

/// <summary>
/// 手数
/// </summary>
class MuzPlyModel
{


    // ========================================
    // 生成／破棄
    // ========================================


public:
    /// <summary>
    ///     <pre>
    /// 文字列から手数を取得。
    /// 
    ///     - エラーの時はヌル・オプションを返す。
    ///     </pre>
    /// </summary>
    static std::optional<MuzPlyModel> from_string(MuzTurnModel turn, std::string_view turn_str);


    MuzPlyModel(RadixHalfPly radix_half_ply = (RadixHalfPly)0);


    // ========================================
    // フィールド
    // ========================================


private:
    /// <summary>
    ///     <pre>
    /// 将棋式の手数。ストックフィッシュでも実装は同じ。
    /// 
    ///     - 時間管理の役に立つ。
    ///     - 開始局面では 0。先手番が指したら 1 になり、後手番が指したら 2 になる。以降、同様に 1 ずつ増えていく。
    ///     - ［ストックフィッシュ］では `gamePly` と呼ばれている。`2 * (ply - 1) + （先手は0、後手は1）` という計算式。
    ///     </pre>
    /// </summary>
    RadixHalfPly radix_half_ply_;


    // ========================================
    // アクセッサー
    // ========================================


public:
    /// <summary>
    /// ［将棋式の手数、つまり開始局面を０とする］を取得
    /// </summary>
    /// <returns></returns>
    RadixHalfPly get_radix_half_ply() const { return this->radix_half_ply_; }


    /// <summary>
    /// ［将棋式の手数、つまり開始局面を０とする］をセット
    /// </summary>
    /// <param name="turn"></param>
    void set_radix_half_ply(const RadixHalfPly radix_half_ply) { this->radix_half_ply_ = radix_half_ply; }


    // ========================================
    // 主要メソッド
    // ========================================


    bool update_from_string(MuzTurnModel turn, std::string_view half_ply_str);


    // ========================================
    // サブルーチン
    // ========================================


private:
    /// <summary>
    ///     <pre>
    /// 文字列から手数を取得。
    /// 
    ///     - エラーの時はヌル・オプションを返す。
    ///     </pre>
    /// </summary>
    static std::optional<RadixHalfPly> parse(MuzTurnModel turn, std::string_view half_ply_str);
};
