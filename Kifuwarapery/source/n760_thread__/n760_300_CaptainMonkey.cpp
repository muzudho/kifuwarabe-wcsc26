#include "../../header/n250_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n760_thread__/n760_250_Monkey.hpp"
#include "../../header/n760_thread__/n760_300_Orangutans.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


// ========================================
// メイン・メソッド
// ========================================


/// <summary>
/// ワーカースレッド開始☆（＾～＾）
/// </summary>
void Orangutans::startMonkey_n10() {
	while (true) {// エグジットするまで　ずっといるぜ☆
		{
			std::unique_lock<Mutex> lock(this->m_sleepLock);
			this->m_isMasterThread = false;
			while (!this->m_isMasterThread && !m_isEndOfSearch)
			{
				// UI 関連だから要らないのかも。
				this->m_pOurCarriage->m_monkiesPub.m_sleepCond_.notify_one();
				this->m_sleepCond.wait(lock);
			}
		}

		if (this->m_isEndOfSearch) { return; }

		this->m_isBeingSearched = true;
		AdventureContinent::exploreContinent_n10(*this->m_pOurCarriage);
		assert(this->m_isBeingSearched);
		this->m_isBeingSearched = false;
	}
}
