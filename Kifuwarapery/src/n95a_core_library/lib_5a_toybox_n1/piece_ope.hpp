//
// 📄 駒の操作
//
//		- 循環参照を避けるため。
//

#pragma once

#include "../lib_5a_toybox_n1/muz_position_n1_model.hpp"

namespace {


	//────────────────────────────────────────────────────────────────────────────────
	// 非クラスメンバ 秘密 静的グローバル・オブジェクト
	//────────────────────────────────────────────────────────────────────────────────

	//────────────────────────────────────────────────────────────────────────────────
	// きふわらべは 計算が苦手なので、早見表を作っておこうぜ☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	/*
	// GetP == Empty のとき、PieceType は OccuPied になってしまうので、
	// Position::bbOf(UtilPiece::pieceToPieceType(GetP)) とすると、
	// Position::emptyBB() ではなく Position::occupiedBB() になってしまうので、
	// 注意すること。出来れば修正したい。
	static inline constexpr PieceType G_TO_PIECE_TYPE10(const Piece p) { return static_cast<PieceType>(p & 15); }
	static const PieceType g_CONV_PIECE_TO_PIECE_TYPE10[g_PIECE_NUM] = {
		G_TO_PIECE_TYPE10(Piece::N00_Empty),
		G_TO_PIECE_TYPE10(Piece::N01_BPawn),
		G_TO_PIECE_TYPE10(Piece::N02_BLance),
		G_TO_PIECE_TYPE10(Piece::N03_BKnight),
		G_TO_PIECE_TYPE10(Piece::N04_BSilver),
		G_TO_PIECE_TYPE10(Piece::N05_BBishop),
		G_TO_PIECE_TYPE10(Piece::N06_BRook),
		G_TO_PIECE_TYPE10(Piece::N07_BGold),
		G_TO_PIECE_TYPE10(Piece::N08_BKing),
		G_TO_PIECE_TYPE10(Piece::N09_BProPawn),
		G_TO_PIECE_TYPE10(Piece::N10_BProLance),
		G_TO_PIECE_TYPE10(Piece::N11_BProKnight),
		G_TO_PIECE_TYPE10(Piece::N12_BProSilver),
		G_TO_PIECE_TYPE10(Piece::N13_BHorse),
		G_TO_PIECE_TYPE10(Piece::N14_BDragon),
		G_TO_PIECE_TYPE10(Piece::N00_Empty),//15は欠番
		G_TO_PIECE_TYPE10(Piece::N00_Empty),//16は欠番
		G_TO_PIECE_TYPE10(Piece::N17_WPawn),
		G_TO_PIECE_TYPE10(Piece::N18_WLance),
		G_TO_PIECE_TYPE10(Piece::N19_WKnight),
		G_TO_PIECE_TYPE10(Piece::N20_WSilver),
		G_TO_PIECE_TYPE10(Piece::N21_WBishop),
		G_TO_PIECE_TYPE10(Piece::N22_WRook),
		G_TO_PIECE_TYPE10(Piece::N23_WGold),
		G_TO_PIECE_TYPE10(Piece::N24_WKing),
		G_TO_PIECE_TYPE10(Piece::N25_WProPawn),
		G_TO_PIECE_TYPE10(Piece::N26_WProLance),
		G_TO_PIECE_TYPE10(Piece::N27_WProKnight),
		G_TO_PIECE_TYPE10(Piece::N28_WProSilver),
		G_TO_PIECE_TYPE10(Piece::N29_WHorse),
		G_TO_PIECE_TYPE10(Piece::N30_WDragon),
		G_TO_PIECE_TYPE10(Piece::N31_PieceNone)
	};
	*/


	//────────────────────────────────────────────────────────────────────────────────
	// bit演算１回ケチるなんて　どうかしているぜ☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	static inline constexpr Piece G_INVERSE10(const Piece pc) { return static_cast<Piece>(pc ^ 0x10); }

