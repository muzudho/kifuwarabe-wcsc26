#pragma once
#include <cstdlib>	// abs()
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_250_squareDelta.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n105_220_bonaDir_/n105_220_500_IBonaDirectional.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n250_pieceTyp/n350_040_ptEvent.hpp"
#include "../n250_pieceTyp/n350_500_ptPrograms.hpp"
#include "../n340_bonaMove/n340_500_IBonaMovable.hpp"


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class DiagonalNESWBonaDirection : public IBonaDirectionable
{


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const
	{
		squareDistance.SetValue( sq0, sq1,
			abs(static_cast<int>(sq0 - sq1) / static_cast<int>(SquareDelta::DeltaNE))
		);
	}
};


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern DiagonalNESWBonaDirection g_diagonalNESWBonaDirection;


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class DiagonalNESWBonaMove : public IBonaMovable
{


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="position"></param>
	/// <param name="from"></param>
	/// <param name="ksq"></param>
	/// <param name="us"></param>
	/// <returns>checkerBB</returns>
	void Do2Move(Position& position, Square from, const Square ksq, const Color us) const
	{
		const PieceTypeEvent ptEvent1(position.GetOccupiedBB(), Color::Null, ksq);
		Bitboard checkerBB = PiecetypePrograms::m_BISHOP.GetAttacks2From(ptEvent1) &
			(
				us == Color::Black
				?
				position.GetBbOf30<Color::Black>(PieceType::N05_Bishop, PieceType::N13_Horse)
				:
				position.GetBbOf30<Color::White>(PieceType::N05_Bishop, PieceType::N13_Horse)
				);

		position.GetStateInfo()->m_checkersBB |= checkerBB;
	}
};


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
extern DiagonalNESWBonaMove g_diagonalNESWBonaMove;
