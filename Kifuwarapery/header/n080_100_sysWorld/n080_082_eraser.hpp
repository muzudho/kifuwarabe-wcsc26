#pragma once
#include "../n080_100_sysWorld/n080_081_ioLock.hpp"


//────────────────────────────────────────────────────────────────────────────────
// イレイザー
//────────────────────────────────────────────────────────────────────────────────
//
//      - 出力を捨ててる（＾～＾）？


#if defined LEARN
#undef SYNCCOUT
#undef SYNCENDL
/// <summary>
/// 
/// </summary>
class Eraser {};


extern Eraser SYNCCOUT;
extern Eraser SYNCENDL;


/// <summary>
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="temp"></param>
/// <param name=""></param>
/// <returns></returns>
template <typename T>
Eraser& operator << (Eraser& temp, const T&) { return temp; }
#endif
