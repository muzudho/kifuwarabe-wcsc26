#pragma once

// MuzPositionN2Model では使ってないヘッダーファイルでも、他のクラスが MuzPositionN2Model をインクルードすれば lib_toybox_n2 のヘッダーファイルが全部付いてくるようにします。
#include "../lib_toybox_n1/muz_position_n1_model.hpp"
#include "char_to_piece_usi.hpp"
#include "file_ope.hpp"
#include "hand_piece_ope.hpp"
#include "piece_ope.hpp"
#include "piece_types.hpp"
#include "piece_type_ope.hpp"
#include "rank_ope.hpp"
#include "squares.hpp"

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
