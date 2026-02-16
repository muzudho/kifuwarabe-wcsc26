#pragma once
#include "muz_position_base_model.hpp"
#include "../../src/concept_game_engine/muz_game_engine_storage_model.hpp"
#include "../../src/lib_toybox_base/color.hpp"
#include "../../src/lib_bitboard/n160_100_bitboard.hpp"
#include "../../src/lib_bitboard/n160_102_FileMaskBb.hpp"
#include "../../src/lib_bitboard/n160_106_inFrontMaskBb.hpp"
#include "../../src/lib_bitboard/n160_240_betweenBb.hpp"
#include "../../src/lib_bitboard/n160_400_printBb.hpp"
#include "../../src/lib_bitboard/n160_170_goldAndSilverAttackBb.hpp"
#include "../../src/lib_bitboard/n160_230_setMaskBb.hpp"
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../src/lib_toybox_base/square.hpp"
#include "../../src/lib_toybox_base/piece_type.hpp"
#include "../../src/lib_toybox_base/piece.hpp"
#include "../../src/lib_toybox_base/hand.hpp"
#include "../../header/n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../../header/n119_500_sweetnes/n119_200_PieceSweetness.hpp"
#include "../../header/n165_movStack/n165_400_move.hpp"
#include "../../header/n220_position/n220_100_repetitionType.hpp"
#include "../../header/n220_position/n220_150_checkInfo.hpp"
#include "../../header/n220_position/n220_350_stateInfo.hpp"
#include "../../header/n220_position/n220_400_evalList.hpp"
#include "../../header/n220_position/n220_640_utilAttack.hpp"
#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../header/n113_piece___/n113_155_convPiece.hpp"
#include "../../header/n165_movStack/n165_300_moveType.hpp"
#include "../../header/n350_pieceTyp/n350_040_ptEvent.hpp"
#include "../../header/n350_pieceTyp/n350_110_ptPawn.hpp"
#include "../../header/n350_pieceTyp/n350_120_ptLance.hpp"
#include "../../header/n350_pieceTyp/n350_130_ptKnight.hpp"
#include "../../header/n350_pieceTyp/n350_140_ptSilver.hpp"
#include "../../header/n350_pieceTyp/n350_150_ptBishop.hpp"
#include "../../header/n350_pieceTyp/n350_160_ptRook.hpp"
#include "../../header/n350_pieceTyp/n350_170_ptGold.hpp"
#include "../../header/n350_pieceTyp/n350_230_ptHorse.hpp"
#include "../../header/n350_pieceTyp/n350_240_ptDragon.hpp"
#include "../../header/n350_pieceTyp/n350_500_ptPrograms.hpp"
#include "../../header/n351_bonaDir_/n351_500_bonaDirArray.hpp"
#include "../../header/n407_moveGen_/n407_900_moveList.hpp"
#include "../../header/n520_evaluate/n520_500_kkKkpKppStorage1.hpp"
#include "../../header/n600_book____/n600_100_mt64bit.hpp"
#include <algorithm>	// std::min,std::max
#include <cassert>
#include <iostream>		// std::cout
#include <sstream>      // std::istringstream
#include <stack>


/// <summary>
/// XXX: 局面に関する何かの情報へのポインター（＾～＾）？
/// </summary>
using StateStackPtr = std::unique_ptr<std::stack<StateInfo> >;


// 依存関係回避のため。
class Monkie;
class MuzGameEngineStorageModel;


/// <summary>
///		<pre>
/// 局面
/// 
///		- クラスがでかすぎるぜ（＾～＾）
///		- 基本と、分析的なものを分けるべきかもしれないぜ（＾～＾）
///		</pre>
/// </summary>
class Position : public MuzPositionBaseModel {


public:


	// ========================================
	// 生成／破棄
	// ========================================


	/// <summary>
	/// 生成
	/// </summary>
	Position();

	explicit Position(MuzGameEngineStorageModel* s);

	Position(const Position& pos);

	Position(const Position& pos, Monkie* th);

