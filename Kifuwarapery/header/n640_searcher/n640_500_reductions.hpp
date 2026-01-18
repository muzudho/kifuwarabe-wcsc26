#pragma once


#include <algorithm>
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n223_move____/n223_200_depth.hpp"


/// <summary>
/// 
/// </summary>
class Reductions {


public:


	/// <summary>
	/// [pv][depth][moveNumber]
	/// </summary>
	s8 m_reductions[2][64][64];


public:


	void Initialize();


	inline Depth DoReduction(
		bool PVNode,
		const Depth depth, const int moveCount
	) {
		return static_cast<Depth>(this->m_reductions[PVNode][std::min(Depth(depth / OnePly), Depth(63))][std::min(moveCount, 63)]);
	}


	inline Depth DoReduction_PvNode(
		const Depth depth, const int moveCount
		) {
		return static_cast<Depth>(this->m_reductions[true//PVNode
		][std::min(Depth(depth / OnePly), Depth(63))][std::min(moveCount, 63)]);
	}


	inline Depth DoReduction_NotPvNode(
		const Depth depth, const int moveCount
		) {
		return static_cast<Depth>(this->m_reductions[false//not PVNode
		][std::min(Depth(depth / OnePly), Depth(63))][std::min(moveCount, 63)]);
	}
};


/// <summary>
/// 
/// </summary>
extern Reductions g_reductions;
