#pragma once

#include "muz_cli_result_model.hpp"
#include <string>
#include <functional>   // std::function

class MuzCliService
{

public:


    // ========================================
    // 型定義
    // ========================================


    // コールバックの型をtypedef（またはusing）でわかりやすく
    using FnProcessCommand = std::function<MuzCliResultModel(const std::string& cmd)>;


    // ========================================
    // 生成／破棄
    // ========================================


    // コンストラクタでハンドラを受け取る（または後でsetしてもOK）
    explicit MuzCliService(FnProcessCommand on_process_command = nullptr)
        : process_command_(std::move(on_process_command))
    {
    }

private:


    // ========================================
    // プロパティー
    // ========================================


    FnProcessCommand process_command_;

public:

    // ========================================
    // 主要なメソッド
    // ========================================

    void main_loop(int argc, char* argv[]);

    void set_process_command(FnProcessCommand h) {
        process_command_ = std::move(h);
    }
};