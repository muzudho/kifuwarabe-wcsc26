#pragma once
#include "n760_250_MonkeyAbstract.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// 部下
/// 
///		- 元の名前： `ＴimerThread`
///		</pre>
/// </summary>
class ErrandMonkey : public MonkeyAbstract {


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
	explicit ErrandMonkey(OurCarriage* s) : MonkeyAbstract(s), m_lifetimeMilliseconds(0) {}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void startMonkey_n10() override;
};
