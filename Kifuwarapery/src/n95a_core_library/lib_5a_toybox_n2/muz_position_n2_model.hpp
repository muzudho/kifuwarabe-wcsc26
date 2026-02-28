#pragma once

// MuzPositionN2Model では使ってないヘッダーファイルでも、他のクラスが MuzPositionN2Model をインクルードすれば lib_5a_toybox_n2 のヘッダーファイルが全部付いてくるようにします。
#include "../lib_5a_toybox_n1/muz_position_n1_model.hpp"
#include "../n95a55b_toybox_94c_board/char_to_piece_usi.hpp"
#include "hand_piece_ope.hpp"
#include "piece_ope.hpp"
#include "piece_types.hpp"
#include "piece_type_ope.hpp"

class MuzPositionN2Model : public MuzPositionN1Model
{


protected:
	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// 先後対局者別の手駒
	/// </summary>
	MuzHandStandModel m_hand_stands_[g_COLOR_NUM];


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// 持ち駒
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <returns></returns>
	template<Color CLR>
	MuzHandStandModel GetHandStand() const
	{
		return this->m_hand_stands_[CLR];
	}
	MuzHandStandModel GetHandStand(const Color c) const;
};
