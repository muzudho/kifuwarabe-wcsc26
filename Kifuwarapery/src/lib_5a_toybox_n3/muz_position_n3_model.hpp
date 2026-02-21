#pragma once

// MuzPositionN3Model では使ってないヘッダーファイルでも、他のクラスが MuzPositionN3Model をインクルードすれば lib_5a_toybox_n3 のヘッダーファイルが全部付いてくるようにします。
#include "../lib_5a_toybox_n2/muz_position_n2_model.hpp"
#include "square_ope.hpp"
#include <string_view>
#include <charconv>     // ← これが大事！ ParsePly() で std::from_chars を使ってる

class MuzPositionN3Model : public MuzPositionN2Model
{

protected:
	// ========================================
	// 主要メソッド
	// ========================================


	/// <summary>
	/// 局面をセット
	/// </summary>
	/// <param name="sfen"></param>
	void Set(std::string_view sfen);

    /// <summary>
    /// 盤上のマスに駒を置く
    /// </summary>
	bool ParseBoard(std::string_view board_str);

	bool ParseTurn(std::string_view turn_str);

	/// <summary>
    ///	駒台（持ち駒）をセット
	/// </summary>
	bool ParseHandStands(std::string_view hand_str);

	int ParsePly(std::string_view ply_str);
};
