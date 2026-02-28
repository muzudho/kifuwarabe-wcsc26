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
    /// 文字列から何手目かをセット。
    /// 
    ///     - エラーの時はヌルを返す。
    ///     </pre>
    /// </summary>
    static std::optional<MuzPlyModel> from_string(MuzTurnModel turn, std::string_view turn_str);


    MuzPlyModel(Ply ply = (Ply)0);


    // ========================================
    // フィールド
    // ========================================


private:
    /// <summary>
    ///     <pre>
    /// チェスの何手目かの数え方から１引いたもの。［ストックフィッシュ］の書き方を残している（＾～＾）
    /// 
    ///     - 時間管理の役に立つ。
    ///     </pre>
    /// </summary>
    Ply game_ply_;


    // ========================================
    // アクセッサー
    // ========================================


public:
    /// <summary>
    /// ストックフィッシュでの［手目］を取得
    /// </summary>
    /// <returns></returns>
    Ply get_game_ply() const { return this->game_ply_; }


    /// <summary>
    /// ストックフィッシュでの［手目］をセット
    /// </summary>
    /// <param name="turn"></param>
    void set_game_ply(const Ply ply) { this->game_ply_ = ply; }
};
