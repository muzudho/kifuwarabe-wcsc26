#include "muz_position_model.hpp"
#include <iostream>	// std::cout を使うために必要
#include <ranges>	// std::views::split と std::views::transform を使うために必要
#include <string_view>


// ========================================
// 生成／破棄
// ========================================


MuzPositionModel::MuzPositionModel()
{
    //// 盤上を空っぽにするぜ（＾～＾）
    //this->board_ = MuzBoardModel{};
}


// ========================================
// アクセッサー
// ========================================


const MuzBoardModel& MuzPositionModel::get_board() const
{
    return this->board_;
}
MuzBoardModel& MuzPositionModel::get_board()
{
    return this->board_;
}


// ========================================
// 主要メソッド
// ========================================


/// <summary>
///		<pre>
/// 局面をセットします。
/// sfen 形式の文字列を解析して、盤上の駒の配置、手番、持ち駒、次の手数などを Position クラスのメンバ変数に設定します。
/// また、ゲームエンジンのストレージモデルもセットします。
/// 解析に失敗した場合はエラーメッセージを出力します。
///		</pre>
/// </summary>
/// <param name="sfen"></param>
void MuzPositionModel::Set(std::string_view sfen)
{
	//MuzGameEngineStorageModel* s = std::move(gameEngineStore__);

	//this->Clear();

	//this->SetGameEngineStore(s);

	// コマンドをスペースで分割して、std::views::split と std::views::transform を使って、std::string_view の range を作る。
	auto parts = sfen
		| std::views::split(' ')
		| std::views::transform([](auto&& r)
			{
				return std::string_view(&*r.begin(), std::ranges::distance(r));
			});

	auto it = parts.begin();

	// 1. 盤面部分
	if (it == parts.end() || !this->get_board().update_from_string(*it)) {
		std::cout << "incorrect SFEN string (Board) : " << sfen << "\n";
		return;
	}
	++it;

	// 2. 手番
	if (it == parts.end() || !this->get_turn().update_from_string(*it)) {
		std::cout << "incorrect SFEN string (Turn) : " << sfen << "\n";
		return;
	}
	++it;

	// 3. 駒台（持ち駒）
	if (it == parts.end() || !this->get_hand_stand_collection().update_from_string(*it)) {
		std::cout << "incorrect SFEN string (Hand stand) : " << sfen << "\n";
		return;
	}
	++it;

	// 4. 手数（オプション）
	if (it != parts.end())
	{
		if (!this->get_ply_obj().update_from_string(this->get_turn(), *it)) {
			std::cout << "incorrect SFEN string (RadixHalfPly) : " << sfen << "\n";
			return;
		}
	}
}
