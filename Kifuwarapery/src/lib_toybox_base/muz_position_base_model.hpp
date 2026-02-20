//
// 📄 局面の状態を表すクラス
//

#pragma once

#include "../../src/lib_cpp/int.hpp"
#include "../lib_toybox_v1/muz_position_n1_model.hpp"
#include "n1_hand_piece.hpp"
#include "n1_piece_type.hpp"
#include "n1_square_delta.hpp"
#include "n2_char_to_piece_usi.hpp"
#include "n2_hand_ope.hpp"
#include "n2_piece_ope.hpp"
#include "n3_hand_piece_ope.hpp"
#include "n3_square_ope.hpp"
#include <iostream>
#include <map>
#include <optional>
#include <ranges>         // C++20 ranges
#include <string>
#include <string_view>

class MuzPositionBaseModel : public MuzPositionN1Model
{


protected:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// 先後対局者別の手駒
	/// </summary>
	MuzHandModel m_hand_[g_COLOR_NUM];

	/// <summary>
	/// ゲームエンジン倉庫
	/// </summary>
	MuzGameEngineStorageModel* m_pGameEngineStore_;


	// ========================================
	// アクセッサ
	// ========================================


	void SetPiece(const Piece piece, const Square sq);

	/// <summary>
	/// 持ち駒
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <returns></returns>
	template<Color CLR>
	MuzHandModel GetHand() const
	{
		return this->m_hand_[CLR];
	}
	MuzHandModel GetHand(const Color c) const;


	/// <summary>
	/// ゲームエンジン倉庫を取得（const）
	/// </summary>
	/// <returns></returns>
	const MuzGameEngineStorageModel* GetConstGameEngineStore() const;


	/// <summary>
	/// ゲームエンジン倉庫を取得
	/// </summary>
	/// <returns></returns>
	MuzGameEngineStorageModel* GetGameEngineStore() const;


	/// <summary>
	/// ゲームエンジン倉庫をセット
	/// </summary>
	/// <param name="s"></param>
	void SetGameEngineStore(MuzGameEngineStorageModel* pGameEngineStore);


	// ========================================
	// 主要メソッド
	// ========================================


	/// <summary>
	/// 局面をセット
	/// </summary>
	/// <param name="sfen"></param>
	void Set(const std::string& sfen);
};

