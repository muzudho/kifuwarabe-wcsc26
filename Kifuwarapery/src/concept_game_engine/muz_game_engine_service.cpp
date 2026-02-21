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
#include "muz_game_engine_service.hpp"
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
// プロパティー
// ========================================


// 将棋エンジン表示名
#ifdef NDEBUG
const std::string MyName = "Kifuwarapery(Apery_Twig_SDT3)";
#else
const std::string MyName = "Kifuwarapery(Apery) Debug Build";
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
    // ========================================
    // 新版
    // ========================================


    MuzCliService cliSvc;

    cliSvc.set_process_command([](const std::string& cmd)
        {
            // TODO: ここで実際のコマンド処理を書く
            std::cout << "処理したよ: " << cmd << "\n";

            MuzCliResultModel result;

            // ポンダー（相手の手番に思考すること）してるのを止めるか
            bool shall_stop_ponder = false;

            // 例: 終了したいなら
            if (cmd == "quit")
            {
                // ここで何かフラグを立てて main_loop から抜けるようにする
                // または throw とか exit(0) でもいいけど、できれば綺麗に抜けたい
                result.request_quit();
                
                // 終了時にポンダーヒットが来ることがあるので、対処してください。
                shall_stop_ponder = true;   // ポンダーしてようと、してなかろうと、止めたらいい。
            }

            if (shall_stop_ponder)
            {
                // TODO: ポンダーを止める処理をここに書いてください。
            }

            return result;
        });

    // メインループを走らせます。
    cliSvc.main_loop(argc, argv);


    // ========================================
    // 旧版
    // ========================================

    
    MuzGameEngineStorageModel& m_pGameEngineStore = *this->m_pGameEngineStore;

    GameStats gameStats{};	// こう書くと関数呼出しと思われてエラー： GameStats gameStats();
    Position pos(g_SFEN_STARTPOS_STR, m_pGameEngineStore.m_pub.GetFirstCaptain(), &m_pGameEngineStore);

    std::string line;
    std::string token;

#if defined MPI_LEARN
    boost::mpi::environment  env(argc, argv);
    boost::mpi::communicator world;
    if (world.m_rank() != 0) {
        learn(GetPos, env, world);
        return;
    }
