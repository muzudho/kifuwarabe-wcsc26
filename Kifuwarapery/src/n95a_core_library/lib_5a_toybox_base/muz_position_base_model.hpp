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
	/// ゲームエンジン倉庫
	/// </summary>
	MuzGameEngineStorageModel* gameEngineStore__;


	// ========================================
	// アクセッサ
	// ========================================


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

};

