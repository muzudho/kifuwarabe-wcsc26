#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class MuzStringService
{
public:


    std::vector<std::string> split_command_line(const std::string& line)
    {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        // 半角スペース ' ' で分割
        while (std::getline(ss, item, ' ')) {
            if (!item.empty()) { // 空文字を除外したい場合
                tokens.push_back(item);
            }
        }

        return tokens;
    }
};
