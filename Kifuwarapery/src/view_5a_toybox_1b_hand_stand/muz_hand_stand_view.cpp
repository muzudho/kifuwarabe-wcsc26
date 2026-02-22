#include "muz_hand_stand_view.hpp"
#include <iomanip>   // ← これ必須！ setw, right とか入ってる


// ========================================
// 主要メソッド
// ========================================


void MuzHandStandView::print_black(const MuzHandStandModel& h)
{
    std::cout << "  飛  角  金  銀  桂  香  歩\n"
        << "  " << std::right << std::setw(2) << h.get_count(HRook)
        << "  " << std::right << std::setw(2) << h.get_count(HBishop)
        << "  " << std::right << std::setw(2) << h.get_count(HGold)
        << "  " << std::right << std::setw(2) << h.get_count(HSilver)
        << "  " << std::right << std::setw(2) << h.get_count(HKnight)
        << "  " << std::right << std::setw(2) << h.get_count(HLance)
        << "  " << std::right << std::setw(2) << h.get_count(HPawn) << "\n";
}


void MuzHandStandView::print_white(const MuzHandStandModel& handStand)
{
    print_black(handStand);   // とりあえず同じ表示でいいか（＾～＾）
}
