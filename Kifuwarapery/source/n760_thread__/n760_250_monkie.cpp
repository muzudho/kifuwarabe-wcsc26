#include <mutex>
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n119_score___/n119_090_ScoreValue.hpp"
#include "../../header/n165_movStack/n165_400_move.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n223_move____/n223_200_depth.hpp"
#include "../../header/n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../../header/n640_searcher/n640_040_nodeKind.hpp"
#include "../../header/n640_searcher/n640_440_splitedNode.hpp"
#include "../../header/n760_thread__/n760_250_monkie.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


// ========================================
// 軽い生成／破棄
// ========================================


Monkie::Monkie(OurCarriage* ourCarriage) /*: ＳｐｌｉｔＰｏｉｎｔｓ()*/ {
	this->m_pOurCarriage = ourCarriage;
	this->m_isEndOfSearch = false;
	this->m_isBeingSearched = false;
	this->m_splitedNodesSize = 0;
	this->m_maxPly = 0;
	this->m_activeSplitedNode = nullptr;
	this->m_activePosition = nullptr;
	this->m_idx = ourCarriage->m_pub.m_monkies.size();
}


// ========================================
// メソッド
// ========================================


// クエスチョン・メソッド


/// <summary>
///		<pre>
/// master と同じ thread であるかを判定
/// 
///		旧名： ＩsAvailableTo
///		</pre>
/// </summary>
/// <param name="master"></param>
/// <returns></returns>
bool Monkie::SetLastSplitNodeSlavesMask(Monkie* master) const {
	if (m_isBeingSearched) { return false; }

	// 分岐ノードの数。ローカルコピーし、次の瞬間に値が変わらないようにする。
	const int splitNodeCount = m_splitedNodesSize;

	// 分岐ノードが０ではなく、最後の分岐ノードのスレーブ・ビットフィールドに 1 を立てる。
	return !splitNodeCount || (m_SplitedNodes[splitNodeCount - 1].m_slavesMask & (UINT64_C(1) << master->m_idx));
}


// メイン・メソッド


void Monkie::NotifyOne() {
	std::unique_lock<Mutex> lock(m_sleepLock);
	m_sleepCond.notify_one();
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Monkie::IsUselessNode() const {
	for (SplitedNode* sp = m_activeSplitedNode; sp != nullptr; sp = sp->m_pParentSplitedNode) {
		if (sp->m_isUselessNode) { return true; }
	}
	return false;
}


/// <summary>
/// 
/// </summary>
/// <param name="b"></param>
void Monkie::WaitFor(volatile const bool& b) {
	std::unique_lock<Mutex> lock(m_sleepLock);
	m_sleepCond.wait(lock, [&] { return b; });
}


/// <summary>
/// 
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
void Monkie::ForkNewMonkey(
	Position& pos,
	Flashlight* pFlashlightBox,
	const ScoreValue alpha,
	const ScoreValue beta,
	ScoreValue& bestScore,
	Move& bestMove,
	const Depth depth,
	const Move threatMove,
	const int moveCount,
	NextmoveEvent& mp,
	const SwordAbstract* pSword,
	const bool cutNode)
{
	assert(pos.IsOK());
	assert(bestScore <= alpha && alpha < beta && beta <= ScoreInfinite);
	assert(-ScoreInfinite < bestScore);
	assert(this->m_pOurCarriage->m_pub.GetMinSplitDepth() <= depth);

	assert(m_isBeingSearched);
	assert(m_splitedNodesSize < g_MaxSplitedNodesPerThread);

	// 個定数のスプリット・ポイント☆（＾ｑ＾）
	SplitedNode& splitedNode = m_SplitedNodes[m_splitedNodesSize];

	splitedNode.m_masterThread = this;
	splitedNode.m_pParentSplitedNode = m_activeSplitedNode;
	splitedNode.m_slavesMask = UINT64_C(1) << m_idx;
	splitedNode.m_depth = depth;
	splitedNode.m_bestMove = bestMove;
	splitedNode.m_threatMove = threatMove;
	splitedNode.m_alpha = alpha;
	splitedNode.m_beta = beta;
	splitedNode.m_pSword01 = pSword;	// ノード・タイプ（実行するプログラム）を切り替える変数みたいだぜ☆（＾ｑ＾）
	splitedNode.m_cutNode = cutNode;
	splitedNode.m_bestScore = bestScore;
	splitedNode.m_pNextmoveEvent = &mp;
	splitedNode.m_moveCount = moveCount;
	splitedNode.m_position = &pos;
	splitedNode.m_nodes = 0;
	splitedNode.m_isUselessNode = false;
	splitedNode.m_pFlashlightBox = pFlashlightBox;

	this->m_pOurCarriage->m_pub.m_mutex_.lock();
	splitedNode.m_mutex.lock();

	++m_splitedNodesSize;
	m_activeSplitedNode = &splitedNode;
	m_activePosition = nullptr;

	// thisThread が常に含まれるので 1
	size_t slavesCount = 1;
	Monkie* slave;

	while ((slave = this->m_pOurCarriage->m_pub.GetAvailableSlave(this)) != nullptr
		&& ++slavesCount <= this->m_pOurCarriage->m_pub.m_maxThreadsPerSplitedNode_ && !Fake)
	{
		splitedNode.m_slavesMask |= UINT64_C(1) << slave->m_idx;
		slave->m_activeSplitedNode = &splitedNode;
		slave->m_isBeingSearched = true;
		slave->NotifyOne();
	}

	if (1 < slavesCount || Fake) {
		splitedNode.m_mutex.unlock();
		this->m_pOurCarriage->m_pub.m_mutex_.unlock();
		Monkie::workAsMonkey();	// ワーカースレッド開始
		assert(!m_isBeingSearched);
		assert(!m_activePosition);
		this->m_pOurCarriage->m_pub.m_mutex_.lock();
		splitedNode.m_mutex.lock();
	}

	m_isBeingSearched = true;
	--m_splitedNodesSize;
	m_activeSplitedNode = splitedNode.m_pParentSplitedNode;
	m_activePosition = &pos;
	pos.setNodesSearched(pos.getNodesSearched() + splitedNode.m_nodes);
	bestMove = splitedNode.m_bestMove;
	bestScore = splitedNode.m_bestScore;

	this->m_pOurCarriage->m_pub.m_mutex_.unlock();
	splitedNode.m_mutex.unlock();
}


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <param name="ss"></param>
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
/// <returns></returns>
template void Monkie::ForkNewMonkey<true >(
	Position& pos,
	Flashlight* ss,
	const ScoreValue alpha,
	const ScoreValue beta,
	ScoreValue& bestScore,
	Move& bestMove,
	const Depth depth,
	const Move threatMove,
	const int moveCount,
	NextmoveEvent& mp,
	const SwordAbstract* pSword,
	const bool cutNode);


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <param name="ss"></param>
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
/// <returns></returns>
template void Monkie::ForkNewMonkey<false>(
	Position& pos,
	Flashlight* ss,
	const ScoreValue alpha,
	const ScoreValue beta,
	ScoreValue& bestScore,
	Move& bestMove,
	const Depth depth,
	const Move threatMove,
	const int moveCount,
	NextmoveEvent& mp,
	const SwordAbstract* pSword,
	const bool cutNode);
