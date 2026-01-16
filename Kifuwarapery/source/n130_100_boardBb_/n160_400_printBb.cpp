#include <iostream>
#include "../../header/n105_120_square__/n105_120_150_file.hpp"
#include "../../header/n105_120_square__/n105_120_200_rank.hpp"
#include "../../header/n105_120_square__/n105_120_500_convSquare.hpp"
#include "../../header/n130_100_boardBb_/n160_230_setMaskBb.hpp"
#include "../../header/n130_100_boardBb_/n160_400_printBb.hpp"


/// <summary>
/// 盤の出力。
/// </summary>
/// <param name="thisBitboard"></param>
void PrintBb::PrintBoard(const Bitboard* thisBitboard)// const
{
	std::cout << "   A  B  C  D  E  F  G  H  I\n";
	for (Rank r = Rank9; r < RankNum; ++r) {
		std::cout << (9 - r);
		for (File f = FileA; FileI <= f; --f) {
			std::cout << (g_setMaskBb.IsSet(thisBitboard, ConvSquare::FROM_FILE_RANK10(f, r)) ? "  X" : "  .");
		}
		std::cout << "\n";
	}

	std::cout << std::endl;
}


