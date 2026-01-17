#include "../../header/n105_100_color___/n105_100_500_convColor.hpp"
#include "../../header/n210_score___/n119_200_pieceScore.hpp"


const ScoreNumber PieceScore::m_pawn = static_cast<ScoreNumber>(100 * 9 / 10);
const ScoreNumber PieceScore::m_lance = static_cast<ScoreNumber>(350 * 9 / 10);
const ScoreNumber PieceScore::m_knight = static_cast<ScoreNumber>(450 * 9 / 10);
const ScoreNumber PieceScore::m_silver = static_cast<ScoreNumber>(550 * 9 / 10);
const ScoreNumber PieceScore::m_gold = static_cast<ScoreNumber>(600 * 9 / 10);
const ScoreNumber PieceScore::m_bishop = static_cast<ScoreNumber>(950 * 9 / 10);
const ScoreNumber PieceScore::m_rook = static_cast<ScoreNumber>(1100 * 9 / 10);
const ScoreNumber PieceScore::m_proPawn = static_cast<ScoreNumber>(600 * 9 / 10);
const ScoreNumber PieceScore::m_proLance = static_cast<ScoreNumber>(600 * 9 / 10);
const ScoreNumber PieceScore::m_proKnight = static_cast<ScoreNumber>(600 * 9 / 10);
const ScoreNumber PieceScore::m_proSilver = static_cast<ScoreNumber>(600 * 9 / 10);
const ScoreNumber PieceScore::m_horse = static_cast<ScoreNumber>(1050 * 9 / 10);
const ScoreNumber PieceScore::m_dragon = static_cast<ScoreNumber>(1550 * 9 / 10);

const ScoreNumber PieceScore::m_king = static_cast<ScoreNumber>(15000);

const ScoreNumber PieceScore::m_capturePawn = PieceScore::m_pawn * 2;
const ScoreNumber PieceScore::m_captureLance = PieceScore::m_lance * 2;
const ScoreNumber PieceScore::m_captureKnight = PieceScore::m_knight * 2;
const ScoreNumber PieceScore::m_captureSilver = PieceScore::m_silver * 2;
const ScoreNumber PieceScore::m_captureGold = PieceScore::m_gold * 2;
const ScoreNumber PieceScore::m_captureBishop = PieceScore::m_bishop * 2;
const ScoreNumber PieceScore::m_captureRook = PieceScore::m_rook * 2;
const ScoreNumber PieceScore::m_captureProPawn = PieceScore::m_proPawn + PieceScore::m_pawn;
const ScoreNumber PieceScore::m_captureProLance = PieceScore::m_proLance + PieceScore::m_lance;
const ScoreNumber PieceScore::m_captureProKnight = PieceScore::m_proKnight + PieceScore::m_knight;
const ScoreNumber PieceScore::m_CaptureProSilverScore = PieceScore::m_proSilver + PieceScore::m_silver;
const ScoreNumber PieceScore::m_CaptureHorseScore = PieceScore::m_horse + PieceScore::m_bishop;
const ScoreNumber PieceScore::m_CaptureDragonScore = PieceScore::m_dragon + PieceScore::m_rook;
const ScoreNumber PieceScore::m_CaptureKingScore = PieceScore::m_king * 2;

const ScoreNumber PieceScore::m_PromotePawnScore = PieceScore::m_proPawn - PieceScore::m_pawn;
const ScoreNumber PieceScore::m_PromoteLanceScore = PieceScore::m_proLance - PieceScore::m_lance;
const ScoreNumber PieceScore::m_PromoteKnightScore = PieceScore::m_proKnight - PieceScore::m_knight;
const ScoreNumber PieceScore::m_PromoteSilverScore = PieceScore::m_proSilver - PieceScore::m_silver;
const ScoreNumber PieceScore::m_PromoteBishopScore = PieceScore::m_horse - PieceScore::m_bishop;
const ScoreNumber PieceScore::m_PromoteRookScore = PieceScore::m_dragon - PieceScore::m_rook;

const ScoreNumber PieceScore::m_ScoreKnownWin = PieceScore::m_king;


/// <summary>
/// 
/// </summary>
const ScoreNumber PieceScore::m_PieceScore[Piece::N31_PieceNone] = {
	ScoreZero,
	PieceScore::m_pawn,
	PieceScore::m_lance,
	PieceScore::m_knight,
	PieceScore::m_silver,
	PieceScore::m_bishop,
	PieceScore::m_rook,
	PieceScore::m_gold,
	ScoreZero, // King
	PieceScore::m_proPawn,
	PieceScore::m_proLance,
	PieceScore::m_proKnight,
	PieceScore::m_proSilver,
	PieceScore::m_horse,
	PieceScore::m_dragon,
	ScoreZero,
	ScoreZero,
	PieceScore::m_pawn,
	PieceScore::m_lance,
	PieceScore::m_knight,
	PieceScore::m_silver,
	PieceScore::m_bishop,
	PieceScore::m_rook,
	PieceScore::m_gold,
	ScoreZero, // King
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
const ScoreNumber PieceScore::m_CapturePieceScore[Piece::N31_PieceNone] = {
	ScoreZero,
	PieceScore::m_capturePawn,
	PieceScore::m_captureLance,
	PieceScore::m_captureKnight,
	PieceScore::m_captureSilver,
	PieceScore::m_captureBishop,
	PieceScore::m_captureRook,
	PieceScore::m_captureGold,
	ScoreZero, // King
	PieceScore::m_captureProPawn,
	PieceScore::m_captureProLance,
	PieceScore::m_captureProKnight,
	PieceScore::m_CaptureProSilverScore,
	PieceScore::m_CaptureHorseScore,
	PieceScore::m_CaptureDragonScore,
	ScoreZero,
	ScoreZero,
	PieceScore::m_capturePawn,
	PieceScore::m_captureLance,
	PieceScore::m_captureKnight,
	PieceScore::m_captureSilver,
	PieceScore::m_captureBishop,
	PieceScore::m_captureRook,
	PieceScore::m_captureGold,
	ScoreZero, // King
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
const ScoreNumber PieceScore::m_PromotePieceScore[7] = {
	ScoreZero,
	PieceScore::m_PromotePawnScore,
	PieceScore::m_PromoteLanceScore,
	PieceScore::m_PromoteKnightScore,
	PieceScore::m_PromoteSilverScore,
	PieceScore::m_PromoteBishopScore,
	PieceScore::m_PromoteRookScore
};
