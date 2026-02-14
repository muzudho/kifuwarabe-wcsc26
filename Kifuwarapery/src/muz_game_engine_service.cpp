#include "../header/n080_100_sysWorld/n080_100_500_common.hpp"
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
#include "../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../header/n600_book____/n600_500_book.hpp"
#include "../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../header/n900_main____/n900_300_usiLoop.hpp"
#include "../src/lib_gui/muz_engine_settings_initialize_service.hpp"
#include "../src/muz_game_engine_service.hpp"
#include "../src/layer_game_engine/muz_game_engine_storage_model.hpp"
#include <iostream>


// ========================================
// 生成／破棄
// ========================================


/// <summary>
/// 生成
/// </summary>
MuzGameEngineService::MuzGameEngineService()
{
    this->m_pGameEngineStore = std::unique_ptr<MuzGameEngineStorageModel>(new MuzGameEngineStorageModel);
}


/// <summary>
/// 破棄。
/// </summary>
MuzGameEngineService::~MuzGameEngineService()
{
    this->m_pGameEngineStore.reset();
}


// ========================================
// ライフサイクルメソッド
// ========================================


/// <summary>
/// 最初の設定
/// </summary>
void MuzGameEngineService::initialize_10a()
{
    //────────────────────────────────────────────────────────────────────────────────
    // ビットボードとテーブルの初期化☆（＾ｑ＾）
    //────────────────────────────────────────────────────────────────────────────────
    {
        SYNCCOUT << "(^q^) 1   . ビットボードとテーブルを初期化するぜ！" << SYNCENDL;

#ifndef SKIP_LONG_TIME_EVAL
        // 長い時間が掛かる初期化処理をするか？
        SYNCCOUT << "(^q^) 1- 1. 飛の利きビットボードの初期化！" << SYNCENDL;
        g_rookAttackBb.initialize_10a100b_rookAttacks();
#endif

        SYNCCOUT << "(^q^) 1- 2. 角の利きビットボードの初期化！" << SYNCENDL;
        g_bishopAttackBb.initialize_10a120b_bishopAttacks();

        SYNCCOUT << "(^q^) 1- 3. 玉の利きビットボードの初期化！" << SYNCENDL;
        g_kingAttackBb.initialize_10a130b_kingAttacks();

        SYNCCOUT << "(^q^) 1- 4. 金の利きビットボードの初期化！" << SYNCENDL;
        g_goldAttackBb.initialize_10a140b_goldAttacks();

        SYNCCOUT << "(^q^) 1- 5. 銀の利きビットボードの初期化！" << SYNCENDL;
        g_silverAttackBb.initialize_10a150b_silverAttacks();

        SYNCCOUT << "(^q^) 1- 6. 歩の利きビットボードの初期化！" << SYNCENDL;
        g_pawnAttackBb.initialize_10a160b_pawnAttacks();

        SYNCCOUT << "(^q^) 1- 7. 桂の利きビットボードの初期化！" << SYNCENDL;
        g_knightAttackBb.initialize_10a170b_knightAttacks();

        SYNCCOUT << "(^q^) 1- 8. 香の利きビットボードの初期化！" << SYNCENDL;
        g_lanceAttackBb.initialize_10a180b_lanceAttacks();

        SYNCCOUT << "(^q^) 1- 9. ２つのマスの位置関係が［同筋］［同段］［同右肩上がり］［同右肩下がり］［その他］かを区別するビットボードの初期化！" << SYNCENDL;
        g_squareRelation.initialize_10a190b_squareRelations();


        // 障害物が無いときの利きの Bitboard
        // g_rookAttack, g_bishopAttack, g_lanceAttack を設定してから、この関数を呼ぶこと。


        SYNCCOUT << "(^q^) 1-10. 障害物が無いときの飛の利きビットボードの初期化！" << SYNCENDL;
        g_rookAttackBb.initialize_10a200b_rookToEdge();

        SYNCCOUT << "(^q^) 1-11. 障害物が無いときの角の利きビットボードの初期化！" << SYNCENDL;
        g_bishopAttackBb.Initialize_10a210b_bishopToEdge();

        SYNCCOUT << "(^q^) 1-12. 障害物が無いときの香の利きビットボードの初期化！" << SYNCENDL;
        g_lanceAttackBb.initialize_10a220b_lanceToEdge();

        SYNCCOUT << "(^q^) 1-13. ［飛車、角の元位置］と、［その利き］の２点のビットボード？の初期化！" << SYNCENDL;
        g_betweenBb.Initialize_10a230b_between();

        SYNCCOUT << "(^q^) 1-14. 金の王手？ビットボードの初期化！" << SYNCENDL;
        g_goldAttackBb.Initialize_10a240b_checkTableGold();

        SYNCCOUT << "(^q^) 1-15. 銀の王手？ビットボードの初期化！" << SYNCENDL;
        g_silverAttackBb.initialize_10a250b_checkTableSilver();

        SYNCCOUT << "(^q^) 1-16. 桂の王手？ビットボードの初期化！" << SYNCENDL;
        g_knightAttackBb.initialize_10a260b_checkTableKnight();

        SYNCCOUT << "(^q^) 1-17. 香の王手？ビットボードの初期化！" << SYNCENDL;
        g_lanceAttackBb.initialize_10a270b_checkTableLance();

        SYNCCOUT << "(^q^) 1-18. ２点の距離初期化！" << SYNCENDL;
        UtilSquareDistance::initialize_10a280b_squareDistance(g_squareDistance);

        SYNCCOUT << "(^q^) I-19. 定跡初期化！" << SYNCENDL;
        Book::initialize_10a290b_book();

        SYNCCOUT << "(^q^) 1-20. 検索テーブル初期化！" << SYNCENDL;
        initialize_10a300b_searchTable();
    }

    SYNCCOUT << "(^q^) 2   . 局面のゾブリストハッシュ初期化！" << SYNCENDL;
    Position::initialize_10a310b_zobrist();

    SYNCCOUT << "(^q^) 2.9 . エンジン設定！" << SYNCENDL;
    MuzEngineSettingsInitializeService engineSettingsInitialize;
    engineSettingsInitialize.initialize_10a510b_engineOptions(
        Move::m_MAX_LEGAL_MOVES,
        SweetnessInfinite,
        SweetnessMate0Ply,
        g_MaxThreads,
        &this->m_pGameEngineStore->m_engineSettings,
        // onHashSizeChanged:
        [this] (auto opt)
        {
            this->m_pGameEngineStore.get()->m_tt.setSize(opt);
        },
        // onHashCleared:
        [this](auto opt)
        {
            this->m_pGameEngineStore.get()->m_tt.Clear();
        },
        // onEvalDirChanged:
        [this](auto opt)
        {
            std::unique_ptr<KkKkpKppStorage1>(new KkKkpKppStorage1)->initialize_10a600b(opt, true);
        },
        // onMaxThreadsPerSplitPointChanged:
        [this](auto opt)
        {
            this->m_pGameEngineStore.get()->m_pub.ReadUSIOptions(this->m_pGameEngineStore.get());
        },
        // onThreadsChanged:
        [this](auto opt)
        {
            this->m_pGameEngineStore.get()->m_pub.ReadUSIOptions(this->m_pGameEngineStore.get());
        },
        // getCpuCoreCount:
        [this]()
        {
            // 論理的なコア数の取得
            // todo: boost::thread::physical_concurrency() を使うこと。
            // std::thread::hardware_concurrency() は 0 を返す可能性がある。
            return std::max(static_cast<int>(std::thread::hardware_concurrency() / 2), 1);
        });

    SYNCCOUT << "(^q^) 3   . 探索部の初期化！" << SYNCENDL;
    this->m_pGameEngineStore->initialize_10a520b_search();


    // 一時オブジェクトの生成と破棄


    SYNCCOUT << "(^q^) 4   . 評価関数の初期化！" << SYNCENDL;
    std::unique_ptr<KkKkpKppStorage1>(new KkKkpKppStorage1)->initialize_10a600b(this->m_pGameEngineStore->m_engineSettings.GetOptionByKey("Eval_Dir"), true);

    SYNCCOUT << "(^q^) 次は USIループへ！" << SYNCENDL;
}


/// <summary>
/// 本体
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void MuzGameEngineService::body_50a(int argc, char* argv[])
{
    UsiLoop usiLoop;
    usiLoop.mainloop_50a500b(argc, argv, *this->m_pGameEngineStore);
}


/// <summary>
/// 事後処理
/// </summary>
void MuzGameEngineService::finalize_90000a()
{
    SYNCCOUT << "(^q^)main(6/6): threads.exit! ----> doUSICommandLoop" << SYNCENDL;
    this->m_pGameEngineStore->m_pub.exit_90a500b();
}
