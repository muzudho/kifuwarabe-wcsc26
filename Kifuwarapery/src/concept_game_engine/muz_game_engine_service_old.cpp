#include "muz_game_engine_service_old.hpp"
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


void MuzGameEngineServiceOld::main_loop_50a(int argc, char* argv[])
{
    MuzGameEngineStorageModel& gameEngineStore_ = *this->gameEngineStore_;

    GameStats gameStats{};	// こう書くと関数呼出しと思われてエラー： GameStats gameStats();
    Position pos(g_SFEN_STARTPOS_STR, gameEngineStore_.m_pub.GetFirstCaptain(), &gameEngineStore_);

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
            token == "stop" ||
            token == "ponderhit" ||
            token == "gameover"
            ) {
            // 終了時にポンダーヒットが来ることがある。

            if (token == "ponderhit" &&
                !gameEngineStore_.m_signals.m_stopOnPonderHit)
            {
                // 相手の思考時間中に自分も思考するのを止める。
                gameEngineStore_.m_limits.m_canPonder = false;
            }
            else
            {
                shall_stop_ponder = true;
            }

            // ポンダーヒットのときに、ムーブタイムが０でなければ、消費した時間分、加算する。
            if (token == "ponderhit" && gameEngineStore_.m_limits.GetMoveTime() != 0) {
                gameEngineStore_.m_limits.IncreaseMoveTime(gameEngineStore_.m_stopwatch.GetElapsed());
            }
        }
        else if (token == "usi")
        {
            // USIプロトコルのバージョンを返す。
            SYNCCOUT << "id name " << MyName << "\nid author (Derivation)Takahashi Satoshi (Base)Hiraoka Takuya\n" << gameEngineStore_.m_engineSettings << "\nusiok" << SYNCENDL;
        }
        else if (token == "setoption")
        {
            // エンジンのオプションを設定するコマンド。これが来たら、オプションを変更する。
            gameEngineStore_.SetOption(ssCmd);
        }
        else if (token == "usinewgame")
        {
            // 新しいゲームの開始を知らせるコマンド。これが来たら、前のゲームの情報をクリアする。
            gameEngineStore_.m_tt.Clear();

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
        else if (token == "position")
        {
            // 局面を設定するコマンド。これが来たら、局面を変更する。
            usiOperation.SetPosition(pos, ssCmd);
        }
        else if (token == "go")
        {
            // 思考開始のコマンド。これが来たら、思考を開始する。
            usiOperation.Go(gameStats, pos, ssCmd);
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
            gameEngineStore_.m_signals.m_stop = true;

            // 排他的処理の何か？？
            gameEngineStore_.m_pub.GetFirstCaptain()->NotifyOne();
        }

        // コマンドライン引数があるときは、ループせずに１回だけコマンドを処理する。
    } while (token != "quit" && argc == 1);

    //────────────────────────────────────────────────────────────────────────────────

    // 評価値ファイルを書き出す指定なら
    if (gameEngineStore_.m_engineSettings.GetOptionByKey("Write_Synthesized_Eval"))
    {
        // シンセサイズド評価を書き出します。
        KkKkpKppStorage1::WriteSynthesized(gameEngineStore_.m_engineSettings.GetOptionByKey("Eval_Dir"));
    }

    //────────────────────────────────────────────────────────────────────────────────

    gameEngineStore_.m_pub.WaitForThinkFinished();
}