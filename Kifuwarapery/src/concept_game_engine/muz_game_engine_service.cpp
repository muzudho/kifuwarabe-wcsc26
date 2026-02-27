#include "../n95a_core_library/lib_95a_cpp/muz_string_service.hpp"
#include "../n95a_core_library/lib_94a_cli/muz_cli_service.hpp"
#include "../lib_5a_gui/muz_engine_settings_initialize_service.hpp"
#include "../n95a_core_library/lib_55a_toybox_95b_hand_stand/color.hpp"
#include "../view_5a_toybox/muz_5a1b_hand_stand_view.hpp"
#include "../view_5a_toybox/muz_5a25b_board_view.hpp"
#include "../n95a_core_library/lib_55a_toybox_95b_hand_stand/muz_hand_stand_collection_service.hpp"
#include "muz_game_engine_service.hpp"

using namespace std;


// 旧版：
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../header/n161_sqDistan/n161_500_squareDistance.hpp"
#include "../../header/n163_sqDistan/n163_600_utilSquareDistance.hpp"
#include "../../header/n165_movStack/n165_400_move.hpp"
#include "../../header/n165_movStack/n165_600_convMove.hpp"
#include "../../header/n350_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n407_moveGen_/n407_800_moveGenerator200.hpp"
#include "../../header/n407_moveGen_/n407_900_moveList.hpp"
#include "../../header/n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../../header/n480_tt______/n480_300_tt.hpp"
#include "../../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../../header/n600_book____/n600_500_book.hpp"
#include "../../header/n720_usi_____/n720_260_usiOperation.hpp"
#include "../../header/n720_usi_____/n720_300_benchmark.hpp"
#include "../../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../../header/n800_learn___/n800_500_learner.hpp"
#include "../../header/n900_main____/n900_300_usiLoop.hpp"
#include "../../src/concept_game_engine/muz_game_engine_storage_model.hpp"
#include "../../src/lib_5a_bitboard/init110_silverAttackBb.hpp"
#include "../../src/lib_5a_bitboard/init120_bishopAttackBb.hpp"
#include "../../src/lib_5a_bitboard/init130_lanceAttackBb.hpp"
#include "../../src/lib_5a_bitboard/init140_goldAttackBb.hpp"
#include "../../src/lib_5a_bitboard/init150_rookAttackBb.hpp"
#include "../../src/lib_5a_bitboard/init160_kingAttackBb.hpp"
#include "../../src/lib_5a_bitboard/init180_knightAttackBb.hpp"
#include "../../src/lib_5a_bitboard/init190_pawnAttackBb.hpp"
#include "../../src/lib_5a_gui/muz_engine_settings_initialize_service.hpp"
#include "../../src/lib_5a_shogi/muz_shogi_model.hpp"
#include "../../src/lib_5a_toybox_n2/char_to_piece_usi.hpp"
#include "../../src/lib_5a_toybox_medium/muz_position_medium_model.hpp"
#include <iostream>


// ========================================
// 生成／破棄
// ========================================


/// <summary>
/// 生成
/// </summary>
MuzGameEngineService::MuzGameEngineService()
{
    this->gameEngineStore_ = std::unique_ptr<MuzGameEngineStorageModel>(new MuzGameEngineStorageModel);
}


/// <summary>
/// 破棄。
/// </summary>
MuzGameEngineService::~MuzGameEngineService()
{
    this->gameEngineStore_.reset();
}


// ========================================
// プロパティー
// ========================================


