#pragma once
#include <chrono>	// std::chrono

using namespace std;


/// <summary>
/// ミリ秒単位の時間を表すクラス
/// </summary>
class Stopwatch {


public:


	/// <summary>
	/// ストップ・ウォッチの再起動
	/// </summary>
	void Restart();


	/// <summary>
	/// 経過時間
	/// </summary>
	/// <returns></returns>
	int GetElapsed() const;


	/// <summary>
	/// 現在時刻で開始したストップ・ウォッチの取得
	/// </summary>
	/// <returns></returns>
	static Stopwatch CreateStopwatchByCurrentTime();


private:
	
	
	/// <summary>
	/// 開始時間（ミリ秒？）
	/// </summary>
	std::chrono::time_point<std::chrono::system_clock> m_start_;
};
