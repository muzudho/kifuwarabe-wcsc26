#pragma once

#include "piece.hpp"
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
        (*this)['P'] = BPawn;   (*this)['p'] = WPawn;
        (*this)['L'] = BLance;  (*this)['l'] = WLance;
        (*this)['N'] = BKnight; (*this)['n'] = WKnight;
        (*this)['S'] = BSilver; (*this)['s'] = WSilver;
        (*this)['B'] = BBishop; (*this)['b'] = WBishop;
        (*this)['R'] = BRook;   (*this)['r'] = WRook;
        (*this)['G'] = BGold;   (*this)['g'] = WGold;
        (*this)['K'] = BKing;   (*this)['k'] = WKing;
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
