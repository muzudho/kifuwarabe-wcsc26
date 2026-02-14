#pragma once


#include "n755_070_WhistleAbstract.hpp"


/// <summary>
///		<pre>
/// ［几帳面な猿］を走らすホイッスルぜ☆（＾ｑ＾）
/// 
///		- 旧名： `NodeType_PV`
/// 	</pre>
/// </summary>
class WhistleForMeticulousMonkey : public WhistleAbstract {


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
		GameEngineStorageOurCarriage& m_pGameEngineStore,
		Position& pos,
		Flashlight* pFlashlight
		) const override;
};


/// <summary>
/// 
/// </summary>
extern const WhistleForMeticulousMonkey g_WHISTLE_FOR_METICULOUS_MONKEY;
