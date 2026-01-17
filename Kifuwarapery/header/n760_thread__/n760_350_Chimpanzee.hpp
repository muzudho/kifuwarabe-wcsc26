#pragma once
#include "n760_250_Monkey.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// チンパンジー
/// 
///		- 元の名前： `ＴimerThread`, `ＥrrandMonkey`
///		</pre>
/// </summary>
class Chimpanzee : public Monkey {


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
	explicit Chimpanzee(OurCarriage* s) : Monkey(s), m_lifetimeMilliseconds(0) {}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void startMonkey_n10() override;
};
