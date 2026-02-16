#include <iostream>
#include "../../header/n165_movStack/n165_400_move.hpp"
#include "../../header/n165_movStack/n165_600_convMove.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n350_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n407_moveGen_/n407_800_moveGenerator200.hpp"
#include "../../header/n407_moveGen_/n407_900_moveList.hpp"
#include "../../header/n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../../header/n480_tt______/n480_300_tt.hpp"
#include "../../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../../header/n600_book____/n600_500_book.hpp"
//#include "../../src/lib_gui/engine_option_collection.hpp"
//#include "../../src/lib_gui/engine_option.hpp"
#include "../../header/n720_usi_____/n720_260_usiOperation.hpp"
#include "../../header/n720_usi_____/n720_300_benchmark.hpp"
#include "../../header/n800_learn___/n800_500_learner.hpp"
#include "../../src/concept_game_engine/muz_game_engine_storage_model.hpp"
#include "..\..\header\n900_main____\n900_300_usiLoop.hpp"
#include "../../src/lib_shogi/muz_shogi_model.hpp"


#if !defined MINIMUL


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
			pms = g_moveGenerator200.GenerateMoves_2(N06_Evasion,pms, pos);
		}
	}
	else {
		for (u64 i = 0; i < num; ++i) {
			pms = &legalMoves[0];
			pms = g_moveGenerator200.GenerateMoves_2(N03_CapturePlusPro,pms, pos);
			pms = g_moveGenerator200.GenerateMoves_2(N04_NonCaptureMinusPro,pms, pos);
			pms = g_moveGenerator200.GenerateMoves_2(N02_Drop,pms, pos);
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
#endif


// 将棋エンジン表示名
#ifdef NDEBUG
const std::string MyName = "Kifuwarapery(Apery_Twig_SDT3)";
#else
const std::string MyName = "Kifuwarapery(Apery) Debug Build";
#endif


/// <summary>
/// 生成。
/// </summary>
UsiLoop::UsiLoop()
{
}


/// <summary>
/// メインループ。
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <param name="m_pGameEngineStore"></param>
void UsiLoop::mainloop_50a500b(int argc, char* argv[], MuzGameEngineStorageModel& m_pGameEngineStore)
{
	GameStats gameStats{};	// こう書くと関数呼出しと思われてエラー： GameStats gameStats();
	Position pos(g_SFEN_STARTPOS_STR, m_pGameEngineStore.m_pub.GetFirstCaptain(), &m_pGameEngineStore);

	std::string cmd;
	std::string token;

#if defined MPI_LEARN
	boost::mpi::environment  env(argc, argv);
	boost::mpi::communicator world;
	if (world.m_rank() != 0) {
		learn(GetPos, env, world);
		return;
	}
#endif

    // コマンドライン引数を結合して１つの文字列として扱う。
	for (int i = 1; i < argc; ++i)
	{
		cmd += std::string(argv[i]) + " ";
	}

	do {
		if (argc == 1)
		{
            // コマンドライン引数がないときは、標準入力からコマンドを読み取る。
			std::getline(std::cin, cmd);
		}

        // コマンドを空白で区切って、最初のトークンを取り出す。
		std::istringstream ssCmd(cmd);

        // 最初のトークンを読み取る。
		ssCmd >> std::skipws >> token;

		UsiOperation usiOperation;

		if (
			token == "quit" ||
			token == "stop" ||
			token == "ponderhit" ||
			token == "gameover"
		) {
			// 終了時にポンダーヒットが来ることがある。
			if (token != "ponderhit" ||
				m_pGameEngineStore.m_signals.m_stopOnPonderHit
			) {
                // 思考停止シグナルを立てる。
				m_pGameEngineStore.m_signals.m_stop = true;

				// 排他的処理の何か？？
				m_pGameEngineStore.m_pub.GetFirstCaptain()->NotifyOne();
			}
			else {
				// 相手の思考時間中に自分も思考するのを止める。
				m_pGameEngineStore.m_limits.m_canPonder = false;
			}

            // ポンダーヒットのときに、ムーブタイムが０でなければ、消費した時間分、加算する。
			if (token == "ponderhit" && m_pGameEngineStore.m_limits.GetMoveTime() != 0) {
				m_pGameEngineStore.m_limits.IncreaseMoveTime( m_pGameEngineStore.m_stopwatch.GetElapsed());
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
		else if (token == "t") { std::cout <<
			(
				pos.GetTurn()==Color::Black
				?
				pos.GetMateMoveIn1Ply<Color::Black,Color::White>().ToCSA()
				:
				pos.GetMateMoveIn1Ply<Color::White,Color::Black>().ToCSA()
			)			
			<< std::endl; }
		else if (token == "b") { MakeBook(gameStats, pos, ssCmd); }
#endif

        // 上記以外のコマンドは、"unknown command: " と表示する。
		else { SYNCCOUT << "unknown command: " << cmd << SYNCENDL; }

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
