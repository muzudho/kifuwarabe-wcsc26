#pragma once

#include <cstdlib>	// abs()
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../src/lib_toybox_base/color.hpp"
#include "../../src/lib_toybox_base/square.hpp"
#include "../../src/lib_toybox_base/square_delta.hpp"
#include "../n161_sqDistan/n161_500_squareDistance.hpp"
#include "../n162_bonaDir_/n162_070_bonaDirAbstract.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n350_pieceTyp/n350_040_ptEvent.hpp"
#include "../n350_pieceTyp/n350_500_ptPrograms.hpp"


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
