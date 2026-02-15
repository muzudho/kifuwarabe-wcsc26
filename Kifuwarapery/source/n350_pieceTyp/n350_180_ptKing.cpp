#include "../../src/lib_toybox_base/color.hpp"
#include "../../src/lib_toybox_base/square.hpp"
#include "../../header/n105_120_square__/n105_120_500_convSquare.hpp"
#include "../../src/lib_toybox_base/piece_type.hpp"
#include "../../header/n160_board___/n160_100_bitboard.hpp"
#include "../../header/n160_board___/n160_130_lanceAttackBb.hpp"
#include "../../header/n160_board___/n160_190_pawnAttackBb.hpp"
#include "../../header/n160_board___/n160_230_setMaskBb.hpp"
#include "../../header/n165_movStack/n165_300_moveType.hpp"
#include "../../header/n165_movStack/n165_500_moveStack.hpp"
#include "../../header/n165_movStack/n165_600_convMove.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"

#include "../../header/n350_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n350_pieceTyp/n350_040_ptEvent.hpp"
#include "../../header/n350_pieceTyp/n350_045_pieceTypeSeeEvent.hpp"
#include "../../header/n350_pieceTyp/n350_070_ptAbstract.hpp"
#include "../../header/n350_pieceTyp/n350_180_ptKing.hpp"
#include "../../header/n350_pieceTyp/n350_500_ptPrograms.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="occupied"></param>
/// <param name="attackers"></param>
/// <param name="nextPT"></param>
/// <param name="ptsEvent"></param>
/// <returns></returns>
PieceType PtKing::AppendToNextAttackerAndTryPromote(
	Bitboard& occupied,
	Bitboard& attackers,
	PieceType nextPT,
	const PieceTypeSeeEvent ptsEvent
	) const {
	PieceType PT = PieceType::N08_King;


	if (ptsEvent.m_opponentAttackers.AndIsNot0(ptsEvent.m_pos.GetBbOf10(PT))) {
		// todo: 実際に移動した方向を基にattackersを更新すれば、template, inline を使用しなくても良さそう。
		//       その場合、キャッシュに乗りやすくなるので逆に速くなるかも。
		// それ以外の駒種類は、そのまま返す☆
		return PT;
	}

	// 王は、これだけ☆
	return N08_King;
}
