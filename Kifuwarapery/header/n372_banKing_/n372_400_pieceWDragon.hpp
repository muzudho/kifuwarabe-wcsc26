#pragma once

#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../n130_100_boardBb_/n160_210_dragonAttackBb.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n250_pieceTyp/n350_040_ptEvent.hpp"
#include "../n250_pieceTyp/n350_500_ptPrograms.hpp"
#include "../n372_banKing_/n372_070_PieceAbstract.hpp"


/// <summary>
/// 後手竜。
/// </summary>
class PieceWDragon : public IKingBannable {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="bannedKingToBB"></param>
	/// <param name="pos"></param>
	/// <param name="checkSq"></param>
	/// <param name="ksq"></param>
	void MakeBanned2KingTo(
		Bitboard& bannedKingToBB, const Position& pos, const Square checkSq, const Square ksq) const override
	{
		// 斜めから王手したとき
		if (g_squareRelation.GetSquareRelation(checkSq, ksq) & N04_DirecDiag)
		{
			// 玉の移動先と王手した駒の間に駒があることがあるので、
			// dragonAttackToEdge(checkSq) は使えない。
			const PieceTypeEvent ptEvent1(pos.GetOccupiedBB(), Color::Null, checkSq);
			bannedKingToBB |= PiecetypePrograms::m_DRAGON.GetAttacks2From(ptEvent1);
		}
		else
		{
			bannedKingToBB |= g_dragonAttackBb.GetControllBbToEdge(checkSq);
		}
	}
};
