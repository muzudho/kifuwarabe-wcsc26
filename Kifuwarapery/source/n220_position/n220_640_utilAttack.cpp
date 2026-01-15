#include "../../header/n105_100_color___/n105_100_100_color.hpp"
#include "../../header/n105_120_square__/n105_120_100_square.hpp"
#include "../../header/n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../../header/n160_board___/n160_100_bitboard.hpp"
#include "../../header/n220_position/n220_640_utilAttack.hpp"
#include "../../header/n250_pieceTyp/n350_040_ptEvent.hpp"
#include "../../header/n250_pieceTyp/n350_070_ptAbstract.hpp"
#include "../../header/n250_pieceTyp/n350_500_ptPrograms.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="pType"></param>
/// <param name="c"></param>
/// <param name="sq"></param>
/// <param name="occupied"></param>
/// <returns></returns>
Bitboard UtilAttack::GetAttacksFrom(const PieceType pType, const Color c, const Square sq, const Bitboard& occupied) {//const
	// FIXME: 配列の範囲チェックをしてないぜ☆（＾ｑ＾）
	const PieceTypeEvent ptEvent1(occupied, c, sq);
	return PiecetypePrograms::m_PIECETYPE_PROGRAMS[pType]->GetAttacks2From(ptEvent1);
}
