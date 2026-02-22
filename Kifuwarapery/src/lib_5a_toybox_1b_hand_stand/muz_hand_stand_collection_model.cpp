#include "muz_hand_stand_collection_model.hpp"
#include <cctype>   // ← これ！ std::isdigit が定義されてるヘッダー


// ========================================
// 主要メソッド
// ========================================


// パース
bool MuzHandStandCollectionModel::parse_hand_stand_collection(
    std::string_view hand_str,
    MuzHandStandModel& blackHandStand,
    MuzHandStandModel& whiteHandStand)
{
    // 持ち駒がない場合は "-" で表す
    if (hand_str == "-")
    {
        // 先手と後手の持ち駒を０に戻すぜ（＾～＾）
        blackHandStand = MuzHandStandModel{};
        whiteHandStand = MuzHandStandModel{};
        return true;
    }

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

        MuzHandStandModel handStand;
        switch (c)
        {
        case Black: handStand = blackHandStand; break;
        case White: handStand = whiteHandStand; break;
        default:
            // ここは本来は例外を投げるべきだが、今回はとりあえずスキップする
            continue;
        }

        // カウントが0のときは1枚とみなす（例: "P" は "1P" と同じ意味）
        handStand.set_count(hp, count == 0 ? 1 : count);
        count = 0;
    }

    // 最後に残った数字は無視しない（エラー扱い可）
    return count == 0;
}
