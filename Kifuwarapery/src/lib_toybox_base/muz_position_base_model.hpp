//
// 📄 局面の状態を表すクラス
//
#pragma once
#include "color.hpp"
#include "ply.hpp"
#include "piece.hpp"
#include "hand.hpp"
#include "square.hpp"


class MuzPositionBaseModel
{


protected:


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// 次の手番
	/// </summary>
	/// <returns></returns>
	Color GetTurn() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Ply GetGamePly() const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ply"></param>
	void SetStartPosPly(const Ply ply);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	Piece GetPiece(const Square sq) const;


	/// <summary>
	/// 持ち駒
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <returns></returns>
	template<Color CLR>
	Hand GetHand() const
	{
		return this->m_hand_[CLR];
	}
	Hand GetHand(const Color c) const;


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// 何手目か。時間管理に使用する
	/// </summary>
	Ply m_gamePly_;

	/// <summary>
	/// 手番
	/// </summary>
	Color m_turn_;

	/// <summary>
	/// 各マスの駒
	/// </summary>
	Piece m_piece_[SquareNum];

	/// <summary>
	/// 先後対局者別の手駒
	/// </summary>
	Hand m_hand_[g_COLOR_NUM];

};

