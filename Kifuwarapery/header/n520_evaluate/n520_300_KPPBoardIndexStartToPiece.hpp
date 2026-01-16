#pragma once


#include <unordered_map>
#include "../n105_180_piece___/n105_180_205_convHandPiece.hpp"
#include "../n160_boardBb_/n160_600_bitboardAll.hpp"
#include "../n520_evaluate/n520_150_kppIndexArray.hpp"


/// <summary>
/// 
/// </summary>
struct KPPBoardIndexStartToPiece : public std::unordered_map<int, Piece> {


	/// <summary>
	/// 生成。
	/// </summary>
	KPPBoardIndexStartToPiece() {
		(*this)[f_pawn] = N01_BPawn;
		(*this)[e_pawn] = N17_WPawn;
		(*this)[f_lance] = N02_BLance;
		(*this)[e_lance] = N18_WLance;
		(*this)[f_knight] = N03_BKnight;
		(*this)[e_knight] = N19_WKnight;
		(*this)[f_silver] = N04_BSilver;
		(*this)[e_silver] = N20_WSilver;
		(*this)[f_gold] = N07_BGold;
		(*this)[e_gold] = N23_WGold;
		(*this)[f_bishop] = N05_BBishop;
		(*this)[e_bishop] = N21_WBishop;
		(*this)[f_horse] = N13_BHorse;
		(*this)[e_horse] = N29_WHorse;
		(*this)[f_rook] = N06_BRook;
		(*this)[e_rook] = N22_WRook;
		(*this)[f_dragon] = N14_BDragon;
		(*this)[e_dragon] = N30_WDragon;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="i"></param>
	/// <returns></returns>
	Piece value(const int i) const {
		const auto it = find(i);
		if (it == std::end(*this))
			return N31_PieceNone;
		return it->second;
	}
};


/// <summary>
/// 
/// </summary>
extern KPPBoardIndexStartToPiece g_kppBoardIndexStartToPiece;
