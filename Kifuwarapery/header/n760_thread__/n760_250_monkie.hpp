#pragma once

#include <thread>	//std::thread
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n223_move____/n223_200_depth.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp" // 持ち合い


class GameEngineStorageOurCarriage;


/// <summary>
///		<pre>
/// ［一緒に走る猿の最大数］
///		- 旧名： スレッド毎のスプリット・ポイントの最大数
///		</pre>
/// </summary>
const int g_MaxNumberOfMonkeysRunningTogether = 8;


/// <summary>
///		<pre>
/// 猿☆（＾▽＾） わたしが名前を変えた☆（＾▽＾） ［わたしたちの馬車］を持っているぜ（＾▽＾）
/// 
///		- 元の名前： 1. `Ｔhread`, 2. `Ｍilitary`
///		- ゲームツリーを戦線拡大していくぜ☆！（＾ｑ＾）
///		</pre>
/// </summary>
class Monkie {


public:


	// ========================================
	// 軽い生成／破棄
	// ========================================


	/// <summary>
	/// 生成。
	/// </summary>
	/// <param name="s"></param>
	explicit Monkie(GameEngineStorageOurCarriage* s);


	/// <summary>
	/// 破棄。
	/// </summary>
	virtual ~Monkie() {};


	// ========================================
	// フィールド
	// ========================================


	// クエスチョン・フィールド


	/// <summary>
	/// 探索中だ
	/// </summary>
	volatile bool m_isBeingSearched;

	/// <summary>
	/// 
	/// </summary>
	volatile bool m_isEndOfSearch;


	// メイン・フィールド


	/// <summary>
	/// ［一緒に走る猿たちが分かれた所］の配列
	/// </summary>
	MonkeySplitedPlace m_MonkeySplitedPlaces[g_MaxNumberOfMonkeysRunningTogether];

	/// <summary>
	/// 
	/// </summary>
	Position* m_activePosition;

	/// <summary>
	/// インデックス。
	/// </summary>
	int m_idx;

	/// <summary>
	/// 
	/// </summary>
	int m_maxPly;

	/// <summary>
	/// 
	/// </summary>
	Mutex m_sleepLock;

	/// <summary>
	/// 
	/// </summary>
	ConditionVariable m_sleepCond;

	/// <summary>
	/// 猿に紐づくスレッド
	/// </summary>
	std::thread m_handleThread;

	/// <summary>
	///		<pre>
	/// ［一緒に走る猿たちが分かれた所］
	/// 
	///		- 親要素になる（＾～＾）？
	///		</pre>
	/// </summary>
	MonkeySplitedPlace* volatile m_activeMonkeySplitedPlace;

	/// <summary>
	/// 
	/// </summary>
	volatile int m_numberOfMonkeysRunningTogether;

	/// <summary>
	/// わたしたちの馬車
	/// </summary>
	GameEngineStorageOurCarriage* m_pOurCarriage;


	// ========================================
	// メソッド
	// ========================================


	// クエスチョン・メソッド


	/// <summary>
	/// 
	/// </summary>
	/// <param name="master"></param>
	/// <returns></returns>
	bool SetLastSplitNodeSlavesMask(Monkie* master) const;


	/// <summary>
	/// カットオフが起こったノードだ
	/// </summary>
	/// <returns></returns>
	bool IsUselessNode() const;


	// メイン・メソッド


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void workAsMonkey();


	/// <summary>
	/// 
	/// </summary>
	void NotifyOne();


	/// <summary>
	/// 
	/// </summary>
	/// <param name="b"></param>
	void WaitFor(volatile const bool& b);


	/// <summary>
	///		<pre>
	/// 元の名前： Ｓｐｌｉｔ
	/// 探索を分けるのだろうか☆？兵士をどんどん増やそうぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <typeparam name="Fake"></typeparam>
	/// <param name="pos"></param>
	/// <param name="pFlashlightBox"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="bestMove"></param>
	/// <param name="depth"></param>
	/// <param name="threatMove"></param>
	/// <param name="moveCount"></param>
	/// <param name="mp"></param>
	/// <param name="pWhistle"></param>
	/// <param name="cutNode"></param>
	template <bool Fake>
	void ForkNewMonkey(
		Position& pos,
		Flashlight* pFlashlightBox,
		const Sweetness alpha,
		const Sweetness beta,
		Sweetness& bestSweetness,
		Move& bestMove,
		const Depth depth,
		const Move threatMove,
		const int moveCount,
		NextmoveEvent& mp,
		const WhistleAbstract* pWhistle,
		const bool cutNode
	);
};
