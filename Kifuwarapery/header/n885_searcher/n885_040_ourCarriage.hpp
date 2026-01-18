#pragma once
#include <string>
#include <sstream>
#include "../n119_score___/n119_090_scoreIndex.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n160_board___/n160_130_lanceAttackBb.hpp"
#include "../n160_board___/n160_150_rookAttackBb.hpp"
#include "../n160_board___/n160_220_queenAttackBb.hpp"
#include "../n160_board___/n160_230_setMaskBb.hpp"
#include "../n220_position/n220_645_gameStats.hpp"
#include "../n223_move____/n223_060_stats.hpp"
#include "../n350_pieceTyp/n350_040_ptEvent.hpp"
#include "../n350_pieceTyp/n350_500_ptPrograms.hpp"
#include "../n560_timeMgr_/n560_500_timeManager.hpp"
#include "../n640_searcher/n640_128_signalsType.hpp"
#include "../n640_searcher/n640_450_rootMove.hpp"
#include "../n680_egOption/n680_240_engineOptionsMap.hpp"
#include "../n640_searcher/n640_440_splitedNode.hpp"
#include "../n760_thread__/n760_400_monkiesPub.hpp"
#include "../n800_learn___/n800_100_stopwatch.hpp"
#include "n885_510_adventureContinent.hpp"

using namespace std;
using History = Stats<false>;
using Gains   = Stats<true>;


/// <summary>
///		<pre>
/// わたしたちの馬車
/// 
///		- 元の名前：　1.Ｓearcher, 2.Ｒucksack
///		- 複数の探索スレッドに渡される、単一のデータのかたまり。
///		</pre>
/// </summary>
class OurCarriage {


public:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// シグナル？
	/// </summary>
	volatile SignalsType		m_signals;

	/// <summary>
	/// 思考用の時間などの上限☆？
	/// </summary>
	LimitsDuringGo		m_limits;

	/// <summary>
	///		<pre>
	/// 元の名前：ｓｅａｒｃｈＭｏｖｅｓ
	/// 送られてきた棋譜。（現局面までの指し手のスタック）
	///		</pre>
	/// </summary>
	std::vector<Move>		m_ourMoves;

	/// <summary>
	/// 検索用タイマー？
	/// </summary>
	Stopwatch		m_stopwatch;

	/// <summary>
	/// ステータス？
	/// </summary>
	StateStackPtr		m_setUpStates;

	/// <summary>
	/// ルート？ 前回の反復深化探索☆？（イテレーション）の結果が入っているみたいだぜ☆
	/// </summary>
	std::vector<RootMove>		m_rootMoves;

#if defined LEARN
	/// <summary>
	/// アルファ
	/// </summary>
	ScoreIndex		m_alpha;

	/// <summary>
	/// ベータ
	/// </summary>
	ScoreIndex		m_beta;
#endif

	/// <summary>
	/// 本譜のサイズ？
	/// </summary>
	size_t		m_pvSize;

	/// <summary>
	/// インデックス？
	/// </summary>
	size_t		m_pvIdx;

	/// <summary>
	/// 時間管理
	/// </summary>
	TimeManager		m_timeMgr;

	/// <summary>
	/// ヒストリー？
	/// </summary>
	History		m_history;

	/// <summary>
	/// ゲインズ？
	/// </summary>
	Gains		m_gains;

	/// <summary>
	/// トランジション・テーブル。
	/// </summary>
	TranspositionTable		m_tt;

#if defined INANIWA_SHIFT
	InaniwaFlag		inaniwaFlag;
#endif
#if defined BISHOP_IN_DANGER
	BishopInDangerFlag		bishopInDangerFlag;
#endif

	/// <summary>
	/// ゲームの統計的なデータ。
	/// </summary>
	GameStats	m_gameStats;

	/// <summary>
	/// 開始局面？
	/// </summary>
	Position	m_rootPosition;

	/// <summary>
	///		<pre>
	/// 猿酒場
	/// 
	///		- スレッドプール
	///		</pre>
	/// </summary>
	MonkiesPub	m_pub;

	/// <summary>
	/// USIオプション？
	/// </summary>
	EngineOptionsMap	m_engineOptions;

	/// <summary>
	/// true にすると、シングルスレッドで動作する。デバッグ用。
	/// </summary>
	static const bool	FakeSplit = false;

	/// <summary>
	/// checkTime() を呼び出す最大間隔(msec)
	/// </summary>
	const int	TimerResolution = 5;


	// ========================================
	// メソッド
	// ========================================


	/// <summary>
	/// ベストムーブ・チェンジスって何だぜ☆？（＾ｑ＾）
	/// </summary>
	/// <returns></returns>
	inline Ply GetBestMovePlyChanges()
	{
		return this->m_bestMovePlyChanges_;
	}


	/// <summary>
	/// 
	/// </summary>
	inline void ZeroclearBestMovePlyChanges()
	{
		this->m_bestMovePlyChanges_ = 0;
	}