// 将棋エンジン表示名
#ifdef NDEBUG
const std::string my_name_ = "Kifuwarapery(Apery_Twig_SDT3)";
#else
const std::string my_name_ = "Kifuwarapery(Apery) Debug Build";
#endif


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
        &this->gameEngineStore_->m_engineSettings,
        // onHashSizeChanged:
        [this] (auto opt)
        {
            this->gameEngineStore_.get()->m_tt.setSize(opt);
        },
        // onHashCleared:
        [this](auto opt)
        {
            this->gameEngineStore_.get()->m_tt.Clear();
        },
        // onEvalDirChanged:
        [this](auto opt)
        {
            std::unique_ptr<KkKkpKppStorage1>(new KkKkpKppStorage1)->initialize_10a600b(opt, true);
        },
        // onMaxThreadsPerSplitPointChanged:
        [this](auto opt)
        {
            this->gameEngineStore_.get()->m_pub.ReadUSIOptions(this->gameEngineStore_.get());
        },
        // onThreadsChanged:
        [this](auto opt)
        {
            this->gameEngineStore_.get()->m_pub.ReadUSIOptions(this->gameEngineStore_.get());
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
    this->gameEngineStore_->initialize_10a520b_search();


    // 一時オブジェクトの生成と破棄


    SYNCCOUT << "(^q^) 4   . 評価関数の初期化！" << SYNCENDL;
    std::unique_ptr<KkKkpKppStorage1>(new KkKkpKppStorage1)->initialize_10a600b(this->gameEngineStore_->m_engineSettings.GetOptionByKey("Eval_Dir"), true);

    SYNCCOUT << "(^q^) 次は USIループへ！" << SYNCENDL;
}


#if !defined MINIMUL

/*
/// <summary>
///		<pre>
/// for debug
/// 指し手生成の速度を計測
///		</pre>
/// </summary>
/// <param name="pos"></param>
void measureGenerateMoves(const Position& pos) {
    pos.Print();

    MoveStack legalMoves[Move::m_MAX_LEGAL_MOVES];
    for (int i = 0; i < Move::m_MAX_LEGAL_MOVES; ++i)
    {
        legalMoves[i].m_move = g_MOVE_NONE;
    }
    MoveStack* pms = &legalMoves[0];
    const u64 num = 5000000;
    Stopwatch t = Stopwatch::CreateStopwatchByCurrentTime();
    if (pos.inCheck()) {
        for (u64 i = 0; i < num; ++i) {
            pms = &legalMoves[0];
            pms = g_moveGenerator200.GenerateMoves_2(N06_Evasion, pms, pos);
        }
    }
    else {
        for (u64 i = 0; i < num; ++i) {
            pms = &legalMoves[0];
            pms = g_moveGenerator200.GenerateMoves_2(N03_CapturePlusPro, pms, pos);
            pms = g_moveGenerator200.GenerateMoves_2(N04_NonCaptureMinusPro, pms, pos);
            pms = g_moveGenerator200.GenerateMoves_2(N02_Drop, pms, pos);
            //			pms = generateMoves<PseudoLegal>(pms, pos);
            //			pms = generateMoves<Legal>(pms, pos);
        }
    }
    const int elapsed = t.GetElapsed();
    std::cout << "elapsed = " << elapsed << " [msec]" << std::endl;
    if (elapsed != 0) {
        std::cout << "times/s = " << num * 1000 / elapsed << " [times/sec]" << std::endl;
    }
    const ptrdiff_t count = pms - &legalMoves[0];
    std::cout << "num of moves = " << count << std::endl;
    for (int i = 0; i < count; ++i) {
        std::cout << legalMoves[i].m_move.ToCSA() << ", ";
    }
    std::cout << std::endl;
}
*/

#endif


