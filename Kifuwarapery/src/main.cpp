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
		MyGameEngineModel gameEngine;
		gameEngine.initialize_10a();
		gameEngine.body_50a(argc, argv);
		gameEngine.finalize_90a();
	}

#endif
