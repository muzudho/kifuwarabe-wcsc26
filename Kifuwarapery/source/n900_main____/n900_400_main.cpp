#include <iostream>
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../header/n130_100_boardBb_/n160_100_bitboard.hpp"
#include "../../header/n130_100_boardBb_/n160_110_silverAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_120_bishopAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_130_lanceAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_140_goldAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_150_rookAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_160_kingAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_180_knightAttackBb.hpp"
#include "../../header/n130_100_boardBb_/n160_190_pawnAttackBb.hpp"
#include "../../header/n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../../header/n105_240_initTwoSquaresDistanceKind/n105_240_500_twoSquaresDistanceKindInitializer.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n480_tt______/n480_300_tt.hpp"
#include "../../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../../header/n600_book____/n600_500_book.hpp"
#include "../../header/n760_thread__/n760_400_MonkiesPub.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"
#include "..\..\header\n900_app_____/n900_300_usiLoop.hpp"
#include "..\..\header\n900_app_____\n900_400_app10.hpp"


/// <summary>
/// 生成。
/// </summary>
App10::App10()
{
	this->searcher = std::unique_ptr<OurCarriage>(new OurCarriage);
}


/// <summary>
/// 破棄。
/// </summary>
App10::~App10()
{
	this->searcher.reset();
}


/// <summary>
/// 最初の設定（初期化）。
/// </summary>
void App10::initialize_10a()
{
	//────────────────────────────────────────────────────────────────────────────────
	// ビットボードとテーブルの初期化☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	{
		SYNCCOUT << "(^q^) 1   . ビットボードとテーブルを初期化するぜ！" << SYNCENDL;

#ifndef SKIP_LONG_TIME_EVAL
		// 長い時間が掛かる初期化処理をするか？
		SYNCCOUT << "(^q^) 1- 1. 飛の利きビットボードの初期化！" << SYNCENDL;
		g_rookAttackBb.initialize_10a100b_rookAttacks_();
#endif

		SYNCCOUT << "(^q^) 1- 2. 角の利きビットボードの初期化！" << SYNCENDL;
		g_bishopAttackBb.initialize_10a120b_bishopAttacks_();

		SYNCCOUT << "(^q^) 1- 3. 玉の利きビットボードの初期化！" << SYNCENDL;
		g_kingAttackBb.initialize_10a140b_kingAttacks_();

		SYNCCOUT << "(^q^) 1- 4. 金の利きビットボードの初期化！" << SYNCENDL;
		g_goldAttackBb.initialize_10a160b_goldAttacks_();

		SYNCCOUT << "(^q^) 1- 5. 銀の利きビットボードの初期化！" << SYNCENDL;
		g_silverAttackBb.initialize_10a180b_silverAttacks_();

		SYNCCOUT << "(^q^) 1- 6. 歩の利きビットボードの初期化！" << SYNCENDL;
		g_pawnAttackBb.initialize_10a200b_pawnAttacks_();

		SYNCCOUT << "(^q^) 1- 7. 桂の利きビットボードの初期化！" << SYNCENDL;
		g_knightAttackBb.initialize_10a220b_knightAttacks_();

		SYNCCOUT << "(^q^) 1- 8. 香の利きビットボードの初期化！" << SYNCENDL;
		g_lanceAttackBb.initialize_10a240b_lanceAttacks_();

		SYNCCOUT << "(^q^) 1- 9. ２つのマスの位置関係が［同筋］［同段］［同右肩上がり］［同右肩下がり］［その他］かを区別するビットボードの初期化！" << SYNCENDL;
		g_squareRelation.initialize_10a260b_squareRelations_();


		// 障害物が無いときの利きの Bitboard
		// g_rookAttack, g_bishopAttack, g_lanceAttack を設定してから、この関数を呼ぶこと。


		SYNCCOUT << "(^q^) 1-10. 障害物が無いときの飛の利きビットボードの初期化！" << SYNCENDL;
		g_rookAttackBb.initialize_10a280b_rookToEdge();

		SYNCCOUT << "(^q^) 1-11. 障害物が無いときの角の利きビットボードの初期化！" << SYNCENDL;
		g_bishopAttackBb.initialize_10a300b_bishopToEdge();

		SYNCCOUT << "(^q^) 1-12. 障害物が無いときの香の利きビットボードの初期化！" << SYNCENDL;
		g_lanceAttackBb.initialize_10a320b_lanceToEdge();

		SYNCCOUT << "(^q^) 1-13. ［飛車、角の元位置］と、［その利き］の２点のビットボード？の初期化！" << SYNCENDL;
		g_betweenBb.initialize_10a340b_between();

		SYNCCOUT << "(^q^) 1-14. 金の王手？ビットボードの初期化！" << SYNCENDL;
		g_goldAttackBb.initialize_10a360b_checkTableGold();

		SYNCCOUT << "(^q^) 1-15. 銀の王手？ビットボードの初期化！" << SYNCENDL;
		g_silverAttackBb.initialize_10a380b_checkTableSilver();

		SYNCCOUT << "(^q^) 1-16. 桂の王手？ビットボードの初期化！" << SYNCENDL;
		g_knightAttackBb.initialize_10a400b_checkTableKnight();

		SYNCCOUT << "(^q^) 1-17. 香の王手？ビットボードの初期化！" << SYNCENDL;
		g_lanceAttackBb.initialize_10a420b_checkTableLance();

		SYNCCOUT << "(^q^) 1-18. ２点の距離初期化！" << SYNCENDL;
		TwoSquaresDistanceKindInitializer::initialize_10a440b_twoSquaresDistanceKind(g_twoSquaresDistanceKind);

		SYNCCOUT << "(^q^) I-19. 定跡初期化！" << SYNCENDL;
		Book::initialize_10a460b_book();

		SYNCCOUT << "(^q^) 1-20. 検索テーブル初期化！" << SYNCENDL;
		initialize_10a480b_searchTable();
	}

	SYNCCOUT << "(^q^) 2   . 局面のゾブリストハッシュ初期化！" << SYNCENDL;
	Position::initialize_10a490b_zobrist();

	SYNCCOUT << "(^q^) 3   . 探索部の初期化！" << SYNCENDL;
	this->searcher->initialize_10a500b_ourCarriage();


	// 一時オブジェクトの生成と破棄


	SYNCCOUT << "(^q^) 4   . 評価関数の初期化！" << SYNCENDL;
	std::unique_ptr<KkKkpKppStorage1>(new KkKkpKppStorage1)->initialize_10a540b_kkKkpKppStorage(this->searcher->m_engineOptions["Eval_Dir"], true);

	SYNCCOUT << "(^q^) 次は USIループへ！" << SYNCENDL;
}


/// <summary>
/// ループ本体。
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void App10::body_50a(int argc, char* argv[])
{
	UsiLoop usiLoop;
	usiLoop.start_50a500b_mainloop(argc, argv, *this->searcher);
}


/// <summary>
/// 事後処理。
/// </summary>
void App10::finalize_90a()
{
	SYNCCOUT << "(^q^)main(6/6): threads.exit! ----> doUSICommandLoop" << SYNCENDL;
	this->searcher->m_monkiesPub.exit_90a500b();
}
