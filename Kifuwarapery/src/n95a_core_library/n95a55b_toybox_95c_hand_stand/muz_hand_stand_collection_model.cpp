#include "../n95a55b_toybox_105c_turn/color.hpp"
#include "muz_hand_stand_collection_model.hpp"
#include <cctype>   // ← これ！ std::isdigit が定義されてるヘッダー


// ========================================
// 生成／破棄
// ========================================


MuzHandStandCollectionModel::MuzHandStandCollectionModel()
{
    this->hand_stands_[Black] = MuzHandStandModel{};
    this->hand_stands_[White] = MuzHandStandModel{};
}


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
MuzHandStandModel MuzHandStandCollectionModel::get_hand_stand(const Color c) const
{
    return this->hand_stands_[c];
}


// ========================================
// 主要メソッド
// ========================================


bool MuzHandStandCollectionModel::update_from_string(std::string_view hand_str)
{
    auto result = MuzHandStandCollectionModel::parse(hand_str);
    if (result) {
        auto [b_hs, w_hs] = result.value();
        this->hand_stands_[Black] = b_hs;
        this->hand_stands_[White] = w_hs;
        return true;
    }

    return false;
}


// ========================================
// サブルーチン
// ========================================


std::optional<std::pair<MuzHandStandModel, MuzHandStandModel>> MuzHandStandCollectionModel::parse(
    std::string_view hand_str)
{
    // 初期化（＾～＾）先手と後手の持ち駒を０に戻すぜ（＾～＾）
    auto b_hs = MuzHandStandModel{};
    auto w_hs = MuzHandStandModel{};

    // 持ち駒がない場合は "-" で表す
    if (hand_str == "-") return std::make_optional(std::make_pair(b_hs, w_hs));

    std::size_t count = 0;

    for (char ch : hand_str)
    {
        Color c;
        HandPiece hp;

        // 数字が続く場合は、次の駒の枚数を表す
        if (std::isdigit(ch))
        {
            count = count * 10 + (ch - '0');
            continue;
        }

        // 駒の種類を表す文字が来たら、枚数をセットして、カウントをリセット
        switch (ch)
        {
        case 'P': c = Black; hp = HPawn; break;
        case 'L': c = Black; hp = HLance; break;
        case 'N': c = Black; hp = HKnight; break;
        case 'S': c = Black; hp = HSilver; break;
        case 'G': c = Black; hp = HGold; break;
        case 'B': c = Black; hp = HBishop; break;
        case 'R': c = Black; hp = HRook; break;
        case 'p': c = White; hp = HPawn; break;
        case 'l': c = White; hp = HLance; break;
        case 'n': c = White; hp = HKnight; break;
        case 's': c = White; hp = HSilver; break;
        case 'g': c = White; hp = HGold; break;
        case 'b': c = White; hp = HBishop; break;
        case 'r': c = White; hp = HRook; break;
        default:
            // ここは本来は例外を投げるべきだが、今回はとりあえずスキップする
            continue;
        }

        // カウントが0のときは1枚とみなす（例: "P" は "1P" と同じ意味）
        if (count == 0) {
            count = 1;
        }

        switch (c)
        {
        case Black: b_hs.set_count(hp, count); break;
        case White: w_hs.set_count(hp, count); break;
        default:
            // ここは本来は例外を投げるべきだが、今回はとりあえずスキップする
            continue;
        }

        // 枚数をリセット        
        count = 0;
    }

    // 最後に残った数字は無視しない（エラー扱い可）
    if (count != 0) {
        return std::nullopt;
    }

    return std::make_optional(std::make_pair(b_hs, w_hs));
}
