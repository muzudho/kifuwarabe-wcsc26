#pragma once

#include <stack>
#include <memory>
#include <map>
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n113_piece___/n113_205_convHandPiece.hpp"
#include "../../src/lib_toybox_base/hand.hpp"
#include "../n119_500_sweetnes/n119_200_PieceSweetness.hpp"
#include "../../src/lib_bitboard/init110_silverAttackBb.hpp"
#include "../../src/lib_bitboard/init120_bishopAttackBb.hpp"
#include "../../src/lib_bitboard/init130_lanceAttackBb.hpp"
#include "../../src/lib_bitboard/init150_rookAttackBb.hpp"
#include "../../src/lib_bitboard/init160_kingAttackBb.hpp"
#include "../../src/lib_bitboard/init180_knightAttackBb.hpp"
#include "../../src/lib_bitboard/init190_pawnAttackBb.hpp"
#include "../../src/lib_bitboard/n160_200_horseAttackBb.hpp"
#include "../../src/lib_bitboard/n160_210_dragonAttackBb.hpp"
#include "../../src/lib_bitboard/n160_400_printBb.hpp"
#include "../../src/lib_bitboard/n160_600_bitboardAll.hpp"
#include "../n220_position/n220_400_evalList.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n350_pieceTyp/n350_110_ptPawn.hpp"
#include "../n350_pieceTyp/n350_120_ptLance.hpp"
#include "../n350_pieceTyp/n350_130_ptKnight.hpp"
#include "../n350_pieceTyp/n350_140_ptSilver.hpp"
#include "../n350_pieceTyp/n350_150_ptBishop.hpp"
#include "../n350_pieceTyp/n350_160_ptRook.hpp"
#include "../n350_pieceTyp/n350_180_ptKing.hpp"
#include "../n350_pieceTyp/n350_230_ptHorse.hpp"
#include "../n350_pieceTyp/n350_240_ptDragon.hpp"




/// <summary>
/// 
/// </summary>
class CharToPieceUSI : public std::map<char, Piece> {

public:


	/// <summary>
	/// 
	/// </summary>
	CharToPieceUSI() {
		(*this)['P'] = N01_BPawn;   (*this)['p'] = N17_WPawn;
		(*this)['L'] = N02_BLance;  (*this)['l'] = N18_WLance;
		(*this)['N'] = N03_BKnight; (*this)['n'] = N19_WKnight;
		(*this)['S'] = N04_BSilver; (*this)['s'] = N20_WSilver;
		(*this)['B'] = N05_BBishop; (*this)['b'] = N21_WBishop;
		(*this)['R'] = N06_BRook;   (*this)['r'] = N22_WRook;
		(*this)['G'] = N07_BGold;   (*this)['g'] = N23_WGold;
		(*this)['K'] = N08_BKing;   (*this)['k'] = N24_WKing;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	Piece GetValue(char c) const      { return this->find(c)->second; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	bool IsLegalChar(char c) const { return (this->find(c) != this->end()); }
};


/// <summary>
/// 
/// </summary>
extern const CharToPieceUSI g_charToPieceUSI;
