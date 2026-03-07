#include "muz_stationaly_position_model.hpp"
#include <iostream>	// std::cout を使うために必要
#include <ranges>	// std::views::split と std::views::transform を使うために必要
#include <string_view>
#include <vector>


// ========================================
// 生成／破棄
// ========================================


MuzStationalyPositionModel::MuzStationalyPositionModel()
{
    //// 盤上を空っぽにするぜ（＾～＾）
    //this->board_ = MuzBoardModel{};
}


// ========================================
// アクセッサー
// ========================================


const MuzBoardModel& MuzStationalyPositionModel::get_board() const
{
    return this->board_;
}
MuzBoardModel& MuzStationalyPositionModel::get_board()
{
    return this->board_;
}


// ========================================
// 主要メソッド
// ========================================


void MuzStationalyPositionModel::Set(std::span<std::string_view> parameter_tokens)
{
	auto it = parameter_tokens.begin();

	// 初期化（＾～＾）
    this->get_board().clear();
    this->get_turn().clear();
    this->get_hand_stand_collection().clear();
    this->get_ply_obj().clear();

	// 1. 盤面部分
	if (it == parameter_tokens.end() || !this->get_board().update_from_string(*it)) {
		std::cout << "incorrect SFEN string (Board).\n";
		return;
	}
	++it;

	// 2. 手番
	if (it == parameter_tokens.end() || !this->get_turn().update_from_string(*it)) {
        std::cout << "incorrect SFEN string (Turn).\n";	// TODO: 読取終わった board を出力して、どこで失敗したのか分かるようにしたいぜ（＾～＾）
		return;
	}
	++it;

	// 3. 駒台（持ち駒）
	if (it == parameter_tokens.end() || !this->get_hand_stand_collection().update_from_string(*it)) {
		std::cout << "incorrect SFEN string (Hand stand).\n";
		return;
	}
	++it;

	// 4. 手数（オプション）
	if (it != parameter_tokens.end())
	{
        auto turn = this->get_turn();
		if (!this->get_ply_obj().update_from_string(turn, *it)) {
			std::cout << "incorrect SFEN string (RadixHalfPly).\n";
			return;
		}
	}

    // moves の解析は、ここでは行わないぜ（＾～＾）
	// `Position::set()` を呼び出した後に、 ループを回しながらやるぜ（＾～＾）
    // 例えば［大樹の枝］の `usi.cpp/setPosition()` を参考にしてほしいぜ（＾～＾）
}
