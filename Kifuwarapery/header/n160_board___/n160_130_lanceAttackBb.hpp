#pragma once

#include "../n105_color___/n105_100_color.hpp"
#include "../n110_square__/n110_100_square.hpp"
#include "n160_100_bitboard.hpp"
#include "n160_108_slideBits.hpp"


/// <summary>
/// 香の利きビットボード
/// </summary>
class LanceAttackBb {


public:


	/// <summary>
	/// メモリ節約をせず、無駄なメモリを持っている。
	/// </summary>
	Bitboard m_controllBb[g_COLOR_NUM][SquareNum][128];


private:


	/// <summary>
	/// メモリ節約をせず、無駄なメモリを持っている。
	/// </summary>
	Bitboard m_controllBbToEdge_[g_COLOR_NUM][SquareNum];

	/// <summary>
	/// 
	/// </summary>
	Bitboard m_lanceCheckTable_[g_COLOR_NUM][SquareNum];


public:


	/// <summary>
	/// 
	/// </summary>
	void Initialize();


	/// <summary>
	/// 
	/// </summary>
	void InitCheckTableLance();


	/// <summary>
	/// 障害物が無いときの利きの Bitboard
	/// g_rookAttack, g_bishopAttack, g_lanceAttack を設定してから、この関数を呼ぶこと。
	/// </summary>
	void InitializeToEdge();


	/// <summary>
	/// todo: 香車の筋がどこにあるか先に分かっていれば、Bitboard の片方の変数だけを調べれば良くなる。
	/// </summary>
	/// <param name="thisBitboard"></param>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	Bitboard GetControllBb(const Bitboard& thisBitboard, const Color c, const Square sq) const {
		const int part = Bitboard::Part(sq);
		const int index = (thisBitboard.GetP(part) >> g_slideBits.m_slide[sq]) & 127;
		return this->m_controllBb[c][sq][index];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	Bitboard GetControllBbToEdge(const Color c, const Square sq) const {
		return this->m_controllBbToEdge_[c][sq];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	Bitboard LanceCheckTable(const Color c, const Square sq) const {
		return this->m_lanceCheckTable_[c][sq];
	}


private:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="square"></param>
	/// <returns></returns>
	Bitboard LanceBlockMask(const Square square);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <param name="square"></param>
	/// <param name="occupied"></param>
	/// <returns></returns>
	Bitboard LanceAttackCalc(const Color c, const Square square, const Bitboard& occupied);
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern LanceAttackBb g_lanceAttackBb;
