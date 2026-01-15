#pragma once
#include "../n210_score___/n119_090_scoreIndex.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"// &参照は使えない。*参照は使える。
#include "../n885_searcher/n885_040_ourCarriage.hpp"


/// <summary>
/// 千日手タイプ
/// </summary>
class RepetitionTypeAbstract {


public:


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// 千日手による探索打切りの判断
	///		</pre>
	/// </summary>
	/// <param name="isReturn"></param>
	/// <param name="resultScore"></param>
	/// <param name="pSearcher"></param>
	/// <param name="pFlashlightBox"></param>
	virtual std::pair<bool, ScoreIndex> IsStop(
		//bool& isReturn,
		//ScoreIndex& resultScore,
		const OurCarriage* pSearcher,
		const Flashlight* pFlashlightBox) const = 0;
};