	Position(const std::string& sfen, Monkie* th, MuzGameEngineStorageModel* s);


	// ========================================
	// 演算子のオーバーロード
	// ========================================


	Position& operator = (const Position& pos);


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sfen"></param>
	/// <param name="th"></param>
	void Set(const std::string& sfen, Monkie* th);


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <returns></returns>
	template<const Color US>
	Bitboard GetBbOf10() const
	{
		return this->m_BB_ByColor_[US];
	}
	Bitboard GetBbOf10(const PieceType pt) const;

	Bitboard GetBbOf10(const Color c) const;


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <param name="pt"></param>
	/// <returns></returns>
	template<Color US>
	Bitboard GetBbOf20(const PieceType pt) const {
		return this->GetBbOf10(pt) & this->GetBbOf10(US);
	}


	Bitboard GetBbOf20(const PieceType pt, const Color c) const;



	Bitboard GetBbOf20(const PieceType pt1, const PieceType pt2) const;

	// template<Color CLR>
	// Bitboard Position::GetBbOf30(const PieceType pt1, const PieceType pt2) const

	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <param name="pt1"></param>
	/// <param name="pt2"></param>
	/// <returns></returns>
	template<Color CLR>
	Bitboard GetBbOf30(const PieceType pt1, const PieceType pt2) const
	{
		return this->GetBbOf20(pt1, pt2) & this->GetBbOf10(CLR);
	}

	Bitboard GetBbOf(const PieceType pt1, const PieceType pt2, const PieceType pt3) const;

	Bitboard GetBbOf(const PieceType pt1, const PieceType pt2, const PieceType pt3, const PieceType pt4) const;

	Bitboard GetBbOf(const PieceType pt1, const PieceType pt2, const PieceType pt3, const PieceType pt4, const PieceType pt5) const;

	Bitboard GetOccupiedBB() const;


	/// <summary>
	/// emptyBB() よりもわずかに速いはず。
	/// emptyBB() とは異なり、全く使用しない位置(0 から数えて、right の 63bit目、left の 18 ~ 63bit目)
	/// の bit が 1 になっても構わないとき、こちらを使う。
	/// todo: SSEにビット反転が無いので実はそんなに速くないはず。不要。
	/// </summary>
	/// <returns></returns>
	Bitboard GetNOccupiedBB() const;

	Bitboard GetEmptyBB() const;


	/// <summary>
	/// 金、成り金 の Bitboard
	/// </summary>
	/// <returns></returns>
	Bitboard GetGoldsBB() const;

	Bitboard GetGoldsBB(const Color c) const;


	/// <summary>
	/// turn() 側が pin されている Bitboard を返す。
	/// checkersBB が更新されている必要がある。
	/// </summary>
	/// <returns></returns>
	Bitboard GetPinnedBB() const;


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="sq"></param>
	/// <returns></returns>
	template<Color US, Color THEM>
	bool IsPawnDropCheckMate(const Square sq) const;


	/// <summary>
	/// Pinされているfromの駒がtoに移動出来なければtrueを返す。
	/// </summary>
	/// <typeparam name="IsKnight"></typeparam>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="ksq"></param>
	/// <param name="pinned"></param>
	/// <returns></returns>
	template <bool IsKnight = false>
	bool IsPinnedIllegal(const Square from, const Square to, const Square ksq, const Bitboard& pinned) const {
		// 桂馬ならどこに動いても駄目。
		return g_setMaskBb.IsSet(&pinned, from) && (IsKnight || !g_squareRelation.IsAligned<true>(from, to, ksq));
	}