	/// <summary>
	/// 本筋じゃないときに呼び出されるぜ（＾～＾）
	/// </summary>
	inline void IncreaseBestMovePlyChanges()
	{
		++this->m_bestMovePlyChanges_;
	}


	/// <summary>
	/// 初期化？
	/// </summary>
	void	initialize_10a500b_search();


	/// <summary>
	/// 本譜の情報？
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="depth"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	/// <returns></returns>
	std::string		PvInfoToUSI(Position& pos, const Ply depth, const ScoreIndex alpha, const ScoreIndex beta);


#if defined INANIWA_SHIFT
	void	detectInaniwa(const Position& GetPos);
#endif
#if defined BISHOP_IN_DANGER
	void	detectBishopInDanger(const Position& GetPos);
#endif


	/// <summary>
	/// 時間チェック？
	/// </summary>
	void	CheckTime();


	/// <summary>
	/// エンジン・オプション設定？
	/// </summary>
	/// <param name="ssCmd"></param>
	void	SetOption(std::istringstream& ssCmd);


	//private:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="score"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	/// <returns></returns>
	std::string		scoreToUSI(const ScoreIndex score, const ScoreIndex alpha, const ScoreIndex beta) {
		std::stringstream ss;

		if (abs(score) < ScoreMateInMaxPly) {
			// cp は centi pawn の略
			ss << "cp " << score * 100 / PieceScore::m_pawn;
		}
		else {
			// mate の後には、何手で詰むかを表示する。
			ss << "mate " << (0 < score ? ScoreMate0Ply - score : -ScoreMate0Ply - score);
		}

		ss << (beta <= score ? " lowerbound" : score <= alpha ? " upperbound" : "");

		return ss.str();
	}


	//private:


