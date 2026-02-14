#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n165_movStack/n165_300_moveType.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n407_moveGen_/n407_900_moveList.hpp"
#include "../../header/n560_timeMgr_/n560_100_limitsDuringGo.hpp"
#include "../../header/n640_searcher/n640_450_rootMove.hpp"
#include "../../header/n760_thread__/n760_250_monkie.hpp"
#include "../../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../../src/layer_game_engine/game_engine_storage.hpp"


// ========================================
// メイン・メソッド
// ========================================


//namespace {


/// <summary>
///		<pre>
/// スレッド・オブジェクトを作成するだけ
///		</pre>
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="s"></param>
/// <returns></returns>
template <typename MONKIE> MONKIE* newThread(MuzGameEngineStorage* s) {
	MONKIE* monkie = new MONKIE(s);
	monkie->m_handleThread = std::thread(&Monkie::workAsMonkey, monkie); // move constructor
	return monkie;
}


/// <summary>
/// 
/// </summary>
/// <param name="th"></param>
void deleteThread(Monkie* th) {
	th->m_isEndOfSearch = true;
	th->NotifyOne();
	th->m_handleThread.join(); // Wait for thread termination
	delete th;
}


//}


/// <summary>
///		<pre>
/// 主に、チンパンジーとオラウータンのスレッドを用意するぜ（＾～＾）
///		</pre>
/// </summary>
/// <param name="s"></param>
void MonkiesPub::initialize_10a520b500c(MuzGameEngineStorage* s)
{
	// 手の空いてる猿は寝てろ。
	m_isIdleMonkeyToSleep_ = true;


	#if defined LEARN
	#else
		// チンパンジーを作成
		m_pChimpanzee_ = newThread<Chimpanzee>(s);
	#endif


	// オラウータンを追加
	this->m_monkies.push_back(newThread<Orangutan>(s));

	ReadUSIOptions(s);
}


/// <summary>
/// 
/// </summary>
void MonkiesPub::exit_90a500b() {
#if defined LEARN
#else
	// checkTime() がデータにアクセスしないよう、先に timer_ を delete
	deleteThread(m_pChimpanzee_);
#endif

	for (auto elem : (*this).m_monkies) {
		deleteThread(elem);
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="m_pGameEngineStore"></param>
void MonkiesPub::ReadUSIOptions(MuzGameEngineStorage* m_pGameEngineStore) {

	this->m_maxThreadsPerMonkeySplitedPlace = m_pGameEngineStore->m_engineOptionCollection.m_map["Max_Threads_per_Split_Point"];

	// スレッドの個数（１以上）
	const size_t numberOfThreads   = m_pGameEngineStore->m_engineOptionCollection.m_map["Threads"];

	this->m_minimumSplitDepth_ = (
		numberOfThreads < 6 ?
			4 :
			(numberOfThreads < 8 ?
				5 :
				7
			)
	) * OnePly;
	assert(0 < numberOfThreads);

	while (this->m_monkies.size() < numberOfThreads) {
		this->m_monkies.push_back(newThread<Monkie>(m_pGameEngineStore));
	}

	while (numberOfThreads < this->m_monkies.size()) {
		deleteThread(this->m_monkies.back());
		this->m_monkies.pop_back();
	}
}


/// <summary>
///		<pre>
/// ヒマしてる猿を取得する（＾～＾）？
/// 
///		- 旧名： `GetAvailableSlave`
///		</pre>
/// </summary>
/// <param name="master"></param>
/// <returns></returns>
Monkie* MonkiesPub::GetBoredMonkey(Monkie* master) const {
	for (auto elem : (*this).m_monkies) {
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
	m_pChimpanzee_->m_maxPly = maxPly;
	m_pChimpanzee_->NotifyOne(); // Wake up and restart the timer
}


/// <summary>
/// 
/// </summary>
void MonkiesPub::WaitForThinkFinished()
{
	Orangutan* t = GetFirstCaptain();
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
	const MoveType MT = N08_Legal;
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
