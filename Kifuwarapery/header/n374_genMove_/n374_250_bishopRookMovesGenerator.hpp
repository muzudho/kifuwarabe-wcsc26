#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_500_convSquare.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n165_movStack/n165_300_movegenType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n250_pieceTyp/n350_040_ptEvent.hpp"
#include "../n250_pieceTyp/n350_500_ptPrograms.hpp"
#include "n374_040_pieceMoveEvent.hpp"


/// <summary>
/// 角と飛車の指し手生成を行う。
/// </summary>
class BishopRookMovesGenerator {


public:


	/// <summary>
	/// 角, 飛車の共通処理☆
	/// </summary>
	/// <typeparam name="isBishop"></typeparam>
	/// <typeparam name="US"></typeparam>
	/// <param name="moveStackList"></param>
	/// <param name="pieceTypeAsMove"></param>
	/// <param name="ptEvent"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	template<const bool isBishop,const Color US>
	static FORCE_INLINE DeliciousBanana* GenerateBishopOrRookMoves(
		DeliciousBanana* moveStackList,
		//const PieceType pt,
		Move pieceTypeAsMove,
		const PieceMoveEvent ptEvent,
		const Bitboard& target
		)
	{
		Bitboard fromBB = ptEvent.m_pos.GetBbOf20<US>(isBishop ? PieceType::N05_Bishop : PieceType::N06_Rook);
		while (fromBB.Exists1Bit()) {
			const Square from = fromBB.PopFirstOneFromI9();
			const bool fromCanPromote = ConvSquare::canPromote_n10<US>(ConvSquare::toRank_n10(from));
			const PieceTypeEvent ptEvent1(ptEvent.m_pos.GetOccupiedBB(), US, from);
			Bitboard toBB = PiecetypePrograms::m_PIECETYPE_PROGRAMS[(isBishop?PieceType::N05_Bishop:PieceType::N06_Rook)]->GetAttacks2From(ptEvent1) & target;
			while (toBB.Exists1Bit()) {
				const Square to = toBB.PopFirstOneFromI9();
				const bool toCanPromote = ConvSquare::canPromote_n10<US>(ConvSquare::toRank_n10(to));
				if (fromCanPromote | toCanPromote) {

					// 成りVer☆
					moveStackList->m_move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_mt2(ptEvent.m_mt,pieceTypeAsMove,from, to, ptEvent.m_pos);
					MakePromoteMove::APPEND_PROMOTE_FLAG(moveStackList->m_move);
					moveStackList++;

					// 次の指し手は不成Ver☆
					if (ptEvent.m_mt == N07_NonEvasion || ptEvent.m_all)
					{
						moveStackList->m_move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_mt2(ptEvent.m_mt,pieceTypeAsMove,from, to, ptEvent.m_pos);
						moveStackList++;
					}
				}
				else // 角、飛車は成れるなら成り、不成は生成しない。
				{
					moveStackList->m_move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_mt2(ptEvent.m_mt,pieceTypeAsMove,from, to, ptEvent.m_pos);
					moveStackList++;
				}
			}
		}
		return moveStackList;
	}
};
