#pragma once


#include "n755_070_WhistleAbstract.hpp"


/// <summary>
/// ホイッスル、ルート☆（＾ｑ＾）
/// </summary>
class WhistleRoot : public WhistleAbstract {


public:


	/// <summary>
	///		<pre>
	/// スプリット・ポイントが検索するぜ☆（＾ｑ＾）
	/// 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ownerMonkeySplitedPlace"></param>
	/// <param name="m_pGameEngineStore"></param>
	/// <param name="pos"></param>
	/// <param name="pFlashlight"></param>
	virtual void blowWhistle_asMonkeySplitedPlace(
		MonkeySplitedPlace& ownerMonkeySplitedPlace,
		MuzGameEngineStorageModel& m_pGameEngineStore,
		Position& pos,
		Flashlight* pFlashlight
		) const override;
};


/// <summary>
/// 
/// </summary>
extern const WhistleRoot g_WHISTLE_ROOT;
