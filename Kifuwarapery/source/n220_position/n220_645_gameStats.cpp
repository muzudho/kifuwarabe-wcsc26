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
