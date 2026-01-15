#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n160_boardBb_/n160_100_bitboard.hpp"
#include "../n220_position/n220_750_charToPieceUSI.hpp"
#include "../n480_tt______/n480_300_tt.hpp"
#include "../n760_thread__/n760_400_herosPub.hpp"
#include "../n885_searcher/n885_040_ourCarriage.hpp"


/// <summary>
/// 
/// </summary>
class Main01 {


public:

	/// <summary>
	/// Rucksack？ 探索者☆？（＾ｑ＾）
	/// </summary>
	std::unique_ptr<OurCarriage> searcher;


public:
	Main01();
	~Main01();
	void Initialize();
	void Body(int argc, char* argv[]);
	void Finalize();
};