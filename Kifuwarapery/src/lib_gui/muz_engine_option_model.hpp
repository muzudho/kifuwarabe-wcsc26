#pragma once
#include "muz_engine_optionable_model.hpp"


/// <summary>
///		<pre>
/// エンジン・オプション☆（＾～＾）
/// 
///     - TODO ほんとはボタン用、テキストボックス用、チェックボックス用、スピンボックス用のクラスを分けるべきだと思うが（＾～＾）
///		</pre
/// </summary>
class MuzEngineOptionModel : public MuzEngineOptionableModel
{


public:


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
