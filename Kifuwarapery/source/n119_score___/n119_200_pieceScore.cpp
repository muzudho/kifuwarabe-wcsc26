#include "../../header/n105_100_color___/n105_100_500_convColor.hpp"
#include "../../header/n119_score___/n119_200_pieceScore.hpp"


const Sweetness PieceScore::m_pawn = static_cast<Sweetness>(100 * 9 / 10);
const Sweetness PieceScore::m_lance = static_cast<Sweetness>(350 * 9 / 10);
const Sweetness PieceScore::m_knight = static_cast<Sweetness>(450 * 9 / 10);
const Sweetness PieceScore::m_silver = static_cast<Sweetness>(550 * 9 / 10);
const Sweetness PieceScore::m_gold = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceScore::m_bishop = static_cast<Sweetness>(950 * 9 / 10);
const Sweetness PieceScore::m_rook = static_cast<Sweetness>(1100 * 9 / 10);
const Sweetness PieceScore::m_proPawn = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceScore::m_proLance = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceScore::m_proKnight = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceScore::m_proSilver = static_cast<Sweetness>(600 * 9 / 10);
const Sweetness PieceScore::m_horse = static_cast<Sweetness>(1050 * 9 / 10);
const Sweetness PieceScore::m_dragon = static_cast<Sweetness>(1550 * 9 / 10);

const Sweetness PieceScore::m_king = static_cast<Sweetness>(15000);

const Sweetness PieceScore::m_capturePawn = PieceScore::m_pawn * 2;
const Sweetness PieceScore::m_captureLance = PieceScore::m_lance * 2;
const Sweetness PieceScore::m_captureKnight = PieceScore::m_knight * 2;
const Sweetness PieceScore::m_captureSilver = PieceScore::m_silver * 2;
const Sweetness PieceScore::m_captureGold = PieceScore::m_gold * 2;
const Sweetness PieceScore::m_captureBishop = PieceScore::m_bishop * 2;
const Sweetness PieceScore::m_captureRook = PieceScore::m_rook * 2;
const Sweetness PieceScore::m_captureProPawn = PieceScore::m_proPawn + PieceScore::m_pawn;
const Sweetness PieceScore::m_captureProLance = PieceScore::m_proLance + PieceScore::m_lance;
const Sweetness PieceScore::m_captureProKnight = PieceScore::m_proKnight + PieceScore::m_knight;
const Sweetness PieceScore::m_CaptureProSilverScore = PieceScore::m_proSilver + PieceScore::m_silver;
const Sweetness PieceScore::m_CaptureHorseScore = PieceScore::m_horse + PieceScore::m_bishop;
const Sweetness PieceScore::m_CaptureDragonScore = PieceScore::m_dragon + PieceScore::m_rook;
const Sweetness PieceScore::m_CaptureKingScore = PieceScore::m_king * 2;

const Sweetness PieceScore::m_PromotePawnScore = PieceScore::m_proPawn - PieceScore::m_pawn;
const Sweetness PieceScore::m_PromoteLanceScore = PieceScore::m_proLance - PieceScore::m_lance;
const Sweetness PieceScore::m_PromoteKnightScore = PieceScore::m_proKnight - PieceScore::m_knight;
const Sweetness PieceScore::m_PromoteSilverScore = PieceScore::m_proSilver - PieceScore::m_silver;
const Sweetness PieceScore::m_PromoteBishopScore = PieceScore::m_horse - PieceScore::m_bishop;
const Sweetness PieceScore::m_PromoteRookScore = PieceScore::m_dragon - PieceScore::m_rook;

const Sweetness PieceScore::m_ScoreKnownWin = PieceScore::m_king;


/// <summary>
/// 
/// </summary>
const Sweetness PieceScore::m_PieceScore[Piece::N31_PieceNone] = {
	SweetnessZero,
	PieceScore::m_pawn,
	PieceScore::m_lance,
	PieceScore::m_knight,
	PieceScore::m_silver,
	PieceScore::m_bishop,
	PieceScore::m_rook,
	PieceScore::m_gold,
	SweetnessZero, // King
	PieceScore::m_proPawn,
	PieceScore::m_proLance,
	PieceScore::m_proKnight,
	PieceScore::m_proSilver,
	PieceScore::m_horse,
	PieceScore::m_dragon,
	SweetnessZero,
	SweetnessZero,
	PieceScore::m_pawn,
	PieceScore::m_lance,
	PieceScore::m_knight,
	PieceScore::m_silver,
	PieceScore::m_bishop,
	PieceScore::m_rook,
	PieceScore::m_gold,
	SweetnessZero, // King
	PieceScore::m_proPawn,
	PieceScore::m_proLance,
	PieceScore::m_proKnight,
	PieceScore::m_proSilver,
	PieceScore::m_horse,
	PieceScore::m_dragon,
};

/// <summary>
/// 
/// </summary>
const Sweetness PieceScore::m_CapturePieceScore[Piece::N31_PieceNone] = {
	SweetnessZero,
	PieceScore::m_capturePawn,
	PieceScore::m_captureLance,
	PieceScore::m_captureKnight,
	PieceScore::m_captureSilver,
	PieceScore::m_captureBishop,
	PieceScore::m_captureRook,
	PieceScore::m_captureGold,
	SweetnessZero, // King
	PieceScore::m_captureProPawn,
	PieceScore::m_captureProLance,
	PieceScore::m_captureProKnight,
	PieceScore::m_CaptureProSilverScore,
	PieceScore::m_CaptureHorseScore,
	PieceScore::m_CaptureDragonScore,
	SweetnessZero,
	SweetnessZero,
	PieceScore::m_capturePawn,
	PieceScore::m_captureLance,
	PieceScore::m_captureKnight,
	PieceScore::m_captureSilver,
	PieceScore::m_captureBishop,
	PieceScore::m_captureRook,
	PieceScore::m_captureGold,
	SweetnessZero, // King
	PieceScore::m_captureProPawn,
	PieceScore::m_captureProLance,
	PieceScore::m_captureProKnight,
	PieceScore::m_CaptureProSilverScore,
	PieceScore::m_CaptureHorseScore,
	PieceScore::m_CaptureDragonScore,
};

/// <summary>
/// 
/// </summary>
const Sweetness PieceScore::m_PromotePieceScore[7] = {
	SweetnessZero,
	PieceScore::m_PromotePawnScore,
	PieceScore::m_PromoteLanceScore,
	PieceScore::m_PromoteKnightScore,
	PieceScore::m_PromoteSilverScore,
	PieceScore::m_PromoteBishopScore,
	PieceScore::m_PromoteRookScore
};
