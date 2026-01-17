#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n165_movStack/n165_300_movegenType.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n407_moveGen_/n407_900_moveList.hpp"
#include "../../header/n560_timeMgr_/n560_100_limitsDuringGo.hpp"
#include "../../header/n640_searcher/n640_450_rootMove.hpp"
#include "../../header/n760_thread__/n760_250_Monkey.hpp"
#include "../../header/n760_thread__/n760_400_MonkiesPub.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


// ========================================
// メイン・メソッド
// ========================================


//namespace {


/// <summary>
/// ワーカースレッド開始
/// </summary>
/// <typeparam name="T">キャプテン猿か、お使い猿</typeparam>
/// <param name="s"></param>
/// <returns></returns>
template <typename MONKT> MONKT* newMonkeyWithThread(OurCarriage* s) {
	MONKT* monkey = new MONKT(s);
	monkey->m_threadHandle = std::thread(&Monkey::startMonkey_n10, monkey); // move constructor
	return monkey;
}


/// <summary>
/// 
/// </summary>
/// <param name="th"></param>
void deleteThread(Monkey* th) {
	th->m_isEndOfSearch = true;
	th->NotifyOne();
	th->m_threadHandle.join(); // Wait for thread termination
	delete th;
}


//}


/// <summary>
/// 最初の設定（初期化）を行うぜ☆（＾▽＾）
/// </summary>
/// <param name="s"></param>
void MonkiesPub::initializeMonkiePub_app10(OurCarriage* s)
{
	// 寝るフラグ？
	this->m_idleMonkeyIsSleep_ = true;

	#if defined LEARN
	#else
		// お使い猿
		this->m_pErrandMonkey_ = newMonkeyWithThread<Chimpanzee>(s);
	#endif

	// キャプテン猿
	this->m_defaultMonkies.push_back(newMonkeyWithThread<Orangutans>(s));

	newAllMonkiesByUSIOptions(s);
}


/// <summary>
/// 
/// </summary>
void MonkiesPub::Exit() {
	#if defined LEARN
	#else
		// checkTime() がデータにアクセスしないよう、先に timer_ を delete
		deleteThread(m_pErrandMonkey_);
	#endif

	for (auto monkey : (*this).m_defaultMonkies) {
		deleteThread(monkey);
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="searcher"></param>
void MonkiesPub::newAllMonkiesByUSIOptions(OurCarriage* pOurCarriage) {

	this->m_maxThreadsPerSplitedNode_ = pOurCarriage->m_engineOptions["Max_Threads_per_Split_Point"];

	// 猿（スレッド）の個数（１以上）
	const size_t numberOfMonkies   = pOurCarriage->m_engineOptions["Threads"];

	this->m_minimumSplitDepth_ = (
		numberOfMonkies < 6 ?
			4 :
			(numberOfMonkies < 8 ?
				5 :
				7
			)
	) * OnePly;
	assert(0 < numberOfMonkies);

	// 猿で埋める
	while (this->m_defaultMonkies.size() < numberOfMonkies)
	{
		this->m_defaultMonkies.push_back(newMonkeyWithThread<Monkey>(pOurCarriage));
	}

	// 多すぎる猿は消す
	while (numberOfMonkies < this->m_defaultMonkies.size())
	{
		deleteThread(this->m_defaultMonkies.back());
		this->m_defaultMonkies.pop_back();
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="master"></param>
/// <returns></returns>
Monkey* MonkiesPub::GetAvailableSlave(Monkey* master) const {
	for (auto elem : (*this).m_defaultMonkies) {
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
	m_pErrandMonkey_->m_maxPly = maxPly;
	m_pErrandMonkey_->NotifyOne(); // Wake up and restart the timer
}


/// <summary>
/// 
/// </summary>
void MonkiesPub::WaitForThinkFinished()
{
	Orangutans* t = GetFirstCaptain();
	std::unique_lock<Mutex> lock(t->m_sleepLock);
	m_sleepCond_.wait(lock, [&] { return !(t->m_isMasterThread); });
}


/// <summary>
/// 思考開始
/// </summary>
/// <param name="position"></param>
/// <param name="limits"></param>
/// <param name="searchMoves">探索する指し手一覧（＾～＾）？</param>
void MonkiesPub::startClimbingTree_n10(
	const GameStats& gameStats,
	const Position& position,
	const LimitsDuringGo& limits,
	const std::vector<Move>& searchMoves)
{
	#if defined LEARN
	#else
		// 考え終わるのを待っている（＾～＾）？
		WaitForThinkFinished();
	#endif

	// ストップウォッチ計測開始
	position.getOurCarriage()->m_stopwatch.Restart();

	// 以下を偽にする
	//		- ポンダーヒット
	//		- 初手
	//		- 停止信号
	//		- 根のフェイルド・ロウ
	position.getOurCarriage()->m_signals.m_isStopOnPonderHit
		= position.getOurCarriage()->m_signals.m_isFirstRootMove
			= position.getOurCarriage()->m_signals.m_isStop
				= position.getOurCarriage()->m_signals.m_isFailedLowAtRoot
					= false;

	// 対局データ
	position.getOurCarriage()->m_gameStats = gameStats;

	// 根局面
	position.getOurCarriage()->m_rootPosition = position;

	// リミットデータ
	position.getOurCarriage()->m_limits = limits;

	// 根の指し手リスト初期化
	position.getOurCarriage()->m_rootMovesByID.clear();


	#if defined LEARN


		// searchMoves を直接使う。
		GetPos.getOurCarriage()->m_rootMoves.push_back(RootMove(position.GetRucksack()->m_ourMoves[0]));

		// 浅い探索なので、thread 生成、破棄のコストが高い。余分な thread を生成せずに直接探索を呼び出す。
		GetPos.getOurCarriage()->Think(GetPos.GetRucksack());


	#else


		const MovegenType MT = N08_Legal;

		// この局面の全ての指し手（＾～＾）？
		for (DeliciousBananaCollection<MT> deliBananaCol(position); !deliBananaCol.IsEnd(); ++deliBananaCol) {

			if (
				// 探索する指し手一覧が空か（＾～＾）？
				searchMoves.empty()
				||
				// この局面の指し手の１つは、探索する指し手の最後の要素ではないとき（＾～＾）？
				std::find(searchMoves.begin(), searchMoves.end(), deliBananaCol.GetMove()) != searchMoves.end())
			{
				// ルート・ムーブスの末尾に指し手を追加している（＾～＾）？
				position.getOurCarriage()->m_rootMovesByID.push_back(RootMove(deliBananaCol.GetMove()));
			}
		}

		// マスタースレッドだというフラグを立てる（＾～＾）？
		this->GetFirstCaptain()->m_isMasterThread = true;

		// フラグを立てた後に、通知してる（＾～＾）？
		this->GetFirstCaptain()->NotifyOne();


	#endif
}
