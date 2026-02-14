#pragma once
#include "engine_optionable.hpp"


class MuzGameEngineStorageModel;


/// <summary>
///		<pre>
/// エンジン・オプション☆（＾～＾）
///		</pre
/// </summary>
class EngineOption : public EngineOptionable {


public:


    /// <summary>
    /// ボタン用
    /// </summary>
    /// <returns></returns>
    EngineOption(
        std::function<void(const EngineOptionable&)> onChanged = nullptr);


    /// <summary>
    /// テキストボックス用
    /// </summary>
    /// <returns></returns>
    EngineOption(
        const char* v, std::function<void(const EngineOptionable&)> onChanged = nullptr);


    /// <summary>
    /// チェックボックス用
    /// </summary>
    /// <returns></returns>
    EngineOption(
        const bool  v, std::function<void(const EngineOptionable&)> onChanged = nullptr);


    /// <summary>
    /// スピンボックス用
    /// </summary>
    /// <returns></returns>
    EngineOption(
        const int   v,
        const int min,
        const int max,
        std::function<void(const EngineOptionable&)> onChanged = nullptr);


};
