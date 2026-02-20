// main.h :
//      標準のシステム インクルード ファイル用のインクルード ファイル、
//      または、プロジェクト専用のインクルード ファイル。

#pragma once

#include <iostream>
#include "../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../src/lib_toybox_base/char_to_piece_usi.hpp"
#include "../header/n480_tt______/n480_300_tt.hpp"
#include "../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../src/lib_bitboard/n160_100_bitboard.hpp"
#include "../src/lib_bitboard/init110_silverAttackBb.hpp"
#include "../src/lib_bitboard/init120_bishopAttackBb.hpp"
#include "../src/lib_bitboard/init130_lanceAttackBb.hpp"
#include "../src/lib_bitboard/init140_goldAttackBb.hpp"
#include "../src/lib_bitboard/init150_rookAttackBb.hpp"
#include "../src/lib_bitboard/init160_kingAttackBb.hpp"
#include "../src/lib_bitboard/init180_knightAttackBb.hpp"
#include "../src/lib_bitboard/init190_pawnAttackBb.hpp"
#include "../header/n161_sqDistan/n161_500_squareDistance.hpp"
#include "../header/n163_sqDistan/n163_600_utilSquareDistance.hpp"
#include "../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../header/n600_book____/n600_500_book.hpp"
#include "../header/n900_main____/n900_300_usiLoop.hpp"
#include "../src/concept_game_engine/muz_game_engine_storage_model.hpp"
#include "../src/muz_game_engine_service.hpp"
// プログラムに必要なヘッダーをここに追加してください。
