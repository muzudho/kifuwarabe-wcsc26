#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n165_movStack/n165_300_movegenType.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n407_moveGen_/n407_900_moveList.hpp"
#include "../../header/n560_timeMgr_/n560_100_limitsDuringGo.hpp"
#include "../../header/n640_searcher/n640_450_rootMove.hpp"
#include "../../header/n760_thread__/n760_250_MonkeyAbstract.hpp"
#include "../../header/n760_thread__/n760_400_MonkiesPub.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


// ========================================
// メイン・メソッド
// ========================================


//namespace {


/// <summary>
/// ワーカースレッド開始
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="s"></param>
/// <returns></returns>
template <typename T> T* newThread(OurCarriage* s) {
	T* th = new T(s);
	th->m_handle = std::thread(&MonkeyAbstract::StartWorkerThread, th); // move constructor
	return th;
}


/// <summary>
/// 
/// </summary>
/// <param name="th"></param>
void deleteThread(MonkeyAbstract* th) {
	th->m_isEndOfSearch = true;
	th->NotifyOne();
	th->m_handle.join(); // Wait for thread termination
	delete th;
}


//}


/// <summary>
/// 最初の設定（初期化）を行うぜ☆（＾▽＾）
/// </summary>
/// <param name="s"></param>
void MonkiesPub::initializeMonkiePub_app10(OurCarriage* s)
{
	m_isSleepWhileIdle_ = true;
#if defined LEARN
#else
	m_pSubordinate_ = newThread<ErrandMonkey>(s);
#endif

	push_back(newThread<CaptainMonkey>(s));

	ReadUSIOptions(s);
}


/// <summary>
/// 
/// </summary>
void MonkiesPub::Exit() {
#if defined LEARN
#else
	// checkTime() がデータにアクセスしないよう、先に timer_ を delete
	deleteThread(m_pSubordinate_);
#endif

	for (auto elem : *this) {
		deleteThread(elem);
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="searcher"></param>
void MonkiesPub::ReadUSIOptions(OurCarriage* searcher) {

	this->m_maxThreadsPerSplitedNode_ = searcher->m_engineOptions["Max_Threads_per_Split_Point"];

	// スレッドの個数（１以上）
	const size_t numberOfThreads   = searcher->m_engineOptions["Threads"];

	this->m_minimumSplitDepth_ = (
		numberOfThreads < 6 ?
			4 :
			(numberOfThreads < 8 ?
				5 :
				7
			)
	) * OnePly;
	assert(0 < numberOfThreads);

	while (size() < numberOfThreads) {
		push_back(newThread<MonkeyAbstract>(searcher));
	}

	while (numberOfThreads < size()) {
		deleteThread(back());
		pop_back();
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="master"></param>
/// <returns></returns>
MonkeyAbstract* MonkiesPub::GetAvailableSlave(MonkeyAbstract* master) const {
	for (auto elem : *this) {
		if (elem->SetLastSplitNodeSlavesMask(master)) {
			return elem;
		}
	}
	return nullptr;
}


/// <summary>
/// 元の引数名はｍｓｅｃ☆
/// </summary>
/// <param name="maxPly"></param>
void MonkiesPub::SetCurrWorrior(const int maxPly) {
	m_pSubordinate_->m_maxPly = maxPly;
	m_pSubordinate_->NotifyOne(); // Wake up and restart the timer
}


/// <summary>
/// 
/// </summary>
void MonkiesPub::WaitForThinkFinished()
{
	CaptainMonkey* t = GetFirstCaptain();
	std::unique_lock<Mutex> lock(t->m_sleepLock);
	m_sleepCond_.wait(lock, [&] { return !(t->m_isMasterThread); });
}


/// <summary>
/// 思考開始
/// </summary>
/// <param name="position"></param>
/// <param name="limits"></param>
/// <param name="searchMoves"></param>
void MonkiesPub::StartThinking(
	const GameStats& gameStats,
	const Position& position,
	const LimitsDuringGo& limits,
	const std::vector<Move>& searchMoves)
{
#if defined LEARN
#else
	WaitForThinkFinished();
#endif

	position.GetOurCarriage()->m_stopwatch.Restart();

	position.GetOurCarriage()->m_signals.m_stopOnPonderHit = position.GetOurCarriage()->m_signals.m_firstRootMove = false;
	position.GetOurCarriage()->m_signals.m_stop = position.GetOurCarriage()->m_signals.m_failedLowAtRoot = false;

	position.GetOurCarriage()->m_gameStats = gameStats;
	position.GetOurCarriage()->m_rootPosition = position;
	position.GetOurCarriage()->m_limits = limits;
	position.GetOurCarriage()->m_rootMoves.clear();

#if defined LEARN
	// searchMoves を直接使う。
	GetPos.GetRucksack()->m_rootMoves.push_back(RootMove(position.GetRucksack()->m_ourMoves[0]));

	// 浅い探索なので、thread 生成、破棄のコストが高い。余分な thread を生成せずに直接探索を呼び出す。
	GetPos.GetRucksack()->Think(GetPos.GetRucksack());
#else
	const MovegenType MT = N08_Legal;
	for (MoveList<MT> ml(position); !ml.IsEnd(); ++ml) {
		if (searchMoves.empty()
			|| std::find(searchMoves.begin(), searchMoves.end(), ml.GetMove()) != searchMoves.end())
		{
			position.GetOurCarriage()->m_rootMoves.push_back(RootMove(ml.GetMove()));
		}
	}

	this->GetFirstCaptain()->m_isMasterThread = true;
	this->GetFirstCaptain()->NotifyOne();
#endif
}
