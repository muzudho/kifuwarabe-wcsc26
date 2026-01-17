#include <iostream>
#include <fstream>
#include <sstream>
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n560_timeMgr_/n560_100_limitsDuringGo.hpp"
#include "../../header/n720_usi_____/n720_260_usiOperation.hpp"
#include "../../header/n720_usi_____/n720_300_benchmark.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


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
		pos.getOurCarriage()->SetOption(is);
	}

	std::ifstream ifs("benchmark.sfen");
	std::string sfen;
	UsiOperation usiOperation;
	while (std::getline(ifs, sfen)) {
		std::cout << sfen << std::endl;
		std::istringstream ss_sfen(sfen);

		usiOperation.SetPositionToOrangutans(pos, ss_sfen);

		std::istringstream ss_go("byoyomi 10000");
		usiOperation.Go(gameStats, pos, ss_go);
		pos.getOurCarriage()->m_monkiesPub.WaitForThinkFinished();
	}
}
