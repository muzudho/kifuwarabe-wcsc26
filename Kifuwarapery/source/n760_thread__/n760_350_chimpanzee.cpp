#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n760_thread__/n760_350_chimpanzee.hpp"
#include "../../src/concept_game_engine/muz_game_engine_storage_model.hpp"


// ========================================
// メイン・メソッド
// ========================================


/// <summary>
/// ワーカースレッド開始
/// </summary>
void Chimpanzee::workAsMonkey() {
	while (!this->m_isEndOfSearch) {
		{
			std::unique_lock<Mutex> lock(this->m_sleepLock);
			if (!this->m_isEndOfSearch)
			{
				// ずっと寝る？？（＾ｑ＾）？
				m_sleepCond.wait_for(lock, std::chrono::milliseconds(
					this->m_lifetimeMilliseconds ? this->m_lifetimeMilliseconds : INT_MAX));
			}
		}
		if (this->m_lifetimeMilliseconds) {
			this->m_pOurCarriage->CheckTime();
		}
	}
}
