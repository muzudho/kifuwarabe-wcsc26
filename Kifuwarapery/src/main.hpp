// main.h :
//      標準のシステム インクルード ファイル用のインクルード ファイル、
//      または、プロジェクト専用のインクルード ファイル。

#pragma once
#include <iostream>
#include "../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../header/n160_board___/n160_100_bitboard.hpp"
#include "../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../header/n480_tt______/n480_300_tt.hpp"
#include "../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../header/n160_board___/n160_110_silverAttackBb.hpp"
#include "../header/n160_board___/n160_120_bishopAttackBb.hpp"
#include "../header/n160_board___/n160_130_lanceAttackBb.hpp"
#include "../header/n160_board___/n160_140_goldAttackBb.hpp"
#include "../header/n160_board___/n160_150_rookAttackBb.hpp"
#include "../header/n160_board___/n160_160_kingAttackBb.hpp"
#include "../header/n160_board___/n160_180_knightAttackBb.hpp"
#include "../header/n160_board___/n160_190_pawnAttackBb.hpp"
#include "../header/n161_sqDistan/n161_500_squareDistance.hpp"
#include "../header/n163_sqDistan/n163_600_utilSquareDistance.hpp"
#include "../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../header/n600_book____/n600_500_book.hpp"
#include "../header/n900_main____/n900_300_usiLoop.hpp"
#include "../src/layer_game_engine/game_engine_storage.hpp"
#include "../src/game_engine.hpp"
// プログラムに必要なヘッダーをここに追加してください。
