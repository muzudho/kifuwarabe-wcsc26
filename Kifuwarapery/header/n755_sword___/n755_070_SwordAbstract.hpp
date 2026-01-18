#pragma once


#include "../n220_position/n220_650_position.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp" // OurCarriage と持ち合い


class OurCarriage;


/// <summary>
/// スプリット・ポイントは、剣を持っているんだぜ☆（＾ｑ＾）
/// </summary>
class SwordAbstract {


public:


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ownerSplitedNode"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pos"></param>
	/// <param name="pFlashlight"></param>
	virtual void workAsMonkey_10a520b500c500d500e_searchAsSplitedNode(
		SplitedNode& ownerSplitedNode,
		OurCarriage& ourCarriage,
		Position& pos,
		Flashlight* pFlashlight
		) const = 0;
};
