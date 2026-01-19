#pragma once
#include "../n113_piece___/n113_150_piece.hpp"
#include "../n113_piece___/n113_205_convHandPiece.hpp"
#include "n119_090_Sweetness.hpp"
#include "n119_100_UtilSweetness.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 駒の価値
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
///		<pre>
/// 駒の価値
///		</pre>
/// </summary>
class PieceSweetness {


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
	static const Sweetness m_captureProSilver;
	static const Sweetness m_captureHorse;
	static const Sweetness m_captureDragon;
	static const Sweetness m_captureKing;

	static const Sweetness m_PromotePawn;
	static const Sweetness m_PromoteLance;
	static const Sweetness m_PromoteKnight;
	static const Sweetness m_PromoteSilver;
	static const Sweetness m_PromoteBishop;
	static const Sweetness m_PromoteRook;

	static const Sweetness m_sweetnessKnownWin;

	static const Sweetness m_pieceArray[Piece::N31_PieceNone];
	static const Sweetness m_capturePieceArray[Piece::N31_PieceNone];
	static const Sweetness m_promotePieceArray[7];


public:


	/// <summary>
	/// Piece を index としても、 PieceType を index としても、
	/// 同じ値が取得出来るようにしているので、PieceType => Piece への変換は必要ない。
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const Sweetness getSweetnessByPiece(const PieceType pt) {
		return PieceSweetness::m_pieceArray[pt];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	inline static const Sweetness getSweetnessByPiece(const Piece pc) {
		return PieceSweetness::m_pieceArray[pc];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	inline static const Sweetness getSweetnessByCapturePiece(const Piece pc) {
		return PieceSweetness::m_capturePieceArray[pc];
	}


	/// <summary>
	/// Piece を index としても、 PieceType を index としても、
	/// 同じ値が取得出来るようにしているので、PieceType => Piece への変換は必要ない。
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const Sweetness getSweetnessByCapturePiece(const PieceType pt) {
		return PieceSweetness::m_capturePieceArray[pt];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pt"></param>
	/// <returns></returns>
	inline static const Sweetness getSweetnessByPromotePiece(const PieceType pt) {
		assert(pt < PieceType::N07_Gold);
		return PieceSweetness::m_promotePieceArray[pt];
	}
};
