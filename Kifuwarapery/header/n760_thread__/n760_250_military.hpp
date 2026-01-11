#pragma once

#include <thread>	//std::thread
#include "../n080_common__/n080_100_common.hpp"
#include "../n119_score___/n119_090_scoreIndex.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n223_move____/n223_040_nodeType.hpp"
#include "../n223_move____/n223_200_depth.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp" // 持ち合い


class Rucksack;


/// <summary>
/// 
/// </summary>
const int g_MaxSplitedNodesPerThread = 8;


/// <summary>
///		<pre>
/// 軍人☆（＾▽＾） わたしが名前を変えた☆（＾▽＾）
/// 
///		- 元の名前：Ｔｈｒｅａｄ
///		- ゲームツリーを戦線拡大していくぜ☆！（＾ｑ＾）
///		</pre>
/// </summary>
class Military {


public:


	/// <summary>
	/// 生成。
	/// </summary>
	/// <param name="s"></param>
	explicit Military(Rucksack* s);


	/// <summary>
	/// 破棄。
	/// </summary>
	virtual ~Military() {};


	/// <summary>
	/// 空回り開始
	/// </summary>
	virtual void StartIdleLoop();


	/// <summary>
	/// 
	/// </summary>
	void NotifyOne();


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool CutoffOccurred() const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="master"></param>
	/// <returns></returns>
	bool IsAvailableTo(Military* master) const;


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
	void ForkNewFighter(
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


	/// <summary>
	/// 
	/// </summary>
	SplitedNode m_SplitedNodes[g_MaxSplitedNodesPerThread];

	/// <summary>
	/// 
	/// </summary>
	Position* m_activePosition;

	/// <summary>
	/// 
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
	/// 
	/// </summary>
	std::thread m_handle;

	/// <summary>
	/// 
	/// </summary>
	SplitedNode* volatile m_activeSplitedNode;

	/// <summary>
	/// 
	/// </summary>
	volatile int m_splitedNodesSize;

	/// <summary>
	/// 
	/// </summary>
	volatile bool m_searching;

	/// <summary>
	/// 
	/// </summary>
	volatile bool m_exit;

	/// <summary>
	/// 
	/// </summary>
	Rucksack* m_pRucksack;
};
