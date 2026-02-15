#include <iostream>
#include <fstream>
#include <sstream>
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../../header/n560_timeMgr_/n560_100_limitsDuringGo.hpp"
#include "../../header/n720_usi_____/n720_260_usiOperation.hpp"
#include "../../header/n720_usi_____/n720_300_benchmark.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"


/// <summary>
/// 今はベンチマークというより、PGO ビルドの自動化の為にある。
/// </summary>
/// <param name="pos"></param>
void Benchmark(GameStats& gameStats, Position& pos) {
	std::string token;
	LimitsDuringGo limits;

	std::string options[] = {"name Threads value 1",
							 "name MultiPV value 1",
							 "name OwnBook value false",
							 "name Max_Random_Score_Diff value 0"};
	for (auto& str : options) {
		std::istringstream is(str);
		pos.GetOurCarriage()->SetOption(is);
	}

	std::ifstream ifs("benchmark.sfen");
	std::string sfen;
	UsiOperation usiOperation;
	while (std::getline(ifs, sfen)) {
		std::cout << sfen << std::endl;
		std::istringstream ss_sfen(sfen);

		usiOperation.SetPosition(pos, ss_sfen);

		std::istringstream ss_go("byoyomi 10000");
		usiOperation.Go(gameStats, pos, ss_go);
		pos.GetOurCarriage()->m_pub.WaitForThinkFinished();
	}
}
