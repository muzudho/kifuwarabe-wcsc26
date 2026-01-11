#pragma once

#include "../n080_common__/n080_100_common.hpp"
#include "../n105_color___/n105_100_color.hpp"


/// <summary>
/// 対局の統計データ
/// </summary>
class GameStats
{


public:


	// ========================================
	// 軽い生成／破棄
	// ========================================


	/// <summary>
	/// 生成
	/// </summary>
	GameStats();


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
	void SetTimeLeftFromStream(Color us, long long milliseconds);


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// クリアー
	/// </summary>
	void Clear();


	/// <summary>
	/// １手に何ミリ秒使うか予測します。
	/// </summary>
	/// <param name="c"></param>
	long long GetPredictPayMilliseconds(Color c);


private:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///		<pre>
	/// TODO: (2026-01-12-mon) 時間管理のために、相手の消費時間の移動平均を取りたいんで、残り時間を記憶していきたいぜ（＾～＾）
	/// 
	///		btime, wtime を単純に記憶していくだけでもいいと思うが……☆（＾～＾）
	///		</pre>
	/// </summary>
	std::vector<std::vector<long long>> m_times = {};


};
