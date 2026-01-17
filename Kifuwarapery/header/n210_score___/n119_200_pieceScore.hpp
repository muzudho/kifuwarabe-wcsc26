#pragma once
#include "../n105_180_piece___/n105_180_150_Piece.hpp"
#include "../n105_180_piece___/n105_180_205_HandPieceExtensions.hpp"
#include "n119_090_scoreIndex.hpp"
#include "n119_100_utilScore.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 駒の価値
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 駒の価値
/// </summary>
class PieceScore {


public:

	static const ScoreNumber m_pawn;
	static const ScoreNumber m_lance;
	static const ScoreNumber m_knight;
	static const ScoreNumber m_silver;
	static const ScoreNumber m_gold;
	static const ScoreNumber m_bishop;
	static const ScoreNumber m_rook;
	static const ScoreNumber m_proPawn;
	static const ScoreNumber m_proLance;
	static const ScoreNumber m_proKnight;
	static const ScoreNumber m_proSilver;
	static const ScoreNumber m_horse;
	static const ScoreNumber m_dragon;

	static const ScoreNumber m_king;

	static const ScoreNumber m_capturePawn;
	static const ScoreNumber m_captureLance;
	static const ScoreNumber m_captureKnight;
	static const ScoreNumber m_captureSilver;
	static const ScoreNumber m_captureGold;
	static const ScoreNumber m_captureBishop;
	static const ScoreNumber m_captureRook;
	static const ScoreNumber m_captureProPawn;
	static const ScoreNumber m_captureProLance;
	static const ScoreNumber m_captureProKnight;
	static const ScoreNumber m_CaptureProSilverScore;
	static const ScoreNumber m_CaptureHorseScore;
	static const ScoreNumber m_CaptureDragonScore;
	static const ScoreNumber m_CaptureKingScore;

	static const ScoreNumber m_PromotePawnScore;
	static const ScoreNumber m_PromoteLanceScore;
	static const ScoreNumber m_PromoteKnightScore;
	static const ScoreNumber m_PromoteSilverScore;
	static const ScoreNumber m_PromoteBishopScore;
	static const ScoreNumber m_PromoteRookScore;

	static const ScoreNumber m_ScoreKnownWin;

	static const ScoreNumber m_PieceScore[Piece::N31_PieceNone];
	static const ScoreNumber m_CapturePieceScore[Piece::N31_PieceNone];
	static const ScoreNumber m_PromotePieceScore[7];


public:


	/// <summary>
	/// Piece を index としても、 PieceType を index としても、
	/// 同じ値が取得出来るようにしているので、PieceType => Piece への変換は必要ない。
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const ScoreNumber GetPieceScore(const PieceType pt) {
		return PieceScore::m_PieceScore[pt];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	inline static const ScoreNumber GetPieceScore(const Piece pc) {
		return PieceScore::m_PieceScore[pc];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	inline static const ScoreNumber GetCapturePieceScore(const Piece pc) {
		return PieceScore::m_CapturePieceScore[pc];
	}


	/// <summary>
	/// Piece を index としても、 PieceType を index としても、
	/// 同じ値が取得出来るようにしているので、PieceType => Piece への変換は必要ない。
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const ScoreNumber GetCapturePieceScore(const PieceType pt) {
		return PieceScore::m_CapturePieceScore[pt];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const ScoreNumber GetPromotePieceScore(const PieceType pt) {
		assert(pt < PieceType::N07_Gold);
		return PieceScore::m_PromotePieceScore[pt];
	}
};
