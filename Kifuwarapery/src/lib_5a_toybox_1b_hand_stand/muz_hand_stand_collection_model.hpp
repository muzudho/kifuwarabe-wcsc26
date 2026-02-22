#pragma once

#include "../lib_5a_toybox_n1/color.hpp"
#include "muz_hand_stand_model.hpp"
#include <string_view>

/// <summary>
/// 駒台２つをまとめて表すぜ（＾～＾） SFEN 形式がそうなってるから（＾～＾）
/// </summary>
class MuzHandStandCollectionModel
{
public:


	// ========================================
	// 主要メソッド
	// ========================================


	/// <summary>
	///		<pre>
	///	駒台（持ち駒）のセットをテキスト形式で行う。
	///		- 例えば "2P1R" なら、▲歩が2、▲飛が1枚あることを表す。
	///		</pre>
	/// </summary>
	bool parse_hand_stand_collection(
		std::string_view hand_str,
		MuzHandStandModel& blackHandStand,
		MuzHandStandModel& whiteHandStand);
};
