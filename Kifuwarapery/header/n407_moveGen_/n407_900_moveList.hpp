#pragma once

#include "../n165_movStack/n165_300_movegenType.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n250_pieceTyp/n350_030_makePromoteMove.hpp"
#include "n407_800_moveGenerator200.hpp"


/// <summary>
/// 
/// </summary>
/// <typeparam name="MT"></typeparam>
template <MovegenType MT>
class MoveList {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	explicit MoveList(const Position& pos) :
		m_curr_(m_moveStackList_), m_last_(g_moveGenerator200.GenerateMoves_2(MT,m_moveStackList_, pos)) {}


	/// <summary>
	/// 
	/// </summary>
	void operator ++ () { ++m_curr_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool IsEnd() const { return (m_curr_ == m_last_); }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Move GetMove() const { return m_curr_->m_move; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t GetSize() const { return static_cast<size_t>(m_last_ - m_moveStackList_); }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	bool Contains(const Move move) const {
		for (const MoveStack* it(m_moveStackList_); it != m_last_; ++it) {
			if (it->m_move == move) {
				return true;
			}
		}
		return false;
	}


private:


	/// <summary>
	/// 
	/// </summary>
	MoveStack m_moveStackList_[Move::m_MAX_LEGAL_MOVES];

	/// <summary>
	/// 
	/// </summary>
	MoveStack* m_curr_;

	/// <summary>
	/// 
	/// </summary>
	MoveStack* m_last_;
};
