#pragma once


#include "n755_070_WhistleAbstract.hpp"


/// <summary>
/// 
/// </summary>
class WhistlePv : public WhistleAbstract {


public:


	/// <summary>
	///		<pre>
	/// スプリット・ポイントが検索するぜ☆（＾ｑ＾）
	/// 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ownerMonkeySplitedPlace"></param>
	/// <param name="searcher"></param>
	/// <param name="pos"></param>
	/// <param name="pFlashlight"></param>
	virtual void blowWhistle_asMonkeySplitedPlace(
		MonkeySplitedPlace& ownerMonkeySplitedPlace,
		OurCarriage& searcher,
		Position& pos,
		Flashlight* pFlashlight
		) const override;
};


/// <summary>
/// 
/// </summary>
extern const WhistlePv g_WHISTLE_PV;
