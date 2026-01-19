#pragma once
#include "../n113_piece___/n113_150_piece.hpp"
#include "../n113_piece___/n113_205_convHandPiece.hpp"
#include "n119_090_Sweetness.hpp"
#include "n119_100_utilScore.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 駒の価値
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 駒の価値
/// </summary>
class PieceScore {


public:

	static const Sweetness m_pawn;
	static const Sweetness m_lance;
	static const Sweetness m_knight;
	static const Sweetness m_silver;
	static const Sweetness m_gold;
	static const Sweetness m_bishop;
	static const Sweetness m_rook;
	static const Sweetness m_proPawn;
	static const Sweetness m_proLance;
	static const Sweetness m_proKnight;
	static const Sweetness m_proSilver;
	static const Sweetness m_horse;
	static const Sweetness m_dragon;

	static const Sweetness m_king;

	static const Sweetness m_capturePawn;
	static const Sweetness m_captureLance;
	static const Sweetness m_captureKnight;
	static const Sweetness m_captureSilver;
	static const Sweetness m_captureGold;
	static const Sweetness m_captureBishop;
	static const Sweetness m_captureRook;
	static const Sweetness m_captureProPawn;
	static const Sweetness m_captureProLance;
	static const Sweetness m_captureProKnight;
	static const Sweetness m_CaptureProSilverScore;
	static const Sweetness m_CaptureHorseScore;
	static const Sweetness m_CaptureDragonScore;
	static const Sweetness m_CaptureKingScore;

	static const Sweetness m_PromotePawnScore;
	static const Sweetness m_PromoteLanceScore;
	static const Sweetness m_PromoteKnightScore;
	static const Sweetness m_PromoteSilverScore;
	static const Sweetness m_PromoteBishopScore;
	static const Sweetness m_PromoteRookScore;

	static const Sweetness m_ScoreKnownWin;

	static const Sweetness m_PieceScore[Piece::N31_PieceNone];
	static const Sweetness m_CapturePieceScore[Piece::N31_PieceNone];
	static const Sweetness m_PromotePieceScore[7];


public:


	/// <summary>
	/// Piece を index としても、 PieceType を index としても、
	/// 同じ値が取得出来るようにしているので、PieceType => Piece への変換は必要ない。
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const Sweetness GetPieceScore(const PieceType pt) {
		return PieceScore::m_PieceScore[pt];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	inline static const Sweetness GetPieceScore(const Piece pc) {
		return PieceScore::m_PieceScore[pc];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	inline static const Sweetness GetCapturePieceScore(const Piece pc) {
		return PieceScore::m_CapturePieceScore[pc];
	}


	/// <summary>
	/// Piece を index としても、 PieceType を index としても、
	/// 同じ値が取得出来るようにしているので、PieceType => Piece への変換は必要ない。
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const Sweetness GetCapturePieceScore(const PieceType pt) {
		return PieceScore::m_CapturePieceScore[pt];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const Sweetness GetPromotePieceScore(const PieceType pt) {
		assert(pt < PieceType::N07_Gold);
		return PieceScore::m_PromotePieceScore[pt];
	}
};
