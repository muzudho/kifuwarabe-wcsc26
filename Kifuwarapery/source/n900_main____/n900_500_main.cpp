#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n480_tt______/n480_300_tt.hpp"
#include "../../header/n760_thread__/n760_400_herosPub.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"
#include "../../header/n900_main____/n900_400_main01.hpp"


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
/// 将棋を指すソフト
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[]) {
	Main01 main01;
	main01.initialize_app10();
	main01.body_app10(argc, argv);
	main01.finalize_app10();
}


#endif

