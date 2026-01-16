#include "../../header/n130_100_boardBb_/n160_106_inFrontMaskBb.hpp"
#include "../../header/n130_100_boardBb_/n160_140_goldAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_150_rookAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_160_kingAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_230_setMaskBb.hpp"
#include "../../header/n130_100_boardBb_/n160_400_printBb.hpp"


/// <summary>
/// 本当はconst にしたいが、やり方がわからない☆ C2373エラーになるんだぜ☆
/// </summary>
GoldAttackBb g_goldAttackBb;


/// <summary>
/// 
/// </summary>
void GoldAttackBb::Initialize()
{
	for (Color c = Black; c < g_COLOR_NUM; ++c)
		for (Square sq = I9; sq < SquareNum; ++sq)
			g_goldAttackBb.m_controllBb_[c][sq] =
			(
				g_kingAttackBb.GetControllBb(sq) &
				g_inFrontMaskBb.GetInFrontMask(c, ConvSquare::TO_RANK10(sq))
			) |
			g_rookAttackBb.GetControllBb(Bitboard::CreateAllOneBB(), sq);
}


/// <summary>
/// 王手？テーブル・ビットボード初期化
/// </summary>
void GoldAttackBb::InitCheckTableGold() {
	for (Color c = Black; c < g_COLOR_NUM; ++c) {	// 手番の色
		const Color opp = ConvColor::OPPOSITE_COLOR10b(c);	// 相手の色☆（＾ｑ＾）
		for (Square sq = I9; sq < SquareNum; ++sq) {

			g_goldAttackBb.m_goldCheckTable_[c][sq] = Bitboard::CreateAllZeroBB();	// 空ビットボード

			Bitboard checkBB = g_goldAttackBb.GetControllBb(opp, sq);
			while (checkBB.Exists1Bit()) {
				const Square checkSq = checkBB.PopFirstOneFromI9();
				g_goldAttackBb.m_goldCheckTable_[c][sq] |= g_goldAttackBb.GetControllBb(opp, checkSq);
			}
			g_goldAttackBb.m_goldCheckTable_[c][sq].AndEqualNot(g_setMaskBb.GetSetMaskBb(sq) | g_goldAttackBb.GetControllBb(opp, sq));
		}
	}
}
