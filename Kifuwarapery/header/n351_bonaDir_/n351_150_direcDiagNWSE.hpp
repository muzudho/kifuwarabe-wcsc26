#pragma once

#include <cstdlib>	// abs()
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_250_squareDelta.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n340_bonaDir_/n162_070_bonaDirAbstract.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n250_pieceTyp/n350_040_ptEvent.hpp"
#include "../n250_pieceTyp/n350_500_ptPrograms.hpp"


/// <summary>
/// 
/// </summary>
class DirecDiagNWSE : public BonaDirAbstract {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const {
		squareDistance.SetValue( sq0, sq1,
			abs(static_cast<int>(sq0 - sq1) / static_cast<int>(SquareDelta::DeltaNW))
		);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="position"></param>
	/// <param name="from"></param>
	/// <param name="ksq"></param>
	/// <param name="us"></param>
	void Do2Move(Position& position, Square from, const Square ksq, const Color us) const {
		const PieceTypeEvent ptEvent1(position.GetOccupiedBB(), Color::Null, ksq);
		position.GetStateInfo()->m_checkersBB |=
			PiecetypePrograms::m_BISHOP.GetAttacks2From(ptEvent1) &
			(
				us==Color::Black
				?
				position.GetBbOf30<Color::Black>(PieceType::N05_Bishop, PieceType::N13_Horse)
				:
				position.GetBbOf30<Color::White>(PieceType::N05_Bishop, PieceType::N13_Horse)
				)
			;
	}

};


/// <summary>
/// 
/// </summary>
extern DirecDiagNWSE g_direcDiagNWSE;
