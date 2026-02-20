#pragma once

// MuzPositionN3Model では使ってないヘッダーファイルでも、他のクラスが MuzPositionN3Model をインクルードすれば lib_toybox_n3 のヘッダーファイルが全部付いてくるようにします。
#include "../lib_toybox_n2/muz_position_n2_model.hpp"
#include "square_ope.hpp"
#include <string_view>

class MuzPositionN3Model : public MuzPositionN2Model
{

protected:
	// ========================================
	// 主要メソッド
	// ========================================

	// TODO: void Set(std::string_view sfen);

	bool ParseBoard(std::string_view board_str);

	// TODO: bool ParseTurn(std::string_view turn_str);
	// TODO: bool ParseHand(std::string_view hand_str);
	// TODO: int ParsePly(std::string_view ply_str);
};
