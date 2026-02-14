#include <iostream>
#include "../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../header/n160_board___/n160_100_bitboard.hpp"
#include "../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../header/n480_tt______/n480_300_tt.hpp"
#include "../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../header/n160_board___/n160_110_silverAttackBb.hpp"
#include "../header/n160_board___/n160_120_bishopAttackBb.hpp"
#include "../header/n160_board___/n160_130_lanceAttackBb.hpp"
#include "../header/n160_board___/n160_140_goldAttackBb.hpp"
#include "../header/n160_board___/n160_150_rookAttackBb.hpp"
#include "../header/n160_board___/n160_160_kingAttackBb.hpp"
#include "../header/n160_board___/n160_180_knightAttackBb.hpp"
#include "../header/n160_board___/n160_190_pawnAttackBb.hpp"
#include "../header/n161_sqDistan/n161_500_squareDistance.hpp"
#include "../header/n163_sqDistan/n163_600_utilSquareDistance.hpp"
#include "../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../header/n600_book____/n600_500_book.hpp"
#include "../header/n900_main____/n900_300_usiLoop.hpp"
#include "../src/game_engine_layer/game_engine_storage.hpp"
#include "../src/game_engine.hpp"
#include "../src/main.hpp"


#if defined FIND_MAGIC


	/// <summary>
	/// Magic Bitboard の Magic Number を求める為のソフト
	/// </summary>
	/// <returns></returns>
	int main01() {
		u64 g_rookMagic[SquareNum];
		u64 g_bishopMagic[SquareNum];

		std::cout << "const u64 RookMagic[81] = {" << std::endl;
		for (Square sq = I9; sq < SquareNum; ++sq) {
			g_rookMagic[sq] = findMagic(sq, false);
			std::cout << "\tUINT64_C(0x" << std::hex << g_rookMagic[sq] << ")," << std::endl;
		}
		std::cout << "};\n" << std::endl;

		std::cout << "const u64 BishopMagic[81] = {" << std::endl;
		for (Square sq = I9; sq < SquareNum; ++sq) {
			g_bishopMagic[sq] = findMagic(sq, true);
			std::cout << "\tUINT64_C(0x" << std::hex << g_bishopMagic[sq] << ")," << std::endl;
		}
		std::cout << "};\n" << std::endl;

		return 0;
	}

#else

	/// <summary>
	/// 将棋を指すエンジン
	/// </summary>
	/// <param name="argc"></param>
	/// <param name="argv"></param>
	/// <returns></returns>
	int main(int argc, char* argv[])
	{
		GameEngineShogi main01;
		main01.initialize_10a();
		main01.body_50a(argc, argv);
		main01.finalize_90a();
	}

#endif
