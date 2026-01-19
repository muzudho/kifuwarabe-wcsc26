#pragma once


#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../n223_move____/n223_200_depth.hpp"


/// <summary>
/// 
/// </summary>
class FutilityMargins {


public:


	/// <summary>
	/// [depth][moveCount]
	/// </summary>
	Sweetness m_FutilityMargins[16][64];


public:


	/// <summary>
	/// 
	/// </summary>
	void Initialize();


	/// <summary>
	/// Search関数で使う。
	/// </summary>
	/// <param name="depth"></param>
	/// <param name="moveCount"></param>
	/// <returns></returns>
	inline Sweetness GetFutilityMargin(const Depth depth, const int moveCount) {
		return (depth < 7 * OnePly ?
			this->m_FutilityMargins[std::max(depth, Depth1)][std::min(moveCount, 63)]
			: 2 * SweetnessInfinite);
	}
};


/// <summary>
/// 
/// </summary>
extern FutilityMargins g_futilityMargins;
