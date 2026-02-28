#pragma once

// MuzPositionN3Model では使ってないヘッダーファイルでも、他のクラスが MuzPositionN3Model をインクルードすれば lib_5a_toybox_n3 のヘッダーファイルが全部付いてくるようにします。
#include "../lib_5a_toybox_n2/muz_position_n2_model.hpp"
#include "../n95a55b_toybox_95c_hand_stand/muz_hand_stand_model.hpp"
#include "../n95a55b_toybox_95c_hand_stand/muz_hand_stand_collection_service.hpp"
#include <string_view>

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
};
