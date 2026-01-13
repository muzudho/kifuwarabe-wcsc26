#pragma once
#include "n105_100_color.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 手番の色の操作
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 手番の色の操作
/// </summary>
class ConvColor {


public:


	/// <summary>
	///		<pre>
	/// 相手の色
	/// 
	///		- コンパイル時に評価
	///		- XXX: 使ってない？
	///		</pre>
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <returns></returns>
	template<Color CLR>
	static inline constexpr Color OPPOSITE_COLOR10() {
		return static_cast<Color>(static_cast<int>(CLR) ^ 1);
	}


	/// <summary>
	///		<pre>
	/// 相手の色
	/// 
	///		- 実行時に評価
	///		</pre>
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	static inline constexpr Color OPPOSITE_COLOR10b(const Color c) {
		return static_cast<Color>(static_cast<int>(c) ^ 1);
	}
};
