#include "../../header/n165_movStack/n165_400_move.hpp"
#include "../../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../../src/lib_gui/muz_engine_optoins_initialize_service.hpp"
#include "../../src/lib_gui/engine_option.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"


/// <summary>
/// USIエンジン・オプションに既定値を入れるぜ☆
/// </summary>
/// <param name="pMap"></param>
/// <param name="pRucksack"></param>
void MuzEngineOptionsInitializeService::initialize_10a510b_engineOptions(
	EngineOptionCollection* pMap,
	MuzGameEngineStorageModel* pRucksack,
	std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> handleHashSizeChanged,
	std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> handleHashCleared,
	std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> handleEvalDirChanged,
	std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> handleMaxThreadsPerSplitPointChanged,
	std::function<void(MuzGameEngineStorageModel*, const EngineOptionable&)> handleThreadsChanged,
	EngineOptionable::FnVoidInt* pGetCpuCoreCount)
{
	// ハッシュサイズ
	pMap->Put("USI_Hash"					, EngineOption(256, 1, 65536, handleHashSizeChanged, pRucksack));

	// ［ハッシュ・クリアー］ボタン
	pMap->Put("Clear_Hash"					, EngineOption(handleHashCleared, pRucksack));

	// 定跡ファイルパス
	pMap->Put("Book_File"					, EngineOption("book/20150503/book.bin"));

	// ［定跡］チェックボックス
	pMap->Put("Best_Book_Move"				, EngineOption(false));

	// ［定跡］チェックボックス
	pMap->Put("OwnBook"						, EngineOption(true));

	// 定跡の最小手数
	pMap->Put("Min_Book_Ply"				, EngineOption(SHRT_MAX, 0, SHRT_MAX));

	// 定跡の最大手数
	pMap->Put("Max_Book_Ply"				, EngineOption(SHRT_MAX, 0, SHRT_MAX));

	// 定跡評価値
	pMap->Put("Min_Book_Score"				, EngineOption(-180, -SweetnessInfinite, SweetnessInfinite));

	// ［評価値ファイル］フォルダー
	pMap->Put("Eval_Dir"					, EngineOption("20151105", handleEvalDirChanged));

	// ［評価値書き込み］チェックボックス
	pMap->Put("Write_Synthesized_Eval"		, EngineOption(false));

	// ［相手の手番に考えるか］チェックボックス
	pMap->Put("USI_Ponder"					, EngineOption(true));

	// ［秒読みマージン］ - 元の値：0.5秒☆？（＾ｑ＾）
	pMap->Put("Byoyomi_Margin"				, EngineOption(500, 0, INT_MAX));

	// ［几帳面な読み］の本数
	pMap->Put("MultiPV"						, EngineOption(1, 1, Move::m_MAX_LEGAL_MOVES));

	// ［コンピューターの強さ］。遊び用
	pMap->Put("Skill_Level"					, EngineOption(20, 0, 20));

	// ［最大ランダム評価値差］
	pMap->Put("Max_Random_Score_Diff"		, EngineOption(0, 0, SweetnessMate0Ply));

	// ［最大ランダム評価値差の手数］
	pMap->Put("Max_Random_Score_Diff_Ply"	, EngineOption(40, 0, SHRT_MAX));

	//────────────────────────────────────────────────────────────────────────────────
	// 時間制御関連☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	pMap->Put("Emergency_Move_Horizon"		, EngineOption(40, 0, 50));
	//pMap->Put("Emergency_Base_Time"			, EngineOption(   200,  0, 30000));	// 緊急時用に残しておこうというタイム（ミリ秒）か☆？
	//pMap->Put("Emergency_Move_Time"			, EngineOption(    70,  0,  5000));	// 緊急時用に残しておこうというタイム（ミリ秒）か☆？
	//pMap->Put("Slow_Mover"					, EngineOption(   100, 10,  1000));//スロー・ムーバーとは何なのか☆？（＾ｑ＾）？
//#if defined(FISCHER_RULE)
//	pMap->Put("Minimum_Thinking_Time"		, EngineOption(  9000,  0, INT_MAX));// 10秒加算されると見越して、9秒は最低使えるということにしようぜ☆（＾ｑ＾）
//#else
	pMap->Put("Minimum_Thinking_Time", EngineOption(1500, 0, INT_MAX));// 元の値：初期値 1500（1.5）秒☆
//#endif

	//────────────────────────────────────────────────────────────────────────────────
	//
	//────────────────────────────────────────────────────────────────────────────────

	// ［一緒に走る猿が分岐する点の最大数］
	pMap->Put("Max_Threads_per_Split_Point"	, EngineOption(		5,  4,     8, handleMaxThreadsPerSplitPointChanged, pRucksack));

	// スレッド数
	pMap->Put("Threads"						, EngineOption((*pGetCpuCoreCount)(), 1, g_MaxThreads, handleThreadsChanged, pRucksack));

	// ［寝てる猿を使う］チェックボックス
	pMap->Put("Use_Sleeping_Threads"		, EngineOption(false));

#if defined BISHOP_IN_DANGER
	(*this)["Danger_Demerit_Score"] = EngineOption(700, SHRT_MIN, SHRT_MAX);
#endif
}
