#pragma once
#include <thread>	//std::thread
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n210_score___/n119_090_scoreIndex.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n223_move____/n223_200_depth.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp" // 持ち合い


class OurCarriage;


/// <summary>
/// 
/// </summary>
const int g_MaxSplitedNodesPerThread = 8;


/// <summary>
///		<pre>
/// 戦士☆（＾▽＾） わたしが名前を変えた☆（＾▽＾） リュックサックを持っているぜ（＾▽＾）
/// 
///		- 元の名前： `Ｔhread`
///		- ゲームツリーを戦線拡大していくぜ☆！（＾ｑ＾）
///		</pre>
/// </summary>
class MonkeyAbstract {


public:


	// ========================================
	// 軽い生成／破棄
	// ========================================


	/// <summary>
	/// 生成。
	/// </summary>
	/// <param name="s"></param>
	explicit MonkeyAbstract(OurCarriage* s);


	/// <summary>
	/// 破棄。
	/// </summary>
	virtual ~MonkeyAbstract() {};


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
	/// 
	/// </summary>
	SplitedNode m_SplitedNodes[g_MaxSplitedNodesPerThread];

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
	///		<pre>
	/// 標準の条件変数。
	/// 
	///		- スリープ？
	///		</pre>
	/// </summary>
	ConditionVariable m_sleepCond;

	/// <summary>
	/// スレッドのハンドル
	/// </summary>
	std::thread m_threadHandle;

	/// <summary>
	/// 
	/// </summary>
	SplitedNode* volatile m_activeSplitedNode;

	/// <summary>
	/// 
	/// </summary>
	volatile int m_splitedNodesSize;

	/// <summary>
	/// わたしたちの馬車
	/// </summary>
	OurCarriage* m_pOurCarriage;


	// ========================================
	// メソッド
	// ========================================


	// クエスチョン・メソッド


	/// <summary>
	/// 
	/// </summary>
	/// <param name="master"></param>
	/// <returns></returns>
	bool SetLastSplitNodeSlavesMask(MonkeyAbstract* master) const;


	/// <summary>
	/// カットオフが起こったノードだ
	/// </summary>
	/// <returns></returns>
	bool IsUselessNode() const;


	// メイン・メソッド


	/// <summary>
	/// ワーカースレッド開始
	/// </summary>
	virtual void startMonkey_n10();


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
	/// <param name="bestScore"></param>
	/// <param name="bestMove"></param>
	/// <param name="depth"></param>
	/// <param name="threatMove"></param>
	/// <param name="moveCount"></param>
	/// <param name="mp"></param>
	/// <param name="pSword"></param>
	/// <param name="cutNode"></param>
	template <bool Fake>
	void ForkNewMonkey(
		Position& pos,
		Flashlight* pFlashlightBox,
		const ScoreIndex alpha,
		const ScoreIndex beta,
		ScoreIndex& bestScore,
		Move& bestMove,
		const Depth depth,
		const Move threatMove,
		const int moveCount,
		NextmoveEvent& mp,
		const SwordAbstract* pSword,
		const bool cutNode
	);
};
