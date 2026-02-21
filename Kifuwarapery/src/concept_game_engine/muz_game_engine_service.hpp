#pragma once

#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../src/lib_bitboard/n160_100_bitboard.hpp"
#include "../../src/lib_toybox_base/char_to_piece_usi.hpp"
#include "../../header/n480_tt______/n480_300_tt.hpp"
#include "../../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../../src/concept_game_engine/muz_game_engine_storage_model.hpp"

/// <summary>
/// 
/// </summary>
class MuzGameEngineService
{


public:


	// ========================================
	// 生成／破棄
	// ========================================


	MuzGameEngineService();
	~MuzGameEngineService();


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///	ゲームエンジン倉庫☆（＾ｑ＾）
	///
	///    - ゲームエンジンが１つだけ持つ、局面の探索状態を保存するクラス☆（＾ｑ＾）
	/// </summary>
	std::unique_ptr<MuzGameEngineStorageModel> m_pGameEngineStore;


	// ========================================
	// ライフサイクルメソッド
	// ========================================


	void initialize_10a();
	void main_loop_50a(int argc, char* argv[]);
	void finalize_90a();
};
