#pragma once
#include "../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../header/n160_board___/n160_100_bitboard.hpp"
#include "../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../header/n480_tt______/n480_300_tt.hpp"
#include "../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../src/layer_game_engine/game_engine_storage.hpp"


/// <summary>
/// 
/// </summary>
class GameEngineShogi {


public:

	/// <summary>
	///		ゲームエンジンが１つだけ持つ、局面の探索状態を保存するクラス☆（＾ｑ＾）
	/// </summary>
	std::unique_ptr<GameEngineStorageOurCarriage> m_ourCarriage;


public:
	GameEngineShogi();
	~GameEngineShogi();
	void initialize_10a();
	void body_50a(int argc, char* argv[]);
	void finalize_90a();
};
