#pragma once

#include "n760_250_soldier.hpp"


class Rucksack;


/// <summary>
///		<pre>
/// 部下
/// 
///		- 元の名前：　1. ＴｉｍｅｒＴｈｒｅａｄ, 2. Ｗarrior
///		</pre>
/// </summary>
class Subordinate : public Soldier {


public:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// ｍｓｅｃはミリ秒☆？ 0にするとタイマーが止まるらしい☆（＾ｑ＾）？
	/// </summary>
	int m_lifetimeMilliseconds;


	// ========================================
	// 軽い生成／破棄
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	/// <param name="s"></param>
	explicit Subordinate(Rucksack* s) : Soldier(s), m_lifetimeMilliseconds(0) {}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void StartWorkerThread() override;
};
