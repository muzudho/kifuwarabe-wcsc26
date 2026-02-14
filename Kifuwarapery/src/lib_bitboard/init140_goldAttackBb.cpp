#include "n160_106_inFrontMaskBb.hpp"
#include "init140_goldAttackBb.hpp"
#include "init150_rookAttackBb.hpp"
#include "init160_kingAttackBb.hpp"
#include "n160_230_setMaskBb.hpp"
#include "n160_400_printBb.hpp"


/// <summary>
/// 本当はconst にしたいが、やり方がわからない☆ C2373エラーになるんだぜ☆
/// </summary>
GoldAttackBb g_goldAttackBb;


/// <summary>
/// 
/// </summary>
void GoldAttackBb::initialize_10a140b_goldAttacks()
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
void GoldAttackBb::Initialize_10a240b_checkTableGold() {
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
