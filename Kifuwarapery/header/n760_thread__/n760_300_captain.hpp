#pragma once

#include "n760_250_military.hpp"


class Rucksack;


/// <summary>
///		<pre>
/// キャプテン☆（＾ｑ＾） わたしが名前を変えた☆（＾▽＾）
/// 
///		- 元の名前：ＭａｉｎＴｈｒｅａｄ
///		</pre>
/// </summary>
class Captain : public Military {


public:


	/// <summary>
    /// 生成☆（＾ｑ＾）
	/// </summary>
	/// <param name="s"></param>
	explicit Captain(Rucksack* s) : Military(s), m_isThinking(true) {}


	/// <summary>
	/// 
	/// </summary>
	virtual void IdleLoop()override;


	/// <summary>
	/// 
	/// </summary>
	volatile bool m_isThinking;
};
