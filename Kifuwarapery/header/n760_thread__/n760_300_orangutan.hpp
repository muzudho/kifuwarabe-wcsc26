#pragma once

#include "n760_250_monkie.hpp"


class MuzGameEngineStorage;


/// <summary>
///		<pre>
/// オラウータン☆（＾ｑ＾） わたしが名前を変えた☆（＾▽＾）
/// 
///		- 元の名前： `ＭainThread`
///		- 先頭の猿だぜ（＾～＾）メインスレッド。
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
	explicit Orangutan(MuzGameEngineStorage* s) : Monkie(s), m_isMasterThread(true) {}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void workAsMonkey() override;
};
