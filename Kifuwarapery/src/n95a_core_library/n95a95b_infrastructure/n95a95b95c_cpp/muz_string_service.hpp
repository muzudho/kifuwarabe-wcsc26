#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <ranges>	// std::views::split と std::views::transform を使うために必要
#include <string_view>
#include <vector>

class MuzStringService
{
public:


    /// <summary>
    ///     <pre>
    /// デリミター（区切り文字）で分割。
    ///     </pre>
    /// </summary>
    std::vector<std::string_view> split(std::string_view line, char delim = ' ')
    {
        auto splitted = line
            // std::views::split は、区切り文字で分割して、分割された部分を range として返す。
            | std::views::split(delim)
            // std::views::transform は、range を std::string_view に変換するために使う。
            | std::views::transform([](auto&& r) -> std::string_view
                {
                    // C++20 で安全にポインタを取る方法
                    auto begin = r.begin();
                    auto end = r.end();

                    // std::to_address は C++20 で使える（<memory> が必要）
                    return { std::to_address(begin), std::to_address(end) };
                });

            // C++23 なら： std::ranges::to<std::vector>() は、std::string_view のイテレーターを std::vector に変換するために使う。
            //| std::ranges::to<std::vector>();

        // C++20 では std::ranges::to が無いので、こうやって vector 化
        return { splitted.begin(), splitted.end() };
    }
};
