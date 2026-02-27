#pragma once

#include "../lib_5a_toybox_1b_hand_stand/color.hpp"
#include "../lib_5a_toybox_1b_hand_stand/muz_hand_stand_model.hpp"
#include <iostream>

/// <summary>
/// 駒台の描画
/// </summary>
class MuzHandStandView
{
public:


    // ========================================
    // 主要メソッド
    // ========================================


    static void print_black(const MuzHandStandModel& handStand);
    static void print_white(const MuzHandStandModel& handStand);
};
