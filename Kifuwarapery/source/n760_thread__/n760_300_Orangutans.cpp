#include "../../header/n250_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n760_thread__/n760_250_Monkey.hpp"
#include "../../header/n760_thread__/n760_300_Orangutans.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


// ========================================
// メイン・メソッド
// ========================================


/// <summary>
/// 猿として働く（ワーカースレッド）☆（＾～＾）
/// </summary>
void Orangutans::workAsMonkey_10a500b500c500d500e() {
	while (true)	// 探索が終わるまで　ずっといるぜ☆
	{
		{
			// ロック作成
			std::unique_lock<Mutex> lock(this->m_sleepLock);

			// マスタースレッドではない
			this->m_isMasterThread = false;

			// マスタースレッドではなく、探索の終わりでもない間
			while (!this->m_isMasterThread && !m_isEndOfSearch)
			{
				// UI 関連だから要らないのかも。
				this->m_pOurCarriage->m_monkiesPub.m_sleepCond_.notify_one();

				this->m_sleepCond.wait(lock);
			}
		}

		// 探索の終わりならループから抜ける
		if (this->m_isEndOfSearch) { return; }

		// 探索中だ
		this->m_isBeingSearched = true;

		// 大陸を大冒険だぜ（＾▽＾）！
		AdventureContinent::exploreContinent_n10(*this->m_pOurCarriage);
		assert(this->m_isBeingSearched);

		// 探索終わり（＾～＾）
		this->m_isBeingSearched = false;
	}
}
