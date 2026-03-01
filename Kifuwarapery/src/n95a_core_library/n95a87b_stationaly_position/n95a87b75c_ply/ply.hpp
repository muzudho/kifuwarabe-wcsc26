//
// 📄 将棋の手数、つまり開始局面を０とする
//

#pragma once

using RadixHalfPly = int;

/// <summary>
/// こんなけたあれば十分だろうという数値。これだけの手数は、実質、読む能力がないはず。
/// </summary>
const RadixHalfPly g_maxPly = 128;

/// <summary>
/// 
/// </summary>
const RadixHalfPly g_maxPlyPlus2 = g_maxPly + 2;
