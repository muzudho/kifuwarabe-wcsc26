#pragma once
#include "../n080_100_sysWorld/n080_082_eraser.hpp"


//────────────────────────────────────────────────────────────────────────────────
// アンローラー
//────────────────────────────────────────────────────────────────────────────────
//
//		- ループの中身を全部ベタ書きして高速化を図るものだぜ（＾～＾）


/// <summary>
/// 	<pre>
/// アンローラー
/// 
///		N 回ループを展開させる。t は lambda で書くと良い。
///		こんな感じに書くと、lambda がテンプレート引数の数値の分だけ繰り返し生成される。
///		Unroller<5>()([&](const int i){std::cout << i << std::endl;});
/// 	<pre>
/// </summary>
/// <typeparam name="N"></typeparam>
template <int N>
struct Unroller
{
	template <typename T>
	FORCE_INLINE void operator () (T t)
	{
		Unroller<N - 1>()(t);
		t(N - 1);
	}
};


/// <summary>
///		<pre>
/// アンローラー
///		</pre>
/// </summary>
template <>
struct Unroller<0>
{
	template <typename T>
	FORCE_INLINE void operator () (T)
	{
	}
};
