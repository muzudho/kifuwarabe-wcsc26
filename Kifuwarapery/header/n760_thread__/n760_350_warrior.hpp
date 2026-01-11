#pragma once


#include "n760_250_military.hpp"


class Rucksack;


/// <summary>
/// 元の名前：　ＴｉｍｅｒＴｈｒｅａｄ
/// </summary>
class Warrior : public Military {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="s"></param>
	explicit Warrior(Rucksack* s) : Military(s), m_lifetimeMilliseconds(0) {}


	/// <summary>
	/// 空回り開始
	/// </summary>
	virtual void StartIdleLoop()override;


	/// <summary>
	/// ｍｓｅｃはミリ秒☆？ 0にするとタイマーが止まるらしい☆（＾ｑ＾）？
	/// </summary>
	int m_lifetimeMilliseconds;
};
