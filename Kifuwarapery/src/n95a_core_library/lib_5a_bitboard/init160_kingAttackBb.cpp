#include "n160_120_bishopAttackBb.hpp"
#include "n160_150_rookAttackBb.hpp"
#include "n160_160_kingAttackBb.hpp"


/// <summary>
/// 本当はconst にしたいが、やり方がわからない☆ C2373エラーになるんだぜ☆
/// </summary>
KingAttackBb g_kingAttackBb;


/// <summary>
/// 
/// </summary>
void KingAttackBb::initialize_10a130b_kingAttacks()
{
	for (Square sq = I9; sq < SquareNum; ++sq)
	{
		this->m_controllBb_[sq] =
			g_rookAttackBb.GetControllBb(Bitboard::CreateAllOneBB(), sq) |
			g_bishopAttackBb.BishopAttack(Bitboard::CreateAllOneBB(), sq);
	}
}
