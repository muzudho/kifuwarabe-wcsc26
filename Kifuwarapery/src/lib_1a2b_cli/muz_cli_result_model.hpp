#pragma once

class MuzCliResultModel
{


    // ========================================
    // フィールド
    // ========================================


private:

    /// <summary>
    /// ［終了しろ］フラグ（＾～＾）
    /// </summary>
    bool should_quit_;


public:


    // ========================================
    // アクセッサー
    // ========================================


    bool should_quit() const { return should_quit_; }
    void request_quit() { should_quit_ = true; }
};
