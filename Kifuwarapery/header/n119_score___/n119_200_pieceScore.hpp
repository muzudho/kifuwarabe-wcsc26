#pragma once
#include "../n113_piece___/n113_150_piece.hpp"
#include "../n113_piece___/n113_205_convHandPiece.hpp"
#include "n119_090_ScoreValue.hpp"
#include "n119_100_utilScore.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 駒の価値
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 駒の価値
/// </summary>
class PieceScore {


public:

	static const ScoreValue m_pawn;
	static const ScoreValue m_lance;
	static const ScoreValue m_knight;
	static const ScoreValue m_silver;
	static const ScoreValue m_gold;
	static const ScoreValue m_bishop;
	static const ScoreValue m_rook;
	static const ScoreValue m_proPawn;
	static const ScoreValue m_proLance;
	static const ScoreValue m_proKnight;
	static const ScoreValue m_proSilver;
	static const ScoreValue m_horse;
	static const ScoreValue m_dragon;

	static const ScoreValue m_king;

	static const ScoreValue m_capturePawn;
	static const ScoreValue m_captureLance;
	static const ScoreValue m_captureKnight;
	static const ScoreValue m_captureSilver;
	static const ScoreValue m_captureGold;
	static const ScoreValue m_captureBishop;
	static const ScoreValue m_captureRook;
	static const ScoreValue m_captureProPawn;
	static const ScoreValue m_captureProLance;
	static const ScoreValue m_captureProKnight;
	static const ScoreValue m_CaptureProSilverScore;
	static const ScoreValue m_CaptureHorseScore;
	static const ScoreValue m_CaptureDragonScore;
	static const ScoreValue m_CaptureKingScore;

	static const ScoreValue m_PromotePawnScore;
	static const ScoreValue m_PromoteLanceScore;
	static const ScoreValue m_PromoteKnightScore;
	static const ScoreValue m_PromoteSilverScore;
	static const ScoreValue m_PromoteBishopScore;
	static const ScoreValue m_PromoteRookScore;

	static const ScoreValue m_ScoreKnownWin;

	static const ScoreValue m_PieceScore[Piece::N31_PieceNone];
	static const ScoreValue m_CapturePieceScore[Piece::N31_PieceNone];
	static const ScoreValue m_PromotePieceScore[7];


public:


	/// <summary>
	/// Piece を index としても、 PieceType を index としても、
	/// 同じ値が取得出来るようにしているので、PieceType => Piece への変換は必要ない。
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const ScoreValue GetPieceScore(const PieceType pt) {
		return PieceScore::m_PieceScore[pt];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	inline static const ScoreValue GetPieceScore(const Piece pc) {
		return PieceScore::m_PieceScore[pc];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	inline static const ScoreValue GetCapturePieceScore(const Piece pc) {
		return PieceScore::m_CapturePieceScore[pc];
	}


	/// <summary>
	/// Piece を index としても、 PieceType を index としても、
	/// 同じ値が取得出来るようにしているので、PieceType => Piece への変換は必要ない。
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const ScoreValue GetCapturePieceScore(const PieceType pt) {
		return PieceScore::m_CapturePieceScore[pt];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const ScoreValue GetPromotePieceScore(const PieceType pt) {
		assert(pt < PieceType::N07_Gold);
		return PieceScore::m_PromotePieceScore[pt];
	}
};
