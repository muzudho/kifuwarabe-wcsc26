#include <iostream>
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../header/n160_boardBb_/n160_100_bitboard.hpp"
#include "../../header/n160_boardBb_/n160_110_silverAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_120_bishopAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_130_lanceAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_140_goldAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_150_rookAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_160_kingAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_180_knightAttackBb.hpp"
#include "../../header/n160_boardBb_/n160_190_pawnAttackBb.hpp"
#include "../../header/n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../../header/n105_200_sqDistan/n105_200_600_utilSquareDistance.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n480_tt______/n480_300_tt.hpp"
#include "../../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../../header/n600_book____/n600_500_book.hpp"
#include "../../header/n760_thread__/n760_400_herosPub.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"
#include "..\..\header\n900_main____/n900_300_usiLoop.hpp"
#include "..\..\header\n900_main____\n900_400_main01.hpp"


/// <summary>
/// 生成。
/// </summary>
Main01::Main01()
{
	this->searcher = std::unique_ptr<OurCarriage>(new OurCarriage);
}


/// <summary>
/// 破棄。
/// </summary>
Main01::~Main01()
{
	this->searcher.reset();
}


/// <summary>
/// 最初の設定（初期化）。
/// </summary>
void Main01::Initialize()
{
	//────────────────────────────────────────────────────────────────────────────────
	// ビットボードとテーブルの初期化☆（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	{
		SYNCCOUT << "(^q^) 1   . ビットボードとテーブルを初期化するぜ！" << SYNCENDL;

#ifndef SKIP_LONG_TIME_EVAL
		// 長い時間が掛かる初期化処理をするか？
		SYNCCOUT << "(^q^) 1- 1. 飛の利きビットボードの初期化！" << SYNCENDL;
		g_rookAttackBb.InitRookAttacks();
#endif

		SYNCCOUT << "(^q^) 1- 2. 角の利きビットボードの初期化！" << SYNCENDL;
		g_bishopAttackBb.InitBishopAttacks();

		SYNCCOUT << "(^q^) 1- 3. 玉の利きビットボードの初期化！" << SYNCENDL;
		g_kingAttackBb.Initialize();

		SYNCCOUT << "(^q^) 1- 4. 金の利きビットボードの初期化！" << SYNCENDL;
		g_goldAttackBb.Initialize();

		SYNCCOUT << "(^q^) 1- 5. 銀の利きビットボードの初期化！" << SYNCENDL;
		g_silverAttackBb.Initialize();

		SYNCCOUT << "(^q^) 1- 6. 歩の利きビットボードの初期化！" << SYNCENDL;
		g_pawnAttackBb.Initialize();

		SYNCCOUT << "(^q^) 1- 7. 桂の利きビットボードの初期化！" << SYNCENDL;
		g_knightAttackBb.Initialize();

		SYNCCOUT << "(^q^) 1- 8. 香の利きビットボードの初期化！" << SYNCENDL;
		g_lanceAttackBb.Initialize();

		SYNCCOUT << "(^q^) 1- 9. ２つのマスの位置関係が［同筋］［同段］［同右肩上がり］［同右肩下がり］［その他］かを区別するビットボードの初期化！" << SYNCENDL;
		g_squareRelation.Initialize();


		// 障害物が無いときの利きの Bitboard
		// g_rookAttack, g_bishopAttack, g_lanceAttack を設定してから、この関数を呼ぶこと。


		SYNCCOUT << "(^q^) 1-10. 障害物が無いときの飛の利きビットボードの初期化！" << SYNCENDL;
		g_rookAttackBb.InitializeToEdge();

		SYNCCOUT << "(^q^) 1-11. 障害物が無いときの角の利きビットボードの初期化！" << SYNCENDL;
		g_bishopAttackBb.InitializeToEdge();

		SYNCCOUT << "(^q^) 1-12. 障害物が無いときの香の利きビットボードの初期化！" << SYNCENDL;
		g_lanceAttackBb.InitializeToEdge();

		SYNCCOUT << "(^q^) 1-13. ［飛車、角の元位置］と、［その利き］の２点のビットボード？の初期化！" << SYNCENDL;
		g_betweenBb.Initialize();

		SYNCCOUT << "(^q^) 1-14. 金の王手？ビットボードの初期化！" << SYNCENDL;
		g_goldAttackBb.InitCheckTableGold();

		SYNCCOUT << "(^q^) 1-15. 銀の王手？ビットボードの初期化！" << SYNCENDL;
		g_silverAttackBb.InitCheckTableSilver();

		SYNCCOUT << "(^q^) 1-16. 桂の王手？ビットボードの初期化！" << SYNCENDL;
		g_knightAttackBb.InitCheckTableKnight();

		SYNCCOUT << "(^q^) 1-17. 香の王手？ビットボードの初期化！" << SYNCENDL;
		g_lanceAttackBb.InitCheckTableLance();

		SYNCCOUT << "(^q^) 1-18. ２点の距離初期化！" << SYNCENDL;
		UtilSquareDistance::InitSquareDistance(g_squareDistance);

		SYNCCOUT << "(^q^) I-19. 定跡初期化！" << SYNCENDL;
		Book::Init();

		SYNCCOUT << "(^q^) 1-20. 検索テーブル初期化！" << SYNCENDL;
		InitSearchTable();
	}

	SYNCCOUT << "(^q^) 2   . 局面のゾブリストハッシュ初期化！" << SYNCENDL;
	Position::InitZobrist();

	SYNCCOUT << "(^q^) 3   . 探索部の初期化！" << SYNCENDL;
	this->searcher->Init();


	// 一時オブジェクトの生成と破棄


	SYNCCOUT << "(^q^) 4   . 評価関数の初期化！" << SYNCENDL;
	std::unique_ptr<KkKkpKppStorage1>(new KkKkpKppStorage1)->Init(this->searcher->m_engineOptions["Eval_Dir"], true);

	SYNCCOUT << "(^q^) 次は USIループへ！" << SYNCENDL;
}


/// <summary>
/// ループ本体。
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
void Main01::Body(int argc, char* argv[])
{
	UsiLoop usiLoop;
	usiLoop.Mainloop(argc, argv, *this->searcher);
}


/// <summary>
/// 事後処理。
/// </summary>
void Main01::Finalize()
{
	SYNCCOUT << "(^q^)main(6/6): threads.exit! ----> doUSICommandLoop" << SYNCENDL;
	this->searcher->m_ownerHerosPub.Exit();
}