	/// <summary>
	/// 
	/// </summary>
	static const Piece g_CONV_PIECE_INVERSE10[g_PIECE_NUM] = {
		G_INVERSE10(Piece::Empty),
		G_INVERSE10(Piece::BPawn),
		G_INVERSE10(Piece::BLance),
		G_INVERSE10(Piece::BKnight),
		G_INVERSE10(Piece::BSilver),
		G_INVERSE10(Piece::BBishop),
		G_INVERSE10(Piece::BRook),
		G_INVERSE10(Piece::BGold),
		G_INVERSE10(Piece::BKing),
		G_INVERSE10(Piece::BProPawn),
		G_INVERSE10(Piece::BProLance),
		G_INVERSE10(Piece::BProKnight),
		G_INVERSE10(Piece::BProSilver),
		G_INVERSE10(Piece::BHorse),
		G_INVERSE10(Piece::BDragon),
		G_INVERSE10(Piece::Empty),//15は欠番
		G_INVERSE10(Piece::Empty),//16は欠番
		G_INVERSE10(Piece::WPawn),
		G_INVERSE10(Piece::WLance),
		G_INVERSE10(Piece::WKnight),
		G_INVERSE10(Piece::WSilver),
		G_INVERSE10(Piece::WBishop),
		G_INVERSE10(Piece::WRook),
		G_INVERSE10(Piece::WGold),
		G_INVERSE10(Piece::WKing),
		G_INVERSE10(Piece::WProPawn),
		G_INVERSE10(Piece::WProLance),
		G_INVERSE10(Piece::WProKnight),
		G_INVERSE10(Piece::WProSilver),
		G_INVERSE10(Piece::WHorse),
		G_INVERSE10(Piece::WDragon),
		G_INVERSE10(Piece::PieceNone)
	};

	/*
	//────────────────────────────────────────────────────────────────────────────────
	// bit演算１回ケチるなんて　どうかしているぜ☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	static inline constexpr Color G_TO_COLOR10(const Piece p) {	return static_cast<Color>(p >> 4); }
	static const Color g_CONV_PIECE_TO_COLOR10[g_PIECE_NUM] = {
		G_TO_COLOR10(Piece::Empty),
		G_TO_COLOR10(Piece::BPawn),
		G_TO_COLOR10(Piece::BLance),
		G_TO_COLOR10(Piece::BKnight),
		G_TO_COLOR10(Piece::BSilver),
		G_TO_COLOR10(Piece::BBishop),
		G_TO_COLOR10(Piece::BRook),
		G_TO_COLOR10(Piece::BGold),
		G_TO_COLOR10(Piece::BKing),
		G_TO_COLOR10(Piece::BProPawn),
		G_TO_COLOR10(Piece::BProLance),
		G_TO_COLOR10(Piece::BProKnight),
		G_TO_COLOR10(Piece::BProSilver),
		G_TO_COLOR10(Piece::BHorse),
		G_TO_COLOR10(Piece::BDragon),
		G_TO_COLOR10(Piece::Empty),//15は欠番
		G_TO_COLOR10(Piece::Empty),//16は欠番
		G_TO_COLOR10(Piece::WPawn),
		G_TO_COLOR10(Piece::WLance),
		G_TO_COLOR10(Piece::WKnight),
		G_TO_COLOR10(Piece::WSilver),
		G_TO_COLOR10(Piece::WBishop),
		G_TO_COLOR10(Piece::WRook),
		G_TO_COLOR10(Piece::WGold),
		G_TO_COLOR10(Piece::WKing),
		G_TO_COLOR10(Piece::WProPawn),
		G_TO_COLOR10(Piece::WProLance),
		G_TO_COLOR10(Piece::WProKnight),
		G_TO_COLOR10(Piece::WProSilver),
		G_TO_COLOR10(Piece::WHorse),
		G_TO_COLOR10(Piece::WDragon),
		G_TO_COLOR10(Piece::PieceNone)
	};
	*/


	//────────────────────────────────────────────────────────────────────────────────
	// 暗算表を作るなら、複数回の演算を１回にしたいんだぜ☆ｗｗｗ（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────


