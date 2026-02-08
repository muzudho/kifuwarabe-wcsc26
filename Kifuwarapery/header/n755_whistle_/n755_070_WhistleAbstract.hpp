#pragma once


#include "../n220_position/n220_650_position.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp" // OurCarriage と持ち合い


class OurCarriage;


/// <summary>
///		<pre>
/// ホイッスル
/// 
///		- 旧名： ノード・タイプ
///		- ［一緒に走る猿たちが分かれた所］でホイッスルを吹けだぜ☆（＾ｑ＾）またそこから猿が走るぜ☆（＾ｑ＾）
///		</pre>
/// </summary>
class WhistleAbstract {


public:


	/// <summary>
	///		<pre>
	/// ［一緒に走る猿たちが分かれた所］でホイッスルを吹くぜ（＾～＾）！
	/// 
	///		- 依存関係の都合上、インラインにはしないぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ownerMonkeySplitedPlace"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="pos"></param>
	/// <param name="pFlashlight"></param>
	virtual void blowWhistle_asMonkeySplitedPlace(
		MonkeySplitedPlace& ownerMonkeySplitedPlace,
		OurCarriage& ourCarriage,
		Position& pos,
		Flashlight* pFlashlight) const = 0;
};
