#include "muz_cli_service.hpp"


// ========================================
// 主要なメソッド
// ========================================


void MuzCliService::main_loop(int argc, char* argv[])
{
    std::cout << "MuzCliService::main_loop() called with " << argc << " arguments.\n";
    for (int i = 0; i < argc; ++i) {
        std::cout << "  argv[" << i << "] = " << argv[i] << "\n";
    }
}
