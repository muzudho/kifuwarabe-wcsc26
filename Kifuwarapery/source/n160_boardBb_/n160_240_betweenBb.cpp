#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../header/n160_boardBb_/n160_120_bishopAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_150_rookAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_230_setMaskBb.hpp"
#include "../../header/n160_boardBb_/n160_240_betweenBb.hpp"
#include "../../header/n160_boardBb_/n160_400_printBb.hpp"


BetweenBb g_betweenBb;


/// <summary>
/// 最初の設定（初期化）を行うぜ☆（＾▽＾）
/// </summary>
void BetweenBb::Initialize() {
	for (Square sq1 = I9; sq1 < SquareNum; ++sq1) {
		for (Square sq2 = I9; sq2 < SquareNum; ++sq2) {
			// 既定値、空ビットボード。
			g_betweenBb.m_betweenBB_[sq1][sq2] = Bitboard::CreateAllZeroBB();

			// ［同マス］
			if (sq1 == sq2) { continue; }

			// ２つの位置の差の区分。
			const Direction direc = g_squareRelation.GetSquareRelation(sq1, sq2);

			// 縦横
			if (direc & N02_DirecCross)
			{
				// 飛車の利きのブロック駒を考慮？
				g_betweenBb.m_betweenBB_[sq1][sq2] =
					  g_rookAttackBb.GetControllBb(g_setMaskBb.GetSetMaskBb(sq2), sq1)
					& g_rookAttackBb.GetControllBb(g_setMaskBb.GetSetMaskBb(sq1), sq2);
			}
			// 斜め
			else if (direc & N04_DirecDiag)
			{
				// 角の利きのブロック駒を考慮？
				g_betweenBb.m_betweenBB_[sq1][sq2] =
					  g_bishopAttackBb.BishopAttack(g_setMaskBb.GetSetMaskBb(sq2), sq1)
					& g_bishopAttackBb.BishopAttack(g_setMaskBb.GetSetMaskBb(sq1), sq2);
			}
		}
	}
}
