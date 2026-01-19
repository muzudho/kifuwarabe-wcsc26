#include "../../header/n105_100_color___/n105_100_500_convColor.hpp"
#include "../../header/n119_500_sweetnes/n119_200_PieceSweetness.hpp"


const Sweetness PieceSweetness::m_pawn = static_cast<Sweetness>(100 * 9 / 10);
const Sweetness PieceSweetness::m_lance = static_cast<Sweetness>(350 * 9 / 10);
const Sweetness PieceSweetness::m_knight = static_cast<Sweetness>(450 * 9 / 10);
const Sweetness PieceSweetness::m_silver = static_cast<Sweetness>(550 * 9 / 10);
const Sweetness PieceSweetness::m_gold = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceSweetness::m_bishop = static_cast<Sweetness>(950 * 9 / 10);
const Sweetness PieceSweetness::m_rook = static_cast<Sweetness>(1100 * 9 / 10);
const Sweetness PieceSweetness::m_proPawn = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceSweetness::m_proLance = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceSweetness::m_proKnight = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceSweetness::m_proSilver = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceSweetness::m_horse = static_cast<Sweetness>(1050 * 9 / 10);
const Sweetness PieceSweetness::m_dragon = static_cast<Sweetness>(1550 * 9 / 10);

const Sweetness PieceSweetness::m_king = static_cast<Sweetness>(15000);

const Sweetness PieceSweetness::m_capturePawn = PieceSweetness::m_pawn * 2;
const Sweetness PieceSweetness::m_captureLance = PieceSweetness::m_lance * 2;
const Sweetness PieceSweetness::m_captureKnight = PieceSweetness::m_knight * 2;
const Sweetness PieceSweetness::m_captureSilver = PieceSweetness::m_silver * 2;
const Sweetness PieceSweetness::m_captureGold = PieceSweetness::m_gold * 2;
const Sweetness PieceSweetness::m_captureBishop = PieceSweetness::m_bishop * 2;
const Sweetness PieceSweetness::m_captureRook = PieceSweetness::m_rook * 2;
const Sweetness PieceSweetness::m_captureProPawn = PieceSweetness::m_proPawn + PieceSweetness::m_pawn;
const Sweetness PieceSweetness::m_captureProLance = PieceSweetness::m_proLance + PieceSweetness::m_lance;
const Sweetness PieceSweetness::m_captureProKnight = PieceSweetness::m_proKnight + PieceSweetness::m_knight;
const Sweetness PieceSweetness::m_captureProSilver = PieceSweetness::m_proSilver + PieceSweetness::m_silver;
const Sweetness PieceSweetness::m_captureHorse = PieceSweetness::m_horse + PieceSweetness::m_bishop;
const Sweetness PieceSweetness::m_captureDragon = PieceSweetness::m_dragon + PieceSweetness::m_rook;
const Sweetness PieceSweetness::m_captureKing = PieceSweetness::m_king * 2;

const Sweetness PieceSweetness::m_PromotePawn = PieceSweetness::m_proPawn - PieceSweetness::m_pawn;
const Sweetness PieceSweetness::m_PromoteLance = PieceSweetness::m_proLance - PieceSweetness::m_lance;
const Sweetness PieceSweetness::m_PromoteKnight = PieceSweetness::m_proKnight - PieceSweetness::m_knight;
const Sweetness PieceSweetness::m_PromoteSilver = PieceSweetness::m_proSilver - PieceSweetness::m_silver;
const Sweetness PieceSweetness::m_PromoteBishop = PieceSweetness::m_horse - PieceSweetness::m_bishop;
const Sweetness PieceSweetness::m_PromoteRook = PieceSweetness::m_dragon - PieceSweetness::m_rook;

const Sweetness PieceSweetness::m_sweetnessKnownWin = PieceSweetness::m_king;


/// <summary>
/// 
/// </summary>
const Sweetness PieceSweetness::m_pieceArray[Piece::N31_PieceNone] = {
	SweetnessZero,
	PieceSweetness::m_pawn,
	PieceSweetness::m_lance,
	PieceSweetness::m_knight,
	PieceSweetness::m_silver,
	PieceSweetness::m_bishop,
	PieceSweetness::m_rook,
	PieceSweetness::m_gold,
	SweetnessZero, // King
	PieceSweetness::m_proPawn,
	PieceSweetness::m_proLance,
	PieceSweetness::m_proKnight,
	PieceSweetness::m_proSilver,
	PieceSweetness::m_horse,
	PieceSweetness::m_dragon,
	SweetnessZero,
	SweetnessZero,
	PieceSweetness::m_pawn,
	PieceSweetness::m_lance,
	PieceSweetness::m_knight,
	PieceSweetness::m_silver,
	PieceSweetness::m_bishop,
	PieceSweetness::m_rook,
	PieceSweetness::m_gold,
	SweetnessZero, // King
	PieceSweetness::m_proPawn,
	PieceSweetness::m_proLance,
	PieceSweetness::m_proKnight,
	PieceSweetness::m_proSilver,
	PieceSweetness::m_horse,
	PieceSweetness::m_dragon,
};

/// <summary>
/// 
/// </summary>
const Sweetness PieceSweetness::m_capturePieceArray[Piece::N31_PieceNone] = {
	SweetnessZero,
	PieceSweetness::m_capturePawn,
	PieceSweetness::m_captureLance,
	PieceSweetness::m_captureKnight,
	PieceSweetness::m_captureSilver,
	PieceSweetness::m_captureBishop,
	PieceSweetness::m_captureRook,
	PieceSweetness::m_captureGold,
	SweetnessZero, // King
	PieceSweetness::m_captureProPawn,
	PieceSweetness::m_captureProLance,
	PieceSweetness::m_captureProKnight,
	PieceSweetness::m_captureProSilver,
	PieceSweetness::m_captureHorse,
	PieceSweetness::m_captureDragon,
	SweetnessZero,
	SweetnessZero,
	PieceSweetness::m_capturePawn,
	PieceSweetness::m_captureLance,
	PieceSweetness::m_captureKnight,
	PieceSweetness::m_captureSilver,
	PieceSweetness::m_captureBishop,
	PieceSweetness::m_captureRook,
	PieceSweetness::m_captureGold,
	SweetnessZero, // King
	PieceSweetness::m_captureProPawn,
	PieceSweetness::m_captureProLance,
	PieceSweetness::m_captureProKnight,
	PieceSweetness::m_captureProSilver,
	PieceSweetness::m_captureHorse,
	PieceSweetness::m_captureDragon,
};

/// <summary>
/// 
/// </summary>
const Sweetness PieceSweetness::m_promotePieceArray[7] = {
	SweetnessZero,
	PieceSweetness::m_PromotePawn,
	PieceSweetness::m_PromoteLance,
	PieceSweetness::m_PromoteKnight,
	PieceSweetness::m_PromoteSilver,
	PieceSweetness::m_PromoteBishop,
	PieceSweetness::m_PromoteRook
};
