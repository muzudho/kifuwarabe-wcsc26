#pragma once

// MuzPositionN1Model では使ってないヘッダーファイルでも、他のクラスが MuzPositionN1Model をインクルードすれば lib_5a_toybox_n1 のヘッダーファイルが全部付いてくるようにします。
#include "color.hpp"
#include "file.hpp"
#include "piece.hpp"
#include "piece_type.hpp"
#include "ply.hpp"
#include "rank.hpp"
#include "square.hpp"
#include "square_delta.hpp"

class MuzPositionN1Model
{


protected:


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


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ply"></param>
	void SetStartPosPly(const Ply ply);


	/// <summary>
	/// 何手目か
	/// </summary>
	/// <returns></returns>
	Ply GetGamePly();


	/// <summary>
	/// 次の手番
	/// </summary>
	/// <returns></returns>
	Color GetTurn();


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	Piece GetPiece(const Square sq);

	void SetPiece(const Piece piece, const Square sq);


};