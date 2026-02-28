#pragma once

// MuzPositionN1Model では使ってないヘッダーファイルでも、他のクラスが MuzPositionN1Model をインクルードすれば lib_5a_toybox_n1 のヘッダーファイルが全部付いてくるようにします。
#include "../n95a55b_toybox_94c_board/muz_board_model.hpp"
#include "../n95a55b_toybox_105c_turn/color.hpp"
#include "../n95a55b_toybox_105c_turn/muz_turn_model.hpp"
#include "../n95a55b_toybox_103c_ply/ply.hpp"
#include "piece_type.hpp"

class MuzPositionN1Model
{


protected:


	// ========================================
    // 生成／破棄
	// ========================================


	MuzPositionN1Model();


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
	MuzTurnModel turn_;

    /// <summary>
    /// ボードの状態を表すぜ（＾～＾）
    /// </summary>
	MuzBoardModel board_;


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ply"></param>
	void SetStartPosPly(const Ply ply);


	/// <summary>
	/// 何手目か
	/// </summary>
	/// <returns></returns>
	Ply GetGamePly();


	/// <summary>
	/// 次の手番
	/// </summary>
	/// <returns></returns>
	Color GetTurn();


    const MuzBoardModel& get_board() const { return this->board_; }
	MuzBoardModel& get_board() { return this->board_; }

	const MuzTurnModel& get_turn() const { return this->turn_; }
	MuzTurnModel& get_turn() { return this->turn_; }
};