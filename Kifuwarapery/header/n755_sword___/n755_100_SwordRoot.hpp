#pragma once


#include "n755_070_SwordAbstract.hpp"


/// <summary>
/// 剣ルート☆（＾ｑ＾）
/// </summary>
class SwordRoot : public SwordAbstract {


public:


	/// <summary>
	///		<pre>
	/// スプリット・ポイントが検索するぜ☆（＾ｑ＾）
	/// 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ownerSplitedNode"></param>
	/// <param name="searcher"></param>
	/// <param name="pos"></param>
	/// <param name="pFlashlight"></param>
	virtual void GoSearch_AsSplitedNode(
		SplitedNode& ownerSplitedNode,
		Rucksack& searcher,
		Position& pos,
		Flashlight* pFlashlight
		) const override;
};


/// <summary>
/// 
/// </summary>
extern const SwordRoot g_SWORD_ROOT;
