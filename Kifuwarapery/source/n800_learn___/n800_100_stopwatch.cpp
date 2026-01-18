#include "../../header/n800_learn___/n800_100_stopwatch.hpp"


/// <summary>
/// 再スタート☆
/// </summary>
void Stopwatch::restart()
{
	this->m_start_ = std::chrono::system_clock::now();
}


/// <summary>
/// 経過ミリ秒☆
/// </summary>
/// <returns></returns>
int Stopwatch::getElapsed() const
{
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;
	return static_cast<int>(
		duration_cast<milliseconds>(
			std::chrono::system_clock::now() - this->m_start_
		).count()
	);
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
Stopwatch Stopwatch::createStopwatchByCurrentTime()
{
	Stopwatch t;
	t.restart();
	return t;
}
