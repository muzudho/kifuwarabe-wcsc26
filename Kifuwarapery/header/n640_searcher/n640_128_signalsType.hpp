#pragma once


/// <summary>
/// 信号タイプ。
/// </summary>
class SignalsType {


public:


	/// <summary>
    /// ポンダーヒットで探索を止めるかどうか☆
	/// </summary>
	bool m_isStopOnPonderHit;

	/// <summary>
	/// 
	/// </summary>
	bool m_isFirstRootMove;

	/// <summary>
	/// ［反復深化探索］を止める信号
	/// </summary>
	bool m_isIterationDeepingStop;

	/// <summary>
	/// 
	/// </summary>
	bool m_isFailedLowAtRoot;
};
