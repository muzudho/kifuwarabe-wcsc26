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
    using FnProcessCommandLine = std::function<MuzCliResultModel(const std::string& cmd)>;


    // ========================================
    // 生成／破棄
    // ========================================


    // コンストラクタでハンドラを受け取る（または後でsetしてもOK）
    explicit MuzCliService(FnProcessCommandLine on_process_command_line = nullptr)
        : process_command_line_(std::move(on_process_command_line))
    {
    }

private:


    // ========================================
    // プロパティー
    // ========================================


    FnProcessCommandLine process_command_line_;

public:

    // ========================================
    // 主要なメソッド
    // ========================================

    void main_loop(int argc, char* argv[]);

    void set_process_command_line(FnProcessCommandLine h) {
        process_command_line_ = std::move(h);
    }
};