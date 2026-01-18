#pragma once

#include "n760_250_soldier.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// チンパンジー
/// 
///		- 元の名前：　1. ＴｉｍｅｒＴｈｒｅａｄ, 2. Ｗarrior
///		- 残り時間を管理する猿だぜ（＾～＾）
///		</pre>
/// </summary>
class Chimpanzee : public Monkie {


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
	explicit Chimpanzee(OurCarriage* s) : Monkie(s), m_lifetimeMilliseconds(0) {}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void StartWorkerThread() override;
};
