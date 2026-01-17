#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n220_position/n220_750_charToPieceUSI.hpp"
#include "../n480_tt______/n480_300_tt.hpp"
#include "../n760_thread__/n760_400_monkiesPub.hpp"
#include "../n885_searcher/n885_040_ourCarriage.hpp"


/// <summary>
/// 
/// </summary>
class App10 {


public:

	/// <summary>
	/// Rucksack？ 探索者☆？（＾ｑ＾）
	/// </summary>
	std::unique_ptr<OurCarriage> searcher;


public:
	App10();
	~App10();
	void initialize_app10();
	void body_app10(int argc, char* argv[]);
	void finalize_app10();
};