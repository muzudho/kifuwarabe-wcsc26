#include "n160_108_slideBits.hpp"
#include "n160_102_FileMaskBb.hpp"
#include "n160_106_inFrontMaskBb.hpp"
#include "init130_lanceAttackBb.hpp"
#include "init140_goldAttackBb.hpp"
#include "init150_rookAttackBb.hpp"
#include "init190_pawnAttackBb.hpp"
#include "n160_230_setMaskBb.hpp"
#include "n160_400_printBb.hpp"


/// <summary>
///		<pre>
/// これらは一度値を設定したら二度と変更しない。
/// 本当はconst にしたいが、やり方がわからない☆ C2373エラーになるんだぜ☆
///		</pre>
/// </summary>
LanceAttackBb g_lanceAttackBb;


/// <summary>
/// 
/// </summary>
void LanceAttackBb::initialize_10a180b_lanceAttacks()
{
	// LanceBlockMask, g_lanceAttack の値を設定する。
	for (Color c = Black; c < g_COLOR_NUM; ++c) {
		for (Square sq = I9; sq < SquareNum; ++sq) {
			const Bitboard blockMask = this->LanceBlockMask(sq);
			//const int num1s = blockMask.popCount(); // 常に 7
			const int num1s = 7;
			assert(num1s == blockMask.PopCount());
			for (int i = 0; i < (1 << num1s); ++i) {
				Bitboard occupied = g_setMaskBb.IndexToOccupied(i, num1s, blockMask);
				this->m_controllBb[c][sq][i] = this->LanceAttackCalc(c, sq, occupied);
			}
		}
	}
}


/// <summary>
/// 
/// </summary>
void LanceAttackBb::initialize_10a270b_checkTableLance() {
	for (Color c = Black; c < g_COLOR_NUM; ++c) {
		const Color opp = ConvColor::OPPOSITE_COLOR10b(c);//色はループで交互になるぜ☆（＾ｑ＾）
		for (Square sq = I9; sq < SquareNum; ++sq) {
			this->m_lanceCheckTable_[c][sq] = this->GetControllBbToEdge(opp, sq);

			const Bitboard TRank789BB = (c == Black ? g_inFrontMaskBb.GetInFrontMask(Black, Rank6) :
				g_inFrontMaskBb.GetInFrontMask(White, Rank4));
			Bitboard checkBB = g_goldAttackBb.GetControllBb(opp, sq) & TRank789BB;
			while (checkBB.Exists1Bit()) {
				const Square checkSq = checkBB.PopFirstOneFromI9();
				this->m_lanceCheckTable_[c][sq] |= this->GetControllBbToEdge(opp, checkSq);
			}
			this->m_lanceCheckTable_[c][sq].AndEqualNot(g_setMaskBb.GetSetMaskBb(sq) | g_pawnAttackBb.GetControllBb(opp, sq));
		}
	}
}


/// <summary>
/// 
/// </summary>
void LanceAttackBb::initialize_10a220b_lanceToEdge()
{
	for (Square sq = I9; sq < SquareNum; ++sq) {
		this->m_controllBbToEdge_[Black][sq] = this->GetControllBb(Bitboard::CreateAllZeroBB(), Black, sq);
		this->m_controllBbToEdge_[White][sq] = this->GetControllBb(Bitboard::CreateAllZeroBB(), White, sq);
	}
}


/// <summary>
///		<pre>
/// square のマスにおける、障害物を調べる必要がある場所を Bitboard で返す。
/// lance の前方だけを調べれば良さそうだけど、Rank8 ~ Rank2 の状態をそのまま index に使いたいので、
/// 縦方向全て(端を除く)の occupied を全て調べる。
///		</pre>
/// </summary>
/// <param name="square"></param>
/// <returns></returns>
Bitboard LanceAttackBb::LanceBlockMask(const Square square) {
	return g_fileMaskBb.GetSquareFileMask(square) & ~(g_rankMaskBb.GetRankMask<Rank1>() | g_rankMaskBb.GetRankMask<Rank9>());
}


/// <summary>
/// 	<pre>
/// lance の利きを返す。
/// 香車の利きは常にこれを使っても良いけど、もう少し速くする為に、テーブル化する為だけに使う。
/// occupied  障害物があるマスが 1 の bitboard
/// 	</pre>
/// </summary>
/// <param name="c"></param>
/// <param name="square"></param>
/// <param name="occupied"></param>
/// <returns></returns>
Bitboard LanceAttackBb::LanceAttackCalc(const Color c, const Square square, const Bitboard& occupied) {
	return g_rookAttackBb.GetControllBb(occupied, square) & g_inFrontMaskBb.GetInFrontMask(c, ConvSquare::TO_RANK10(square));
}
