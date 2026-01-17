#pragma once

#include "../n105_120_square__/n105_120_500_convSquare.hpp"
#include "../n105_180_piece___/n105_180_205_HandPieceExtensions.hpp"


class Position;


/// <summary>
/// 評価値リスト☆？（＾ｑ＾）
/// </summary>
class EvalList {


public:


	/// <summary>
	/// 
	/// </summary>
	static const int m_ListSize = 38;

	/// <summary>
	/// 
	/// </summary>
	int m_list0[m_ListSize];

	/// <summary>
	/// 
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