	/// <summary>
	/// ピース が遠隔駒であるか
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	static inline constexpr bool G_IS_SLIDER10(const Piece pc) { return (g_CONV_PIECE_TYPE_SLIDER_VAL & (1 << pc)) != 0; }
	static const bool g_CONV_PIECE_IS_SLIDER10[g_PIECE_NUM] = {
		G_IS_SLIDER10(Piece::Empty),
		G_IS_SLIDER10(Piece::BPawn),
		G_IS_SLIDER10(Piece::BLance),
		G_IS_SLIDER10(Piece::BKnight),
		G_IS_SLIDER10(Piece::BSilver),
		G_IS_SLIDER10(Piece::BBishop),
		G_IS_SLIDER10(Piece::BRook),
		G_IS_SLIDER10(Piece::BGold),
		G_IS_SLIDER10(Piece::BKing),
		G_IS_SLIDER10(Piece::BProPawn),
		G_IS_SLIDER10(Piece::BProLance),
		G_IS_SLIDER10(Piece::BProKnight),
		G_IS_SLIDER10(Piece::BProSilver),
		G_IS_SLIDER10(Piece::BHorse),
		G_IS_SLIDER10(Piece::BDragon),
		G_IS_SLIDER10(Piece::Empty),//15は欠番
		G_IS_SLIDER10(Piece::Empty),//16は欠番
		G_IS_SLIDER10(Piece::WPawn),
		G_IS_SLIDER10(Piece::WLance),
		G_IS_SLIDER10(Piece::WKnight),
		G_IS_SLIDER10(Piece::WSilver),
		G_IS_SLIDER10(Piece::WBishop),
		G_IS_SLIDER10(Piece::WRook),
		G_IS_SLIDER10(Piece::WGold),
		G_IS_SLIDER10(Piece::WKing),
		G_IS_SLIDER10(Piece::WProPawn),
		G_IS_SLIDER10(Piece::WProLance),
		G_IS_SLIDER10(Piece::WProKnight),
		G_IS_SLIDER10(Piece::WProSilver),
		G_IS_SLIDER10(Piece::WHorse),
		G_IS_SLIDER10(Piece::WDragon),
		G_IS_SLIDER10(Piece::PieceNone)
	};
}


/// <summary>
/// 駒の操作
/// </summary>
class ConvPiece {


public:


	/// <summary>
	/// ピースを、ピースタイプに変換だぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	static inline PieceType TO_PIECE_TYPE10(const Piece p) {
		return static_cast<PieceType>(p & 15);//ビット演算を使うぜ☆（＾ｑ＾）
		//return g_CONV_PIECE_TO_PIECE_TYPE10[p];//暗算表を使うぜ☆（＾ｑ＾）
	}


	/// <summary>
	/// ピースの白黒を反転だぜ☆（＾ｑ＾）
	/// 暗算表を使うぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	static inline Piece INVERSE10(const Piece pc) { return g_CONV_PIECE_INVERSE10[pc]; }


	/// <summary>
	/// ピースの白黒を取得だぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	static inline Color TO_COLOR10(const Piece p) {
		//assert(p != N00_Empty);
		return static_cast<Color>(p >> 4);//ビット演算を使うぜ☆（＾ｑ＾）
		//return g_CONV_PIECE_TO_COLOR10[p];//暗算表を使うぜ☆（＾ｑ＾）
	}


	/// <summary>
	/// ピース が遠隔駒であるかどうか調べるぜ☆（＾ｑ＾）
	/// 暗算表を使うぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="pc"></param>
	/// <returns></returns>
	static inline bool IS_SLIDER10(const Piece pc) { return g_CONV_PIECE_IS_SLIDER10[pc]; }


	/// <summary>
	/// これは計算しないとタイヘンか☆（＾ｑ＾）
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <param name="pt"></param>
	/// <returns></returns>
	template<Color CLR>
	static inline Piece FROM_COLOR_AND_PIECE_TYPE10(const PieceType pt) { return static_cast<Piece>((CLR << 4) | pt); }
	static inline Piece FROM_COLOR_AND_PIECE_TYPE10(const Color c, const PieceType pt) { return static_cast<Piece>((c << 4) | pt); }
};
