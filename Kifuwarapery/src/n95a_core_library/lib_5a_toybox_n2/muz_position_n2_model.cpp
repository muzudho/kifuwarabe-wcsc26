#include "muz_position_n2_model.hpp"


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
MuzHandStandModel MuzPositionN2Model::GetHandStand(const Color c) const
{
	return this->m_hand_stands_[c];
}
