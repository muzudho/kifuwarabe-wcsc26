#pragma once
#include "muz_engine_optionable_model.hpp"


class MuzGameEngineStorageModel;


/// <summary>
///		<pre>
/// エンジン・オプション☆（＾～＾）
///		</pre
/// </summary>
class MuzEngineOptionModel : public MuzEngineOptionableModel {


public:


    /// <summary>
    /// ボタン用
    /// </summary>
    /// <returns></returns>
    MuzEngineOptionModel(
        std::function<void(const MuzEngineOptionableModel&)> onChanged = nullptr);


    /// <summary>
    /// テキストボックス用
    /// </summary>
    /// <returns></returns>
    MuzEngineOptionModel(
        const char* v, std::function<void(const MuzEngineOptionableModel&)> onChanged = nullptr);


    /// <summary>
    /// チェックボックス用
    /// </summary>
    /// <returns></returns>
    MuzEngineOptionModel(
        const bool  v, std::function<void(const MuzEngineOptionableModel&)> onChanged = nullptr);


    /// <summary>
    /// スピンボックス用
    /// </summary>
    /// <returns></returns>
    MuzEngineOptionModel(
        const int   v,
        const int min,
        const int max,
        std::function<void(const MuzEngineOptionableModel&)> onChanged = nullptr);


};
