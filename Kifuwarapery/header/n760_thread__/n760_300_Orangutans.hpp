#pragma once
#include "n760_250_Monkey.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// オラウータン☆（＾ｑ＾） わたしが名前を変えた☆（＾▽＾）
/// 
///		- 元の名前： `ＭainThread`, `ＣaptainMonkey`
///		- マスタースレッドに対応する
///		- 冒険しているのはこの猿（＾～＾）
///		</pre>
/// </summary>
class Orangutans : public Monkey {


public:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///		<pre>
	/// マスタースレッドだ（ワーカースレッドではない）
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
	/// 猿として働く（ワーカースレッド）
	/// </summary>
	virtual void workAsMonkey_10a520b500c500d() override;
};
