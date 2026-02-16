#include "../../header/n350_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n760_thread__/n760_250_monkie.hpp"
#include "../../header/n760_thread__/n760_300_orangutan.hpp"
#include "../../src/concept_game_engine/muz_game_engine_storage_model.hpp"


// ========================================
// メイン・メソッド
// ========================================


/// <summary>
/// ワーカースレッド開始☆（＾～＾）
/// </summary>
void Orangutan::workAsMonkey() {
	while (true) {// エグジットするまで　ずっといるぜ☆
		{
			std::unique_lock<Mutex> lock(this->m_sleepLock);
			this->m_isMasterThread = false;
			while (!this->m_isMasterThread && !m_isEndOfSearch)
			{
				// UI 関連だから要らないのかも。
				this->m_pOurCarriage->m_pub.m_sleepCond_.notify_one();
				this->m_sleepCond.wait(lock);
			}
		}

		if (this->m_isEndOfSearch) { return; }

		this->m_isBeingSearched = true;
		AdventureContinent::ExploreContinent(*this->m_pOurCarriage);
		assert(this->m_isBeingSearched);
		this->m_isBeingSearched = false;
	}
}