/// <summary>
/// 本体
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void MuzGameEngineService::main_loop_50a(int argc, char* argv[])
{
    // テスト：駒台の初期化
    // TODO: これらの変数は、ポジションに移動したい（＾～＾）
    this->gameEngineStore_->black_hand_stand_.set_count(HRook, 0);
    this->gameEngineStore_->black_hand_stand_.set_count(HBishop, 1);
    this->gameEngineStore_->black_hand_stand_.set_count(HGold, 0);
    this->gameEngineStore_->black_hand_stand_.set_count(HSilver, 4);
    this->gameEngineStore_->black_hand_stand_.set_count(HKnight, 3);
    this->gameEngineStore_->black_hand_stand_.set_count(HLance, 1);
    this->gameEngineStore_->black_hand_stand_.set_count(HPawn, 2);   // とりあえず歩を２枚持ってることにするぜ（＾ｑ＾）

    this->gameEngineStore_->white_hand_stand_.set_count(HRook, 2);
    this->gameEngineStore_->white_hand_stand_.set_count(HBishop, 0);
    this->gameEngineStore_->white_hand_stand_.set_count(HGold, 1);
    this->gameEngineStore_->white_hand_stand_.set_count(HSilver, 0);
    this->gameEngineStore_->white_hand_stand_.set_count(HKnight, 1);
    this->gameEngineStore_->white_hand_stand_.set_count(HLance, 0);
    this->gameEngineStore_->white_hand_stand_.set_count(HPawn, 3);   // とりあえず歩を３枚持ってることにするぜ（＾ｑ＾）

    // テスト：盤の初期化
    // TODO: これらの変数は、ポジションに移動したい（＾～＾）
    this->gameEngineStore_->board_.set_piece(M91, WLance);
    this->gameEngineStore_->board_.set_piece(M81, WKnight);
    this->gameEngineStore_->board_.set_piece(M71, WSilver);
    this->gameEngineStore_->board_.set_piece(M61, WGold);
    this->gameEngineStore_->board_.set_piece(M51, WKing);
    this->gameEngineStore_->board_.set_piece(M41, WGold);
    this->gameEngineStore_->board_.set_piece(M31, WSilver);
    this->gameEngineStore_->board_.set_piece(M21, WKnight);
    this->gameEngineStore_->board_.set_piece(M11, WLance);
    this->gameEngineStore_->board_.set_piece(M82, WRook);
    this->gameEngineStore_->board_.set_piece(M22, WBishop);
    this->gameEngineStore_->board_.set_piece(M93, WPawn);
    this->gameEngineStore_->board_.set_piece(M83, WPawn);
    this->gameEngineStore_->board_.set_piece(M73, WPawn);
    this->gameEngineStore_->board_.set_piece(M63, WPawn);
    this->gameEngineStore_->board_.set_piece(M53, WPawn);
    this->gameEngineStore_->board_.set_piece(M43, WPawn);
    this->gameEngineStore_->board_.set_piece(M33, WPawn);
    this->gameEngineStore_->board_.set_piece(M23, WPawn);
    this->gameEngineStore_->board_.set_piece(M13, WPawn);
    this->gameEngineStore_->board_.set_piece(M97, BPawn);
    this->gameEngineStore_->board_.set_piece(M87, BPawn);
    this->gameEngineStore_->board_.set_piece(M77, BPawn);
    this->gameEngineStore_->board_.set_piece(M67, BPawn);
    this->gameEngineStore_->board_.set_piece(M57, BPawn);
    this->gameEngineStore_->board_.set_piece(M47, BPawn);
    this->gameEngineStore_->board_.set_piece(M37, BPawn);
    this->gameEngineStore_->board_.set_piece(M27, BPawn);
    this->gameEngineStore_->board_.set_piece(M17, BPawn);
    this->gameEngineStore_->board_.set_piece(M88, BBishop);
    this->gameEngineStore_->board_.set_piece(M28, BRook);
    this->gameEngineStore_->board_.set_piece(M99, BLance);
    this->gameEngineStore_->board_.set_piece(M89, BKnight);
    this->gameEngineStore_->board_.set_piece(M79, BSilver);
    this->gameEngineStore_->board_.set_piece(M69, BGold);
    this->gameEngineStore_->board_.set_piece(M59, BKing);
    this->gameEngineStore_->board_.set_piece(M49, BGold);
    this->gameEngineStore_->board_.set_piece(M39, BSilver);
    this->gameEngineStore_->board_.set_piece(M29, BKnight);
    this->gameEngineStore_->board_.set_piece(M19, BLance);

    MuzCliService cliSvc;

    // TODO: ここで実際のコマンド処理を書く
    cliSvc.set_process_command_line([this](const std::string& line)
        {
            if (!this->gameEngineStore_->is_usi()) {
                std::cout << "処理するよ: " << line << "\n";
            }

            MuzStringService stringSvc;
            std::vector<std::string> tokens;

            // 半角スペース ' ' で分割
            tokens = stringSvc.split_command_line(line);


            MuzCliResultModel result;

            // ポンダー（相手の手番に思考すること）してるのを止めるか
            bool shall_stop_ponder = false;

            // TODO: 対局中に呼び出される回数が多いものを先にした方がいいかだぜ（＾～＾）？
            // 例: 終了したいなら
            if (line == "quit")
            {
                // ここで何かフラグを立てて main_loop から抜けるようにする
                // または throw とか exit(0) でもいいけど、できれば綺麗に抜けたい
                result.request_quit();

                // 終了時にポンダーヒットが来ることがあるので、対処してください。
                shall_stop_ponder = true;   // ポンダーしてようと、してなかろうと、止めたらいい。
            }
            else if (line == "usi")
            {
                this->gameEngineStore_->set_usi();

                // USIプロトコルのバージョンを返す。
                std::cout << "id name " << my_name_ << "\nid author (Derivation)Takahashi Satoshi (Base)Hiraoka Takuya\nusiok" << "\n";

                // TODO: セット・オプション付けてください： std::cout << "id name " << my_name_ << "\nid author (Derivation)Takahashi Satoshi (Base)Hiraoka Takuya\n" << gameEngineStore_.m_engineSettings << "\nusiok" << "\n";
            }
            else if (line == "isready")
            {
                // エンジンが準備できたら、"readyok" を返す。
                std::cout << "readyok" << "\n";
            }
            else if (line == "setoption")
            {
                // TODO: エンジンのオプションを設定するコマンド。これが来たら、オプションを変更する。
                //gameEngineStore_.SetOption(ssCmd);
            }
            else if (line == "usinewgame")
            {
                //                // 新しいゲームの開始を知らせるコマンド。これが来たら、前のゲームの情報をクリアする。
                //                gameEngineStore_.m_tt.Clear();
                //
                //#if defined INANIWA_SHIFT
                //                inaniwaFlag = NotInaniwa;
                //#endif
                //#if defined BISHOP_IN_DANGER
                //                bishopInDangerFlag = NotBishopInDanger;
                //#endif
                //
                //                // 最初は乱数に偏りがあるかも。少し回しておく。
                //                for (int i = 0; i < 100; ++i)
                //                {
                //                    g_randomTimeSeed();
                //                }
            }
            else if (line == "position")
            {
                // TODO: 局面を設定するコマンド。これが来たら、局面を変更する。
                //usiOperation.SetPosition(pos, ssCmd);
            }
            else if (tokens[0] == "go")
            {
                //// TODO: 思考開始のコマンド。これが来たら、思考を開始する。
                //usiOperation.Go(gameStats, pos, ssCmd);

                std::cout << "bestmove resign" << "\n";  // とりあえず投了を返すぜ（＾ｑ＾）
            }
            // ----------------------------------------
            // 以下、独自実装
            // ----------------------------------------
            // 先手駒台の描画
            else if (tokens[0] == "handb")
            {
                MuzHandStandView::print_black(this->gameEngineStore_->black_hand_stand_);
            }
            // 後手駒台の描画
            else if (tokens[0] == "handw")
            {
                MuzHandStandView::print_white(this->gameEngineStore_->white_hand_stand_);
            }
            // 駒台のセット
            //      - `handset 2PR`
            else if (tokens[0] == "handset")
            {
                MuzHandStandCollectionService handStandCollectionSvc;
                handStandCollectionSvc.parse_hand_stand_collection(
                    tokens[1],
                    this->gameEngineStore_->black_hand_stand_,
                    this->gameEngineStore_->white_hand_stand_);
            }
            // 盤だけの描画（駒台を除く）
            else if (tokens[0] == "boardonly")
            {
                MuzBoardView::print(this->gameEngineStore_->get_board());
            }
            else
            {
                std::cout << "そんなコマンド無い（＾～＾）\n";
            }

            if (shall_stop_ponder)
            {
                // TODO: ポンダーを止める処理をここに書いてください。
            }

            return result;
        });

    // メインループを走らせます。
    cliSvc.main_loop(argc, argv);
}


/// <summary>
/// 事後処理
/// </summary>
void MuzGameEngineService::finalize_90a()
{
    SYNCCOUT << "(^q^)main(6/6): threads.exit! ----> doUSICommandLoop" << SYNCENDL;
    this->gameEngineStore_->m_pub.exit_90a500b();
}
