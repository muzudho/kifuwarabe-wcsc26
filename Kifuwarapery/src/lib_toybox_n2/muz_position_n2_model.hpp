#pragma once

#include "hand_piece_ope.hpp"
#include "piece_ope.hpp"
#include "../lib_toybox_n1/muz_hand_n1_model.hpp"
#include "../lib_toybox_n1/muz_position_n1_model.hpp"
#include "../lib_toybox_n1/piece_type.hpp"

class MuzPositionN2Model : public MuzPositionN1Model
{


protected:
	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// 先後対局者別の手駒
	/// </summary>
	MuzHandN1Model m_hand_models_[g_COLOR_NUM];


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// 持ち駒
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <returns></returns>
	template<Color CLR>
	MuzHandN1Model GetHand() const
	{
		return this->m_hand_models_[CLR];
	}
	MuzHandN1Model GetHand(const Color c) const;

	void SetHand(const Piece piece, const int num);

	void SetHand(const HandPiece hp, const Color c, const int num);
};
