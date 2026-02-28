#pragma once

#include "muz_hand_stand_model.hpp"
#include <string_view>
#include <optional>
#include <tuple>

/// <summary>
/// 駒台２つをまとめて表すぜ（＾～＾） SFEN 形式がそうなってるから（＾～＾）
/// </summary>
class MuzHandStandCollectionModel
{


	// ========================================
	// 生成／破棄
	// ========================================


public:
	MuzHandStandCollectionModel();


	// ========================================
	// フィールド
	// ========================================


private:
	/// <summary>
	/// 先後対局者別の手駒
	/// </summary>
	MuzHandStandModel hand_stands_[g_COLOR_NUM];


	// ========================================
	// アクセッサ
	// ========================================


public:
	/// <summary>
	/// 持ち駒
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <returns></returns>
	template<Color CLR>
	MuzHandStandModel get_hand_stand() const
	{
		return this->hand_stands_[CLR];
	}
	MuzHandStandModel get_hand_stand(const Color c) const;


	// ========================================
	// 主要メソッド
	// ========================================


	bool update_from_string(std::string_view hand_str);


	// ========================================
	// サブルーチン
	// ========================================

//TODO: protected:
	/// <summary>
	///		<pre>
	///	駒台（持ち駒）のセットをテキスト形式で行う。
	///		- 例えば "2P1R" なら、▲歩が2、▲飛が1枚あることを表す。
	///		</pre>
	/// </summary>
	static std::optional<std::pair<MuzHandStandModel, MuzHandStandModel>> parse(
		std::string_view hand_str);
};
