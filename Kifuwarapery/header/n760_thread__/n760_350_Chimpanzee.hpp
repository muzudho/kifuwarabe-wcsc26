#pragma once
#include "n760_250_Monkey.hpp"


class OurCarriage;


/// <summary>
///		<pre>
/// チンパンジー
/// 
///		- 元の名前： `ＴimerThread`, `ＥrrandMonkey`
///		- こいつは他の猿とは違う。思考用ではなく、時計監視用。
///		- ［反復深化探索］を止めるかどうかのタイマーの働きをしている。１アプリケーションに１匹。
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
	/// 猿として働く（ワーカースレッド）
	/// </summary>
	virtual void workAsMonkey_10a500b500c500d500e() override;
};
