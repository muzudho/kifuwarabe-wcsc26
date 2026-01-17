#pragma once
#include "n760_250_Monkey.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// チンパンジー
/// 
///		- 元の名前： `ＴimerThread`, `ＥrrandMonkey`
///		- ［反復深化探索］を止めるかどうかのタイマーの働きをしている。
///		</pre>
/// </summary>
class Chimpanzee : public Monkey {


public:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///		<pre>
	/// ライフタイム・ミリ秒
	/// 
	///		- 旧名： `ｍsec`
	///		- 0 になると、［反復深化探索］を止めるフラグをオンにするぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	int m_lifetimeMilliseconds;


	// ========================================
	// 軽い生成／破棄
	// ========================================


	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="s"></param>
	explicit Chimpanzee(OurCarriage* s) :
		Monkey(s),
		m_lifetimeMilliseconds(0) {}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void startMonkey_n10() override;
};
