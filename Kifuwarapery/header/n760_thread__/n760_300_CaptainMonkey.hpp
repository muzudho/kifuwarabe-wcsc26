#pragma once
#include "n760_250_MonkeyAbstract.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// キャプテン☆（＾ｑ＾） わたしが名前を変えた☆（＾▽＾）
/// 
///		- 元の名前： `ＭainThread`
///		</pre>
/// </summary>
class CaptainMonkey : public MonkeyAbstract {


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
	explicit CaptainMonkey(OurCarriage* s) : MonkeyAbstract(s), m_isMasterThread(true) {}


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void StartWorkerThread() override;
};
