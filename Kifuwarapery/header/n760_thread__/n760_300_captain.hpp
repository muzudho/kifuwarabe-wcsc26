#pragma once

#include "n760_250_soldier.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// キャプテン☆（＾ｑ＾） わたしが名前を変えた☆（＾▽＾）
/// 
///		- 元の名前：ＭａｉｎＴｈｒｅａｄ
///		</pre>
/// </summary>
class Orangutan : public Monkie {


public:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///		<pre>
	/// キャプテンのマスタースレッドだ（ワーカースレッドではない）
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
	explicit Orangutan(OurCarriage* s) : Monkie(s), m_isMasterThread(true) {}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void workAsMonkey() override;
};
