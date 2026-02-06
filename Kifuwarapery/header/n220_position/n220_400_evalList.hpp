#pragma once

#include "../n105_120_square__/n105_120_500_convSquare.hpp"
#include "../n113_piece___/n113_205_convHandPiece.hpp"


class Position;


/// <summary>
/// 評価値リスト☆？（＾ｑ＾）
/// </summary>
class EvalList {


public:


	/// <summary>
	/// ２枚の玉を除いた駒の数（＾～＾）？
	/// </summary>
	static const int m_ListSize = 38;

	/// <summary>
	/// リスト０って何だぜ☆（＾～＾）？
	/// </summary>
	int m_list0[m_ListSize];

	/// <summary>
	/// リスト１って何だぜ☆（＾～＾）？
	/// </summary>
	int m_list1[m_ListSize];

	/// <summary>
	/// 
	/// </summary>
	Square m_listToSquareHand[m_ListSize];

	/// <summary>
	/// 
	/// </summary>
	int m_squareHandToList[SquareHandNum];


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	void Set(const Position& pos);
};


/// <summary>
/// 
/// </summary>
extern const Square g_HandPieceToSquareHand[g_COLOR_NUM][HandPieceNum];
