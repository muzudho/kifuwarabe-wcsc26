#pragma once

#include <stack>
#include <memory>
#include <map>
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_180_piece___/n105_180_205_HandPieceExtensions.hpp"
#include "../n105_180_piece___/n105_180_500_Hand.hpp"
#include "../n210_score___/n119_200_pieceScore.hpp"
#include "../n130_100_boardBb_/n160_110_silverAttackBb.hpp"
#include "../n130_100_boardBb_/n160_120_bishopAttackBb.hpp"
#include "../n130_100_boardBb_/n160_130_lanceAttackBb.hpp"
#include "../n130_100_boardBb_/n160_150_rookAttackBb.hpp"
#include "../n130_100_boardBb_/n160_160_kingAttackBb.hpp"
#include "../n130_100_boardBb_/n160_180_knightAttackBb.hpp"
#include "../n130_100_boardBb_/n160_190_pawnAttackBb.hpp"
#include "../n130_100_boardBb_/n160_200_horseAttackBb.hpp"
#include "../n130_100_boardBb_/n160_210_dragonAttackBb.hpp"
#include "../n130_100_boardBb_/n160_400_printBb.hpp"
#include "../n130_100_boardBb_/n160_600_bitboardAll.hpp"
#include "../n220_position/n220_400_evalList.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n250_pieceTyp/n350_110_ptPawn.hpp"
#include "../n250_pieceTyp/n350_120_ptLance.hpp"
#include "../n250_pieceTyp/n350_130_ptKnight.hpp"
#include "../n250_pieceTyp/n350_140_ptSilver.hpp"
#include "../n250_pieceTyp/n350_150_ptBishop.hpp"
#include "../n250_pieceTyp/n350_160_ptRook.hpp"
#include "../n250_pieceTyp/n350_180_ptKing.hpp"
#include "../n250_pieceTyp/n350_230_ptHorse.hpp"
#include "../n250_pieceTyp/n350_240_ptDragon.hpp"


/// <summary>
/// 平手初期局面の SFEN 文字列☆（＾▽＾）
/// </summary>
const std::string g_DefaultStartPositionSFEN = "lnsgkgsnl/1r5b1/ppppppppp/9/9/9/PPPPPPPPP/1B5R1/LNSGKGSNL b - 1";


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
