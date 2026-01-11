#include <numeric>  // accumulate用
#include <algorithm>	// for std::min
#include "../../header/n220_position/n220_645_gameStats.hpp"


// ========================================
// 軽い生成／破棄
// ========================================


/// <summary>
/// 生成
/// </summary>
GameStats::GameStats()
{
	this->Clear();
}


// ========================================
// アクセッサ
// ========================================


/// <summary>
///		<pre>
/// btime, wtime コマンドをそのまま受け取るぜ☆（＾ｑ＾）
///		</pre>
/// </summary>
/// <param name="us"></param>
/// <param name="ssCmd"></param>
void GameStats::SetTimeLeftFromStream(Color us, long long milliseconds)
{
	this->m_times[us].push_back(milliseconds);
}


// ========================================
// メイン・メソッド
// ========================================


/// <summary>
/// クリアー
/// </summary>
void GameStats::Clear() {
	// vectorを明示的にクリア（これがないとヤバいぜ）。
	this->m_times.clear();		// 全要素削除（size=0）
	this->m_times.resize(2);	// 黒番、白番、２つの空ベクターを作った。
}


/// <summary>
/// １手に何秒使うか予測します。
/// </summary>
/// <param name="c"></param>
long long GameStats::GetPredictPayMilliseconds(Color c)
{
	std::vector<long long> msecVec = this->m_times[c];

	if (msecVec.empty()) { return 0; }

	std::vector<long long> sampleMsecVec;  // 直近5手分の消費時間（ミリ秒）

	for (int i = 0; i < std::min(static_cast<size_t>(5), msecVec.size()); i++)
	{
		sampleMsecVec.push_back(msecVec[i]);
	}

	long long sum = std::accumulate(sampleMsecVec.begin(), sampleMsecVec.end(), 0LL);
	return sum / sampleMsecVec.size();
}
