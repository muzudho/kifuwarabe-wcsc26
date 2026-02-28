#pragma once

#include "../n95a55b_toybox_94c_board/muz_board_model.hpp"
#include "../n95a55b_toybox_95c_hand_stand/muz_hand_stand_collection_model.hpp"
#include "../n95a55b_toybox_103c_ply/muz_ply_model.hpp"
#include "../n95a55b_toybox_103c_ply/ply.hpp"
#include "../n95a55b_toybox_105c_turn/color.hpp"
#include "../n95a55b_toybox_105c_turn/muz_turn_model.hpp"
#include <string_view>

class MuzPositionModel
{


	// ========================================
	// 生成／破棄
	// ========================================


public:
    MuzPositionModel();


	// ========================================
	// 定数
	// ========================================


	/// <summary>
	/// 平手初期局面の SFEN 文字列☆（＾▽＾）
	/// </summary>
	const std::string g_SFEN_STARTPOS_STR = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";


	// ========================================
	// フィールド
	// ========================================

private:     
	/// <summary>
	/// 盤の状態を表すぜ（＾～＾）
	/// </summary>
	MuzBoardModel board_;

	/// <summary>
	/// 先手、後手の駒台をまとめて表すぜ（＾～＾） SFEN 形式がそうなってるから（＾～＾）
	/// </summary>
	MuzHandStandCollectionModel hand_stand_collection_;

	/// <summary>
	///		<pre>
	/// 将棋式の手数、つまり開始局面を０とする。
	/// 
	///		- ストックフィッシュでも実装は同じで変数名は `gamePly`。
	///		- 時間管理の役に立つ。
	///		</pre>
	/// </summary>
	MuzPlyModel ply_obj_;

	/// <summary>
	/// 手番
	/// </summary>
	MuzTurnModel turn_;


	// ========================================
	// アクセッサー
	// ========================================


public:
	/// <summary>
	/// 盤。
	/// </summary>
	/// <returns></returns>
	const MuzBoardModel& get_board() const;
	MuzBoardModel& get_board();

	/// <summary>
	/// 駒台。
	/// </summary>
	/// <returns></returns>
	const MuzHandStandCollectionModel& get_hand_stand_collection() const { return this->hand_stand_collection_; }
	MuzHandStandCollectionModel& get_hand_stand_collection() { return this->hand_stand_collection_; }

	/// <summary>
	/// 手数オブジェクトを取得。
	/// </summary>
	/// <returns></returns>
	const MuzPlyModel& get_ply_obj() const { return this->ply_obj_; }
	MuzPlyModel& get_ply_obj() { return this->ply_obj_; }

	/// <summary>
	/// ［将棋式の手数、つまり開始局面を０とする］を取得。
	/// </summary>
	/// <returns></returns>
	RadixHalfPly get_radix_half_ply() { return this->get_ply_obj().get_radix_half_ply(); }

	/// <summary>
	/// 手番。
	/// </summary>
	/// <returns></returns>
	const MuzTurnModel& get_turn() const { return this->turn_; }
	MuzTurnModel& get_turn() { return this->turn_; }

	/// <summary>
	/// 手番の色。
	/// </summary>
	/// <returns></returns>
	Color get_turn_color() const { return this->get_turn().get_color(); }


	// ========================================
	// 主要メソッド
	// ========================================


	/// <summary>
	///     <pre>
	/// 局面をセット
	/// 
	///     - 旧名： `Position::set()`
	///     </pre>
	/// </summary>
	/// <param name="sfen"></param>
	void Set(std::string_view sfen);
};
