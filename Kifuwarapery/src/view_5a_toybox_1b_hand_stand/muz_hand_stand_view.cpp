#include "muz_hand_stand_view.hpp"


// ========================================
// 主要メソッド
// ========================================


void MuzHandStandView::print(Color color)
{
    if (color == Black)
    {
        std::cout << "黒（＾～＾）\n";
    }
    else if (color == White)
    {
        std::cout << "白（＾～＾）\n";
    }
    else
    {
        // 何もしません
        std::cout << "not found color = " << color << "\n";
    }
}
