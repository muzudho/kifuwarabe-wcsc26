#include "muz_position_n3_model.hpp"
#include "../n95a55b_toybox_103c_ply/muz_ply_model.hpp"
#include <string_view>
#include <ranges>	// std::views::split と std::views::transform を使うために必要
#include <iostream>	// std::cout を使うために必要


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
void MuzPositionN3Model::Set(std::string_view sfen)
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
	if (it == parts.end() || !this->get_board().from_string(*it)) {
		std::cout << "incorrect SFEN string (Board) : " << sfen << "\n";
		return;
	}
	++it;

	// 2. 手番
	if (it == parts.end() || !this->get_turn().from_string(*it)) {
		std::cout << "incorrect SFEN string (Turn) : " << sfen << "\n";
		return;
	}
	++it;

	// 3. 駒台（持ち駒）
    MuzHandStandModel blackHandStand, whiteHandStand;	// TODO: これらの変数は、Position クラスのメンバ変数にしたい（＾～＾）
    MuzHandStandCollectionService handStandCollectionSvc;
	if (it == parts.end() || !handStandCollectionSvc.parse_hand_stand_collection(*it, blackHandStand, whiteHandStand)) {
		std::cout << "incorrect SFEN string (Hand stand) : " << sfen << "\n";
		return;
	}
	++it;

	// 4. 手数（オプション）
	if (it != parts.end())
	{
        MuzTurnModel turn = this->get_turn();	// TODO: これ、仮なんで修正したい（＾～＾）
		if (auto muz_ply = MuzPlyModel::from_string(turn, *it)) {
			m_gamePly_ = muz_ply->get_game_ply();
		}
		else {
			std::cout << "incorrect SFEN string (Ply) : " << sfen << "\n";
			return;
		}
	}
}