#endif

    // コマンドライン引数（があれば）を結合して１つの文字列として扱う。
    for (int i = 1; i < argc; ++i)
    {
        // 末尾に半角空白が残るけど、まあいいか。
        line += std::string(argv[i]) + " ";
    }

    do {
        if (argc == 1)
        {
            // コマンドライン引数がないときは、標準入力からコマンドを１行読み取る。改行は読み取らない。
            std::getline(std::cin, line);
        }

        // コマンドを空白で区切って、最初のトークンを取り出す。
        std::istringstream ssCmd(line);

        // 最初のトークンを読み取る。
        ssCmd >> std::skipws >> token;

        UsiOperation usiOperation;
        
        // ポンダーしてるのを止めるか
        bool shall_stop_ponder = false;

        if (
            token == "quit" ||
            token == "stop" ||
            token == "ponderhit" ||
            token == "gameover"
            ) {
            // 終了時にポンダーヒットが来ることがある。
            
            if (token == "ponderhit" &&
                !m_pGameEngineStore.m_signals.m_stopOnPonderHit)
            {
                // 相手の思考時間中に自分も思考するのを止める。
                m_pGameEngineStore.m_limits.m_canPonder = false;
            }
            else
            {
                shall_stop_ponder = true;
            }
            
            // ポンダーヒットのときに、ムーブタイムが０でなければ、消費した時間分、加算する。
            if (token == "ponderhit" && m_pGameEngineStore.m_limits.GetMoveTime() != 0) {
                m_pGameEngineStore.m_limits.IncreaseMoveTime(m_pGameEngineStore.m_stopwatch.GetElapsed());
            }
        }
        else if (token == "usinewgame")
        {
            // 新しいゲームの開始を知らせるコマンド。これが来たら、前のゲームの情報をクリアする。
            m_pGameEngineStore.m_tt.Clear();

#if defined INANIWA_SHIFT
            inaniwaFlag = NotInaniwa;
#endif
#if defined BISHOP_IN_DANGER
            bishopInDangerFlag = NotBishopInDanger;
#endif

            // 最初は乱数に偏りがあるかも。少し回しておく。
            for (int i = 0; i < 100; ++i)
            {
                g_randomTimeSeed();
            }
        }
        else if (token == "usi")
        {
            // USIプロトコルのバージョンを返す。
            SYNCCOUT << "id name " << MyName << "\nid author (Derivation)Takahashi Satoshi (Base)Hiraoka Takuya\n" << m_pGameEngineStore.m_engineSettings << "\nusiok" << SYNCENDL;
        }
        else if (token == "go")
        {
            // 思考開始のコマンド。これが来たら、思考を開始する。
            usiOperation.Go(gameStats, pos, ssCmd);
        }
        else if (token == "isready")
        {
            // エンジンが準備できたら、"readyok" を返す。
            SYNCCOUT << "readyok" << SYNCENDL;
        }
        else if (token == "position")
        {
            // 局面を設定するコマンド。これが来たら、局面を変更する。
            usiOperation.SetPosition(pos, ssCmd);
        }
        else if (token == "setoption")
        {
            // エンジンのオプションを設定するコマンド。これが来たら、オプションを変更する。
            m_pGameEngineStore.SetOption(ssCmd);
        }

#if defined LEARN
        else if (token == "l") {
            auto learner = std::unique_ptr<Learner>(new Learner);
#if defined MPI_LEARN
            learner->learn(GetPos, env, world);
#else
            learner->learn(GetPos, ssCmd);
#endif
        }
#endif

#if !defined MINIMUL
        // 以下、デバッグ用
        else if (token == "bench") { Benchmark(gameStats, pos); }
        else if (token == "d") { pos.Print(); }
        else if (token == "s") { measureGenerateMoves(pos); }
        else if (token == "t") {
            std::cout <<
                (
                    pos.GetTurn() == Color::Black
                    ?
                    pos.GetMateMoveIn1Ply<Color::Black, Color::White>().ToCSA()
                    :
                    pos.GetMateMoveIn1Ply<Color::White, Color::Black>().ToCSA()
                    )
                << std::endl;
        }
        else if (token == "b") { MakeBook(gameStats, pos, ssCmd); }
#endif

        // 上記以外のコマンドは、"unknown command: " と表示する。
        else { SYNCCOUT << "unknown command: " << line << SYNCENDL; }

                
        if (shall_stop_ponder)
        {
            // 思考停止シグナルを立てる。
            m_pGameEngineStore.m_signals.m_stop = true;

            // 排他的処理の何か？？
            m_pGameEngineStore.m_pub.GetFirstCaptain()->NotifyOne();
        }

        // コマンドライン引数があるときは、ループせずに１回だけコマンドを処理する。
    } while (token != "quit" && argc == 1);

    //────────────────────────────────────────────────────────────────────────────────

    // 評価値ファイルを書き出す指定なら
    if (m_pGameEngineStore.m_engineSettings.GetOptionByKey("Write_Synthesized_Eval"))
    {
        // シンセサイズド評価を書き出します。
        KkKkpKppStorage1::WriteSynthesized(m_pGameEngineStore.m_engineSettings.GetOptionByKey("Eval_Dir"));
    }

    //────────────────────────────────────────────────────────────────────────────────

    m_pGameEngineStore.m_pub.WaitForThinkFinished();
}


/// <summary>
/// 事後処理
/// </summary>
void MuzGameEngineService::finalize_90000a()
{
    SYNCCOUT << "(^q^)main(6/6): threads.exit! ----> doUSICommandLoop" << SYNCENDL;
    this->m_pGameEngineStore->m_pub.exit_90a500b();
}
