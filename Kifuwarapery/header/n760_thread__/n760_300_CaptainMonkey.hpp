#pragma once
#include "n760_250_MonkeyDefault.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// キャプテン☆（＾ｑ＾） わたしが名前を変えた☆（＾▽＾）
/// 
///		- 元の名前： `ＭainThread`
///		- マスタースレッドに対応する
///		</pre>
/// </summary>
class CaptainMonkey : public MonkeyDefault {


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
	explicit CaptainMonkey(
		OurCarriage* s
	) :
		MonkeyDefault(s),
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
