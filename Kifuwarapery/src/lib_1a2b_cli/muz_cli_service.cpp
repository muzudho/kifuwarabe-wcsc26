#include "muz_cli_service.hpp"
#include <string>
#include <iostream>


// ========================================
// 主要なメソッド
// ========================================


void MuzCliService::main_loop(int argc, char* argv[])
{
    std::string line;

    // コマンドライン引数（があれば）を結合して１つのコマンド文字列として扱い、最初に1回だけ処理するぜ（＾～＾）
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            // 引数をスペース区切りで自然に結合（末尾スペースなし）
            line = argv[1];
            for (int i = 2; i < argc; ++i)
            {
                line += " " + std::string(argv[i]);
            }

            // ここで1回コマンドを処理する
            if (this->process_command_line_)
            {
                auto result = this->process_command_line_(line);
                if (result.should_quit()) { return; }
            }
            else
            {
                std::cout << "(^q^) process_command_line_ not found." << "\n";
                return;
            }
            //process_command(line);
            line.clear();  // 次は標準入力から読む
        }
    }

    // インタラクティブモード（REPL）ループ
    //      - いわゆる、コマンド受付
    while (true)
    {
        //std::cout << "(^q^) muz> " << std::flush;  // プロンプト（好みで変えて）

        if (!std::getline(std::cin, line)) {
            // Ctrl+D または入力エラー → 終了
            std::cout << "\n";
            break;
        }

        // 空行（ただのEnter）はスルーするか、特別扱いしてもいい
        if (line.empty())
        {
            continue;           // ← 空行無視パターン（おすすめ）
            // または process_command(""); とかでもOK
        }

        // コマンドを処理する
        if (this->process_command_line_)
        {
            auto result = this->process_command_line_(line);
            if (result.should_quit()) { return; }
        }
        else
        {
            std::cout << "(^q^) process_command_line_ not found." << "\n";
            return;
        }
        //process_command(line);
        line.clear();  // 次回用にクリア（なくてもいいけど明示的）
    }

    //std::cout << "bye.\n";
}
