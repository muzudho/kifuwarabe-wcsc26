#pragma once

#include "char_to_piece_usi.hpp"
#include "file.hpp"
#include "file_ope.hpp"
#include "piece.hpp"
#include "rank.hpp"
#include "rank_ope.hpp"
#include "square.hpp"
#include "square_delta.hpp"
#include "square_ope.hpp"
#include <string_view>

/// <summary>
///		<pre>
/// ボードの状態を表すぜ（＾～＾）
///     </pre>
/// </summary>
class MuzBoardModel
{


	// ========================================
	// フィールド
	// ========================================


private:
	/// <summary>
	/// 各マスの駒
	/// </summary>
	Piece piece_[SquareNum];


	// ========================================
	// アクセッサ
	// ========================================


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	const Piece get_piece(const Square sq) const;

	void set_piece(const Square sq, const Piece piece);


	// ========================================
	// 主要メソッド
	// ========================================


	/// <summary>
	/// 盤面をクリアーするぜ（＾～＾）
	/// </summary>
	void clear() {
		std::fill(std::begin(piece_), std::end(piece_), Piece::Empty);
    }


	/// <summary>
	///		<pre>
	/// 盤上のマスに駒を置く
	/// 
	///		- 旧名： `ParseBoard`
	///		</pre>
	/// </summary>
	bool from_string(std::string_view board_str);
};