	/// <summary>
	/// 空き王手かどうか。
	/// </summary>
	/// <typeparam name="IsKnight"></typeparam>
	/// <param name="from"></param>
	/// <param name="to"></param>
	/// <param name="ksq"></param>
	/// <param name="dcBB"></param>
	/// <returns></returns>
	template <bool IsKnight = false>
	bool IsDiscoveredCheck(const Square from, const Square to, const Square ksq, const Bitboard& dcBB) const {
		// 桂馬ならどこに動いても空き王手になる。
		return g_setMaskBb.IsSet(&dcBB, from) && (IsKnight || !g_squareRelation.IsAligned<true>(from, to, ksq));
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Bitboard GetCheckersBB() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Bitboard GetPrevCheckersBB() const;


	/// <summary>
	/// 王手が掛かっているか。
	/// </summary>
	/// <returns></returns>
	bool inCheck() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Sweetness GetMaterial() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Sweetness GetMaterialDiff() const;


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <returns></returns>
	template<const Color COLOR>
	FORCE_INLINE Square GetKingSquare() const
	{
		// assert(m_kingSquare_[COLOR] == this->GetBbOf<COLOR>(N08_King).GetFirstOneFromI9());
		assert(m_kingSquare_[COLOR] == this->GetBbOf10(N08_King).GetFirstOneFromI9());
		return m_kingSquare_[COLOR];
	}
	FORCE_INLINE Square GetKingSquare(const Color c) const {
		assert(m_kingSquare_[c] == this->GetBbOf20(N08_King, c).GetFirstOneFromI9());
		// assert(m_kingSquare_[c] == this->GetBbOf(N08_King, c).GetFirstOneFromI9());
		return m_kingSquare_[c];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	bool IsMoveGivesCheck(const Move m) const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="move"></param>
	/// <param name="ci"></param>
	/// <returns></returns>
	bool IsMoveGivesCheck(const Move move, const CheckInfo& ci) const;


	/// <summary>
	/// 王手？
	/// </summary>
	/// <param name="sq"></param>
	/// <param name="occupied"></param>
	/// <returns></returns>
	Bitboard GetAttackersTo(const Square sq, const Bitboard& occupied) const;


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="TURN1"></typeparam>
	/// <typeparam name="TURN2"></typeparam>
	/// <param name="sq"></param>
	/// <param name="occupied"></param>
	/// <returns></returns>
	template<
		Color TURN1,
		Color TURN2//TURN1の相手の色
	>
	Bitboard GetAttackersTo_a(const Square sq, const Bitboard& occupied) const {
		const PieceTypeEvent ptEvent1(occupied, TURN2, sq);
		return ((PiecetypePrograms::m_PAWN.GetAttacks2From(ptEvent1) & this->GetBbOf10(N01_Pawn))
			| (PiecetypePrograms::m_LANCE.GetAttacks2From(ptEvent1) & this->GetBbOf10(N02_Lance))
			| (PiecetypePrograms::m_KNIGHT.GetAttacks2From(ptEvent1) & this->GetBbOf10(N03_Knight))
			| (PiecetypePrograms::m_SILVER.GetAttacks2From(ptEvent1) & this->GetBbOf10(N04_Silver))
			| (PiecetypePrograms::m_GOLD.GetAttacks2From(ptEvent1) & GetGoldsBB())
			| (PiecetypePrograms::m_BISHOP.GetAttacks2From(ptEvent1) & this->GetBbOf20(N05_Bishop, N13_Horse))
			| (PiecetypePrograms::m_ROOK.GetAttacks2From(ptEvent1) & this->GetBbOf20(N06_Rook, N14_Dragon))
			| (PiecetypePrograms::m_KING.GetAttacks2From(ptEvent1) & this->GetBbOf(N08_King, N13_Horse, N14_Dragon)))
			& this->GetBbOf10(TURN1);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <param name="occupied"></param>
	/// <returns></returns>
	Bitboard GetAttackersTo_clr(const Color c, const Square sq, const Bitboard& occupied) const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	Bitboard GetAttackersToExceptKing(const Color c, const Square sq) const;


	/// <summary>
	/// todo: 利きをデータとして持ったとき、attackersToIsNot0() を高速化すること。
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	bool IsAttackersToIsNot0(const Color c, const Square sq) const;

	bool IsAttackersToIsNot0(const Color c, const Square sq, const Bitboard& occupied) const;


	/// <summary>
	/// 移動王手が味方の利きに支えられているか。false なら相手玉で取れば詰まない。
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	bool IsUnDropCheckIsSupported(const Color c, const Square sq) const;


	/// <summary>
	/// pseudoLegal とは
	/// ・玉が相手駒の利きがある場所に移動する
	/// ・pin の駒を移動させる
	/// ・連続王手の千日手の手を指す
	/// これらの反則手を含めた手の事と定義する。
	/// よって、打ち歩詰めや二歩の手は pseudoLegal では無い。
	/// </summary>
	/// <typeparam name="MUSTNOTDROP"></typeparam>
	/// <typeparam name="FROMMUSTNOTBEKING"></typeparam>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="move"></param>
	/// <param name="pinned"></param>
	/// <returns></returns>
	template <bool MUSTNOTDROP, bool FROMMUSTNOTBEKING, Color US, Color THEM>
	bool IsPseudoLegalMoveIsLegal(const Move move, const Bitboard& pinned) const;


	/// <summary>
	/// FIXME: これ使ってないのでは☆？（＾ｑ＾）？
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="move"></param>
	/// <param name="pinned"></param>
	/// <returns></returns>
	template<Color US, Color THEM>
	bool IsPseudoLegalMoveIsEvasion(const Move move, const Bitboard& pinned) const;


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="move"></param>
	/// <param name="asymmThreshold"></param>
	/// <returns></returns>
	template<Color US, Color THEM>
	Sweetness GetSee1(const Move move, const int asymmThreshold = 0) const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	Sweetness GetSeeSign(const Move move) const;


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <returns></returns>
	template <Color US, Color THEM>
	Move GetMateMoveIn1Ply();
	//Move GetMateMoveIn1Ply();


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetBoardKey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetHandKey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetKey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetExclusionKey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetKeyExcludeTurn() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	u64 getNodesSearched() const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="n"></param>
	void setNodesSearched(const u64 n);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="checkMaxPly"></param>
	/// <returns></returns>
	RepetitionType IsRepetition(const int checkMaxPly = std::numeric_limits<int>::max()) const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Monkie* getHandleMonkey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	static constexpr int GetNlist() {
		return EvalList::m_ListSize;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	int GetList0(const int index) const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	int GetList1(const int index) const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	int GetSquareHandToList(const Square sq) const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="i"></param>
	/// <returns></returns>
	Square GetListToSquareHand(const int i) const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int* GetPlist0();


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int* GetPlist1();


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const int* GetCplist0() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const int* GetCplist1() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const ChangedLists& GetCl() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const MuzGameEngineStorageModel* GetConstOurCarriage() const;


	/// <summary>
	/// わたしたちの馬車を取得
	/// </summary>
	/// <returns></returns>
	MuzGameEngineStorageModel* GetOurCarriage() const;


	/// <summary>
	/// わたしたちの馬車を設定
	/// </summary>
	/// <param name="s"></param>
	void SetOurCarriage(MuzGameEngineStorageModel* ourCarriage);


#if !defined NDEBUG
	/// <summary>
	/// for debug
	/// </summary>
	/// <returns></returns>
	bool IsOK() const;
#endif


	/// <summary>
	/// メンバーを変更するのに使われる。
	/// </summary>
	/// <returns></returns>
	inline StateInfo* GetStateInfo() { return m_st_; }


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// 間の駒を動かすことで、turn() 側が空き王手が出来る駒のBitboardを返す。
	/// checkersBB が更新されている必要はない。
	/// BetweenIsUs == true  : 間の駒が自駒。
	/// BetweenIsUs == false : 間の駒が敵駒。
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <typeparam name="BetweenIsUs"></typeparam>
	/// <returns></returns>
	template <Color US, Color THEM, bool BetweenIsUs = true>
	Bitboard DiscoveredCheckBB() const {

		return GetHiddenCheckers<false, BetweenIsUs, US, THEM>();
		/*
		if (this->GetTurn() == Color::Black)
		{
			return GetHiddenCheckers<false, BetweenIsUs,Color::Black,Color::White>();
		}
		else
		{
			return GetHiddenCheckers<false, BetweenIsUs,Color::White,Color::Black>();
		}
		*/
	}


	/// <summary>
	/// toFile と同じ筋に us の歩がないなら true
	/// </summary>
	/// <param name="us"></param>
	/// <param name="toFile"></param>
	/// <returns></returns>
	bool NoPawns(const Color us, const File toFile) const;


	/// <summary>
	/// checkPawnDrop : 二歩と打ち歩詰めも調べるなら true
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="move"></param>
	/// <param name="checkPawnDrop"></param>
	/// <returns></returns>
	template<Color US, Color THEM>
	bool MoveIsPseudoLegal(const Move move, const bool checkPawnDrop = false) const;


#if !defined NDEBUG
	/// <summary>
	/// 
	/// </summary>
	/// <param name="GetMove"></param>
	/// <returns></returns>
	bool MoveIsLegal(const Move GetMove) const;
#endif


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="move"></param>
	/// <param name="newSt"></param>
	template<Color US,Color THEM>
	void DoMove(const Move move, StateInfo& newSt);


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="move"></param>
	/// <param name="newSt"></param>
	/// <param name="ci"></param>
	/// <param name="moveIsCheck"></param>
	template<Color US, Color THEM>
	void DoMove(const Move move, StateInfo& newSt, const CheckInfo& ci, const bool moveIsCheck);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="move"></param>
	void UndoMove(const Move move);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="DO"></param>
	/// <param name="backUpSt"></param>
	void DoNullMove(bool DO, StateInfo& backUpSt);


	/// <summary>
	/// 
	/// </summary>
	void Print() const;


	/// <summary>
	/// 
	/// </summary>
	static void initialize_10a310b_zobrist();


private:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// このポジションをピースタイプ毎にビットボードにしたもの。（byTypeBB は敵、味方の駒を区別しない）
	/// </summary>
	Bitboard m_BB_ByPiecetype_[g_PIECETYPE_NUM];

	/// <summary>
	/// このポジションを白黒毎にビットボードにしたもの。（byColorBB は駒の種類を区別しない）
	/// </summary>
	Bitboard m_BB_ByColor_[g_COLOR_NUM];

	/// <summary>
	/// このポジションのカナゴマをビットボードにしたもの。
	/// </summary>
	Bitboard m_goldsBB_;

	/// <summary>
	/// 
	/// </summary>
	Square m_kingSquare_[g_COLOR_NUM];

	/// <summary>
	/// 
	/// </summary>
	EvalList m_evalList_;

	/// <summary>
	/// 
	/// </summary>
	StateInfo m_startState_;

	/// <summary>
	/// 
	/// </summary>
	StateInfo* m_st_;

	/// <summary>
	/// 
	/// </summary>
	Monkie* m_thisThread_;

	/// <summary>
	/// 
	/// </summary>
	u64 m_nodes_;

	/// <summary>
	/// ゲームエンジン倉庫
	/// </summary>
	MuzGameEngineStorageModel* m_pGameEngineStore_;

	/// <summary>
	/// 
	/// </summary>
	static Key m_ZOBRIST_[g_PIECETYPE_NUM][SquareNum][g_COLOR_NUM];

	/// <summary>
	/// 
	/// </summary>
	static const Key m_zobTurn_ = 1;

	/// <summary>
	/// 
	/// </summary>
	static Key m_ZOB_HAND_[HandPieceNum][g_COLOR_NUM];

	/// <summary>
	/// todo: これが必要か、要検討
	/// </summary>
	static Key m_ZOB_EXCLUSION_;


	// ========================================
	// アクセッサ
	// ========================================


	/// <summary>
	/// 
	/// </summary>
	/// <param name="piece"></param>
	/// <param name="sq"></param>
	void SetPiece(const Piece piece, const Square sq);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="hp"></param>
	/// <param name="c"></param>
	/// <param name="num"></param>
	void SetHand(const HandPiece hp, const Color c, const int num);


	void SetHand(const Piece piece, const int num);


	/// <summary>
	/// turn() 側が
	/// pin されて(して)いる駒の Bitboard を返す。
	/// BetweenIsUs == true  : 間の駒が自駒。
	/// BetweenIsUs == false : 間の駒が敵駒。
	/// </summary>
	/// <typeparam name="FindPinned"></typeparam>
	/// <typeparam name="BetweenIsUs"></typeparam>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <returns></returns>
	template <bool FindPinned, bool BetweenIsUs, Color US, Color THEM>
	Bitboard GetHiddenCheckers() const {
		Bitboard result = Bitboard::CreateAllZeroBB();
		// pin する遠隔駒
		// まずは自駒か敵駒かで大雑把に判別
		Bitboard pinners = this->GetBbOf10(FindPinned ? THEM : US);

		const Square ksq = GetKingSquare(FindPinned ? US : THEM);

		// 障害物が無ければ玉に到達出来る駒のBitboardだけ残す。
		pinners &= (
			this->GetBbOf10(N02_Lance) &
			g_lanceAttackBb.GetControllBbToEdge((FindPinned ? US : THEM), ksq)
			) |
			(
				this->GetBbOf20(N06_Rook, N14_Dragon) &
				g_rookAttackBb.GetControllBbToEdge(ksq)
				) |
			(
				this->GetBbOf20(N05_Bishop, N13_Horse) &
				g_bishopAttackBb.GetControllBbToEdge(ksq)
				);

		while (pinners.Exists1Bit()) {
			const Square sq = pinners.PopFirstOneFromI9();
			// pin する遠隔駒と玉の間にある駒の位置の Bitboard
			const Bitboard between = g_betweenBb.GetBetweenBB(sq, ksq) & GetOccupiedBB();

			// pin する遠隔駒と玉の間にある駒が1つで、かつ、引数の色のとき、その駒は(を) pin されて(して)いる。
			if (between.Exists1Bit()
				&& between.IsOneBit<false>()
				&& between.AndIsNot0(this->GetBbOf10(BetweenIsUs ? US : THEM)))
			{
				result |= between;
			}
		}

		return result;
	}


#if !defined NDEBUG
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int GetDebugSetEvalList() const;
#endif


	/// <summary>
	/// 
	/// </summary>
	void SetEvalList();


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetComputeBoardKey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetComputeHandKey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Key GetComputeKey() const;


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <param name="pt"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	template<Color CLR>
	static Key GetZobrist(const PieceType pt, const Square sq)
	{
		return Position::m_ZOBRIST_[pt][sq][CLR];
	}
	static Key GetZobrist(const PieceType pt, const Square sq, const Color c);


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	static Key GetZobTurn();


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <param name="hp"></param>
	/// <returns></returns>
	template<Color CLR>
	static Key GetZobHand(const HandPiece hp)
	{
		return Position::m_ZOB_HAND_[hp][CLR];
	}
	static Key GetZobHand(const HandPiece hp, const Color c);


	// ========================================
	// メイン・メソッド
	// ========================================


	/// <summary>
	/// クリアー
	/// </summary>
	void Clear();


	/// <summary>
	/// 手番側の玉へ check している駒を全て探して checkersBB_ にセットする。
	/// 最後の手が何か覚えておけば、attackersTo() を使用しなくても良いはずで、処理が軽くなる。
	/// </summary>
	void FindCheckers();


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Sweetness ComputeMaterial() const;


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="CLR"></typeparam>
	/// <param name="pt"></param>
	/// <param name="sq"></param>
	template<Color CLR>
	inline void XorBBs(const PieceType pt, const Square sq) {
		g_setMaskBb.XorBit(&this->m_BB_ByPiecetype_[N00_Occupied], sq);
		g_setMaskBb.XorBit(&this->m_BB_ByPiecetype_[pt], sq);
		g_setMaskBb.XorBit(&this->m_BB_ByColor_[CLR], sq);
	}
	void XorBBs(const PieceType pt, const Square sq, const Color c);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	void PrintHand(const Color c) const;
};
