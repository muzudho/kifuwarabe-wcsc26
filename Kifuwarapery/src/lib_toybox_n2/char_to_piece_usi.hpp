#pragma once

#include "../lib_toybox_n1/muz_position_n1_model.hpp"
#include <map>

/// <summary>
/// 
/// </summary>
class CharToPieceUSI : public std::map<char, Piece>
{

public:


    /// <summary>
    /// 
    /// </summary>
    CharToPieceUSI()
    {
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
    Piece GetValue(char c) const { return this->find(c)->second; }


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