	inline std::string		scoreToUSI(const ScoreIndex score) {
		return scoreToUSI(score, -ScoreIndex::ScoreInfinite, ScoreIndex::ScoreInfinite);
	}


public://private:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="d"></param>
	/// <returns></returns>
	inline ScoreIndex	razorMargin(const Depth d) {
		return static_cast<ScoreIndex>(512 + 16 * static_cast<int>(d));
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline bool		checkIsDangerous() {
		// not implement
		// 使用しないで良いかも知れない。
		return false;
	}


	/// <summary>
	/// 1 ply前の first move によって second move が合法手にするか。
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="first"></param>
	/// <param name="second"></param>
	/// <returns></returns>
	bool allows(const Position& pos, const Move first, const Move second) {
		const Square m1to = first.To();
		const Square m1from = first.From();
		const Square m2from = second.From();
		const Square m2to = second.To();
		if (m1to == m2from || m2to == m1from) { return true; }
		if (second.IsDrop() && first.IsDrop()) { return false; }

		if (!second.IsDrop() && !first.IsDrop()) {
			if (g_setMaskBb.IsSet(&g_betweenBb.GetBetweenBB(m2from, m2to), m1from)) { return true; }
		}

		const PieceType m1pt = first.GetPieceTypeFromOrDropped();
		const Color us = pos.GetTurn();
		const Bitboard occ = (second.IsDrop() ? pos.GetOccupiedBB() : pos.GetOccupiedBB() ^ g_setMaskBb.GetSetMaskBb(m2from));
		const Bitboard m1att = UtilAttack::GetAttacksFrom(m1pt, us, m1to, occ);
		if (g_setMaskBb.IsSet(&m1att, m2to)) { return true; }
		if (g_setMaskBb.IsSet(&m1att, pos.GetKingSquare(us))) { return true; }

		return false;
	}


	/// <summary>
	/// トランスポジション・テーブル用にスコアを変更する？
	/// </summary>
	/// <param name="score"></param>
	/// <param name="ply"></param>
	/// <returns></returns>
	ScoreIndex ConvertScoreToTT(const ScoreIndex score, const Ply ply) {
		assert(score != ScoreNone);

		return (
			// mate表示をするとき☆
			ScoreMateInMaxPly <= score ?
			// スコアの土台に、手数（mate）を乗せるぜ☆！
			score + static_cast<ScoreIndex>(ply)
			:
			score <= ScoreMatedInMaxPly ?
			// 先後逆のときも、手数を乗せる（マイナスをもっと引く）のは同じ☆
			score - static_cast<ScoreIndex>(ply)
			// それ以外のときは、そのままスコア表示。
			: score
		);
	}


	/// <summary>
	/// トランスポジション・テーブル用のスコアから、スコアを復元する？
	/// </summary>
	/// <param name="s"></param>
	/// <param name="ply"></param>
	/// <returns></returns>
	ScoreIndex ConvertScoreFromTT(const ScoreIndex s, const Ply ply) {
		return (s == ScoreNone ? ScoreNone
			: ScoreMateInMaxPly <= s ? s - static_cast<ScoreIndex>(ply)
			: s <= ScoreMatedInMaxPly ? s + static_cast<ScoreIndex>(ply)
			: s);
	}


	/// <summary>
	/// fitst move によって、first move の相手側の second move を違法手にするか。
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="pos"></param>
	/// <param name="first"></param>
	/// <param name="second"></param>
	/// <returns></returns>
	template<Color US, Color THEM>
	bool refutes(const Position& pos, const Move first, const Move second) {
		assert(pos.IsOK());

		const Square m2to = second.To();
		const Square m1from = first.From(); // 駒打でも今回はこれで良い。

		if (m1from == m2to) { return true; }

		const PieceType m2ptFrom = second.GetPieceTypeFrom();
		if (
			second.IsCaptureOrPromotion()
			&& (
				//(pos.GetPieceScore(second.GetCap()) <= pos.GetPieceScore(m2ptFrom))
				(PieceScore::GetPieceScore(second.GetCap()) <= PieceScore::GetPieceScore(m2ptFrom))
				||
				m2ptFrom == N08_King
				)
			) {
			// first により、新たに m2to に当たりになる駒があるなら true
			assert(!second.IsDrop());

			//const Color us = pos.GetTurn();
			const Square m1to = first.To();
			const Square m2from = second.From();
			Bitboard occ = pos.GetOccupiedBB() ^ g_setMaskBb.GetSetMaskBb(m2from) ^ g_setMaskBb.GetSetMaskBb(m1to);
			PieceType m1ptTo;

			if (first.IsDrop()) {
				m1ptTo = first.GetPieceTypeDropped();
			}
			else {
				m1ptTo = first.GetPieceTypeTo();
				occ ^= g_setMaskBb.GetSetMaskBb(m1from);
			}

			if (g_setMaskBb.IsSet(&UtilAttack::GetAttacksFrom(m1ptTo, US, m1to, occ), m2to)) { return true; }

			// first で動いた後、sq へ当たりになっている遠隔駒
			const PieceTypeEvent ptEventL(occ, THEM, m2to);
			const PieceTypeEvent ptEventRB(occ, Color::Null, m2to);
			const Bitboard xray =
				(PiecetypePrograms::m_LANCE.GetAttacks2From(ptEventL) & pos.GetBbOf20<US>(N02_Lance))
				| (PiecetypePrograms::m_ROOK.GetAttacks2From(ptEventRB) & pos.GetBbOf30<US>(N06_Rook, N14_Dragon))
				| (PiecetypePrograms::m_BISHOP.GetAttacks2From(ptEventRB) & pos.GetBbOf30<US>(N05_Bishop, N13_Horse));

			// sq へ当たりになっている駒のうち、first で動くことによって新たに当たりになったものがあるなら true
			if (xray.Exists1Bit() && (xray ^ (xray & g_queenAttackBb.GetControllBb(pos.GetOccupiedBB(), m2to))).Exists1Bit()) { return true; }
		}

		if (!second.IsDrop()
			&& ConvPieceType::IS_SLIDER10(m2ptFrom)
			&& g_setMaskBb.IsSet(&g_betweenBb.GetBetweenBB(second.From(), m2to), first.To())
			&& ScoreZero <= pos.GetSeeSign(first))
		{ return true; }

		return false;
	}


private:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///		<pre>
	/// ベストムーブ・チェンジスって何だぜ☆？（＾ｑ＾）
	/// なんか１ずつ増えるみたいだが……（＾～＾）
	/// 
	///		- 元の名前：ｂｅｓｔＭｏｖｅＣｈａｎｇｅｓ
	///		</pre>
	/// </summary>
	Ply		m_bestMovePlyChanges_;
};


/// <summary>
/// メイン関数で１回だけ呼ばれる。
/// </summary>
void initialize_10a300b_searchTable();


//────────────────────────────────────────────────────────────────────────────────
// 依存順の関係でここに☆（＾ｑ＾）
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
///		<pre>
/// 起きろ？
/// 一箇所でしか呼ばないので、FORCE_INLINE
///		</pre>
/// </summary>
/// <param name="ourCarriage">わたしたちの馬車</param>
/// <returns></returns>
FORCE_INLINE void		MonkiesPub::WakeUp(OurCarriage* ourCarriage) {
	// 全員初期化☆？
	for (size_t i = 0; i < this->m_monkies.size(); ++i) {
		(*this).m_monkies[i]->m_maxPly = 0;
	}

	// ［手の空いてる猿は寝かす］フラグを立てる☆
	this->m_isIdleMonkeyToSleep_ = ourCarriage->m_engineOptions["Use_Sleeping_Threads"];
}


/// <summary>
///		<pre>
/// 猿は寝てろ。
/// 
///		- 一箇所でしか呼ばないので、FORCE_INLINE
///		</pre>
/// </summary>
/// <returns></returns>
FORCE_INLINE void		MonkiesPub::SleepMonkies() {
	this->m_isIdleMonkeyToSleep_ = true;
}
