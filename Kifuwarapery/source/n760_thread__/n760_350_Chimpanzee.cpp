#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n760_thread__/n760_350_Chimpanzee.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


// ========================================
// メイン・メソッド
// ========================================


/// <summary>
/// 猿として働く（ワーカースレッド）
/// </summary>
void Chimpanzee::workAsMonkey_10a520b500c500d() {
	while (!this->m_isEndOfSearch)	// 探索が終わっていない間
	{
		{
			// ロックする
			std::unique_lock<Mutex> lock(this->m_sleepLock);

			// 探索が終わっていない間
			if (!this->m_isEndOfSearch)
			{
				// ずっと寝る？？（＾ｑ＾）？
				m_sleepCond.wait_for(lock, std::chrono::milliseconds(
					this->m_lifetimeMilliseconds ? this->m_lifetimeMilliseconds : INT_MAX));
			}
		}

		if (this->m_lifetimeMilliseconds) {
			this->m_pOurCarriage->ChimpanzeeStopped();
		}
	}
}
