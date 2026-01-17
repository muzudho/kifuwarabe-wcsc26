#pragma once
#include "n760_250_Monkey.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// オラウータン☆（＾ｑ＾） わたしが名前を変えた☆（＾▽＾）
/// 
///		- 元の名前： `ＭainThread`, `ＣaptainMonkey`
///		- マスタースレッドに対応する
///		</pre>
/// </summary>
class Orangutans : public Monkey {


public:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///		<pre>
	/// キャプテン猿（マスタースレッド）だ（ワーカースレッドではない）
	///		</pre>
	/// </summary>
	volatile bool m_isMasterThread;


	// ========================================
	// 軽い生成／破棄
	// ========================================


	/// <summary>
    /// 生成☆（＾ｑ＾）
	/// </summary>
	/// <param name="s"></param>
	explicit Orangutans(
		OurCarriage* s
	) :
		Monkey(s),
		m_isMasterThread(true)
	{
	}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void startMonkey_n10() override;
};
