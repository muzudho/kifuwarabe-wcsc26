#include "../../header/n105_120_square__/n105_120_500_convSquare.hpp"
#include "../../header/n130_100_boardBb_/n160_400_printBb.hpp"
#include "../../header/n130_100_boardBb_/n160_106_inFrontMaskBb.hpp"
#include "../../header/n130_100_boardBb_/n160_120_bishopAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_140_goldAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_180_knightAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_190_pawnAttackBb.hpp"


/// <summary>
/// 本当はconst にしたいが、やり方がわからない☆ C2373エラーになるんだぜ☆
/// </summary>
KnightAttackBb g_knightAttackBb;


/// <summary>
/// 桂の利きを初期化するぜ☆（＾▽＾）
/// </summary>
void KnightAttackBb::Initialize()
{
	for (Color c = Black; c < g_COLOR_NUM; ++c) {
		for (Square sq = I9; sq < SquareNum; ++sq) {
			g_knightAttackBb.m_controllBb_[c][sq] = Bitboard::CreateAllZeroBB();
			const Bitboard bb = g_pawnAttackBb.GetControllBb(c, sq);
			if (bb.Exists1Bit())
				g_knightAttackBb.m_controllBb_[c][sq] =
					g_bishopAttackBb.BishopStepAttacks(
						bb.GetFirstOneFromI9()) &
						g_inFrontMaskBb.GetInFrontMask(c, ConvSquare::TO_RANK10(sq)
					);
		}
	}
}


/// <summary>
/// 桂の王手チェックテーブルを初期化するぜ☆（＾▽＾）
/// </summary>
void KnightAttackBb::InitCheckTableKnight() {
	for (Color color = Black; color < g_COLOR_NUM; ++color) {
		const Color opponent = ConvColor::OPPOSITE_COLOR10b(color);//色はループで交互になるぜ☆（＾ｑ＾）
		for (Square sq = I9; sq < SquareNum; ++sq) {
			this->m_knightCheckTable_[color][sq] = Bitboard::CreateAllZeroBB();

			// 相手の桂馬の利き
			Bitboard checkBB = this->GetControllBb(opponent, sq);
			while (checkBB.Exists1Bit()) {
				const Square checkSq = checkBB.PopFirstOneFromI9();
				this->m_knightCheckTable_[color][sq] |= this->GetControllBb(opponent, checkSq);
			}

			const Bitboard TRank789BB = (color == Black ? g_inFrontMaskBb.GetInFrontMask(Black, Rank6) :
				g_inFrontMaskBb.GetInFrontMask(White, Rank4));
			checkBB = g_goldAttackBb.GetControllBb(opponent, sq) & TRank789BB;
			while (checkBB.Exists1Bit()) {
				const Square checkSq = checkBB.PopFirstOneFromI9();
				this->m_knightCheckTable_[color][sq] |= this->GetControllBb(opponent, checkSq);
			}
		}
	}
}
