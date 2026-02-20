//
// 📄 局面の状態を表すクラス
//

#pragma once

#include "../../src/concept_game_engine/muz_game_engine_storage_model.hpp"
#include "char_to_piece_usi.hpp"
#include "color.hpp"
#include "ply.hpp"
#include "piece.hpp"
#include "hand.hpp"
#include "square.hpp"

class MuzPositionBaseModel
{


protected:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// 何手目か。時間管理に使用する
	/// </summary>
	Ply m_gamePly_;

	/// <summary>
	/// 手番
	/// </summary>
	Color m_turn_;

	/// <summary>
	/// 各マスの駒
	/// </summary>
	Piece m_piece_[SquareNum];

	/// <summary>
	/// 先後対局者別の手駒
	/// </summary>
	Hand m_hand_[g_COLOR_NUM];

	/// <summary>
	/// ゲームエンジン倉庫
	/// </summary>
	MuzGameEngineStorageModel* m_pGameEngineStore_;


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// 次の手番
	/// </summary>
	/// <returns></returns>
	Color GetTurn() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Ply GetGamePly() const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ply"></param>
	void SetStartPosPly(const Ply ply);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	Piece GetPiece(const Square sq) const;


	/// <summary>
	/// 持ち駒
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <returns></returns>
	template<Color CLR>
	Hand GetHand() const
	{
		return this->m_hand_[CLR];
	}
	Hand GetHand(const Color c) const;


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

