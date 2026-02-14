#include "muz_engine_option_button_model.hpp"
#include "muz_engine_option_checkbox_model.hpp"
#include "muz_engine_option_spinbox_model.hpp"
#include "muz_engine_option_textbox_model.hpp"
#include "muz_engine_settings_initialize_service.hpp"


/// <summary>
/// USIエンジン・オプションに既定値を入れるぜ☆
/// </summary>
/// <param name="pMap"></param>
/// <param name="pRucksack"></param>
void MuzEngineSettingsInitializeService::initialize_10a510b_engineOptions(
	int max_legal_moves,
	int sweetnessInfinite,
	int sweetnessMate0Ply,
	int maxThreads,
	MuzEngineSettingsModel* pMap,
	std::function<void(const IMuzEngineOptionableModel&)> onHashSizeChanged,
	std::function<void(const IMuzEngineOptionableModel&)> onHashCleared,
	std::function<void(const IMuzEngineOptionableModel&)> onEvalDirChanged,
	std::function<void(const IMuzEngineOptionableModel&)> onMaxThreadsPerSplitPointChanged,
	std::function<void(const IMuzEngineOptionableModel&)> onThreadsChanged,
	std::function<int()> getCPUCoreCount)
{
	// ハッシュサイズ
	pMap->Put("USI_Hash"					, MuzEngineOptionSpinboxModel(256, 1, 65536, onHashSizeChanged));

	// ［ハッシュ・クリアー］ボタン
	pMap->Put("Clear_Hash"					, MuzEngineOptionButtonModel(onHashCleared));

	// 定跡ファイルパス
	pMap->Put("Book_File"					, MuzEngineOptionTextboxModel("book/20150503/book.bin"));

	// ［定跡］チェックボックス
	pMap->Put("Best_Book_Move"				, MuzEngineOptionCheckboxModel(false));

	// ［定跡］チェックボックス
	pMap->Put("OwnBook"						, MuzEngineOptionCheckboxModel(true));

	// 定跡の最小手数
	pMap->Put("Min_Book_Ply"				, MuzEngineOptionSpinboxModel(SHRT_MAX, 0, SHRT_MAX));

	// 定跡の最大手数
	pMap->Put("Max_Book_Ply"				, MuzEngineOptionSpinboxModel(SHRT_MAX, 0, SHRT_MAX));

	// 定跡評価値
	pMap->Put("Min_Book_Score"				, MuzEngineOptionSpinboxModel(-180, -sweetnessInfinite, sweetnessInfinite));

	// ［評価値ファイル］フォルダー
	pMap->Put("Eval_Dir"					, MuzEngineOptionTextboxModel("20151105", onEvalDirChanged));

	// ［評価値書き込み］チェックボックス
	pMap->Put("Write_Synthesized_Eval"		, MuzEngineOptionCheckboxModel(false));

	// ［相手の手番に考えるか］チェックボックス
	pMap->Put("USI_Ponder"					, MuzEngineOptionCheckboxModel(true));

	// ［秒読みマージン］ - 元の値：0.5秒☆？（＾ｑ＾）
	pMap->Put("Byoyomi_Margin"				, MuzEngineOptionSpinboxModel(500, 0, INT_MAX));

	// ［几帳面な読み］の本数
	pMap->Put("MultiPV"						, MuzEngineOptionSpinboxModel(1, 1, max_legal_moves));

	// ［コンピューターの強さ］。遊び用
	pMap->Put("Skill_Level"					, MuzEngineOptionSpinboxModel(20, 0, 20));

	// ［最大ランダム評価値差］
	pMap->Put("Max_Random_Score_Diff"		, MuzEngineOptionSpinboxModel(0, 0, sweetnessMate0Ply));

	// ［最大ランダム評価値差の手数］
	pMap->Put("Max_Random_Score_Diff_Ply"	, MuzEngineOptionSpinboxModel(40, 0, SHRT_MAX));

	//────────────────────────────────────────────────────────────────────────────────
	// 時間制御関連☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	pMap->Put("Emergency_Move_Horizon"		, MuzEngineOptionSpinboxModel(40, 0, 50));
	//pMap->Put("Emergency_Base_Time"			, MuzEngineOptionSpinboxModel(   200,  0, 30000));	// 緊急時用に残しておこうというタイム（ミリ秒）か☆？
	//pMap->Put("Emergency_Move_Time"			, MuzEngineOptionSpinboxModel(    70,  0,  5000));	// 緊急時用に残しておこうというタイム（ミリ秒）か☆？
	//pMap->Put("Slow_Mover"					, MuzEngineOptionSpinboxModel(   100, 10,  1000));//スロー・ムーバーとは何なのか☆？（＾ｑ＾）？
//#if defined(FISCHER_RULE)
//	pMap->Put("Minimum_Thinking_Time"		, MuzEngineOptionSpinboxModel(  9000,  0, INT_MAX));// 10秒加算されると見越して、9秒は最低使えるということにしようぜ☆（＾ｑ＾）
//#else
	pMap->Put("Minimum_Thinking_Time", MuzEngineOptionSpinboxModel(1500, 0, INT_MAX));// 元の値：初期値 1500（1.5）秒☆
//#endif

	//────────────────────────────────────────────────────────────────────────────────
	//
	//────────────────────────────────────────────────────────────────────────────────

	// ［一緒に走る猿が分岐する点の最大数］
	pMap->Put("Max_Threads_per_Split_Point"	, MuzEngineOptionSpinboxModel(		5,  4,     8, onMaxThreadsPerSplitPointChanged));

	// スレッド数
	pMap->Put("Threads"						, MuzEngineOptionSpinboxModel(getCPUCoreCount(), 1, maxThreads, onThreadsChanged));

	// ［寝てる猿を使う］チェックボックス
	pMap->Put("Use_Sleeping_Threads"		, MuzEngineOptionCheckboxModel(false));

#if defined BISHOP_IN_DANGER
	(*this)["Danger_Demerit_Score"] = MuzEngineOptionModel(700, SHRT_MIN, SHRT_MAX);
#endif
}
