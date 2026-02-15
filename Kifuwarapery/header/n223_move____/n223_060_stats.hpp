#pragma once

#include "../../src/lib_toybox_base/square.hpp"
#include "../n105_120_square__/n105_120_500_convSquare.hpp"
#include "../../src/lib_toybox_base/piece.hpp"
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"


/// <summary>
/// 
/// </summary>
/// <typeparam name="Gain"></typeparam>
template <bool Gain>
class Stats {
public:


	/// <summary>
	/// 
	/// </summary>
	static const Sweetness m_maxSweetness = static_cast<Sweetness>(2000);


	/// <summary>
	/// 
	/// </summary>
	void Clear() { memset(this->m_table_, 0, sizeof(this->m_table_)); }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isDrop"></param>
	/// <param name="pc"></param>
	/// <param name="to"></param>
	/// <returns></returns>
	Sweetness GetValue(const bool isDrop, const Piece pc, const Square to) const {
		assert(0 < pc && pc < N31_PieceNone);
		assert(ConvSquare::CONTAINS_OF10(to));
		return this->m_table_[isDrop][pc][to];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isDrop"></param>
	/// <param name="pc"></param>
	/// <param name="to"></param>
	/// <param name="s"></param>
	void Update(const bool isDrop, const Piece pc, const Square to, const Sweetness s) {
		if (Gain) {
			this->m_table_[isDrop][pc][to] = std::max(s, GetValue(isDrop, pc, to) - 1);
		}
		else if (abs(GetValue(isDrop, pc, to) + s) < m_maxSweetness) {
			this->m_table_[isDrop][pc][to] += s;
		}
	}


private:


	/// <summary>
	/// [isDrop][piece][square] とする。
	/// </summary>
	Sweetness m_table_[2][N31_PieceNone][SquareNum];
};
