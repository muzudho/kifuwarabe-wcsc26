#include <iostream>
#include "../../header/n119_score___/n119_200_pieceScore.hpp"
#include "../../header/n160_board___/n160_106_inFrontMaskBb.hpp"
#include "../../header/n160_board___/n160_220_queenAttackBb.hpp"
#include "../../header/n160_board___/n160_230_setMaskBb.hpp"
#include "../../header/n800_learn___/n800_100_stopwatch.hpp"
#include "../../header/n886_repeType/n886_100_rtNot.hpp"
#include "../../header/n886_repeType/n886_110_rtDraw.hpp"
#include "../../header/n886_repeType/n886_120_rtWin.hpp"
#include "../../header/n886_repeType/n886_130_rtLose.hpp"
#include "../../header/n886_repeType/n886_140_rtSuperior.hpp"
#include "../../header/n886_repeType/n886_150_rtInferior.hpp"
#include "../../header/n886_repeType/n886_500_rtArray.hpp"
#include "../../header/n220_position/n220_100_repetitionType.hpp"
#include "../../header/n220_position/n220_640_utilAttack.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n220_position/n220_665_utilMoveStack.hpp"
#include "../../header/n220_position/n220_750_charToPieceUSI.hpp"
#include "../../header/n223_move____/n223_300_moveAndScoreIndex.hpp"
#include "../../header/n350_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n350_pieceTyp/n350_500_ptPrograms.hpp"
#include "../../header/n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../../header/n520_evaluate/n520_700_evaluation09.hpp"
#include "../../header/n560_timeMgr_/n560_500_timeManager.hpp"
#include "../../header/n600_book____/n600_500_book.hpp"
#include "../../header/n640_searcher/n640_040_nodeKind.hpp"
#include "../../header/n640_searcher/n640_440_splitedNode.hpp"
#include "../../header/n640_searcher/n640_500_reductions.hpp"
#include "../../header/n640_searcher/n640_510_futilityMargins.hpp"
#include "../../header/n640_searcher/n640_520_futilityMoveCounts.hpp"
#include "../../header/n680_egOption/n680_240_engineOptionsMap.hpp"
#include "../../header/n680_egOption/n680_300_engineOptionSetup.hpp"
#include "../../header/n755_sword___/n755_070_SwordAbstract.hpp"
#include "../../header/n760_thread__/n760_400_monkiesPub.hpp"
#include "../../header/n883_nodeKind/n883_070_adventurePlainNodekindAbstract.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"
#include "../../header/n885_searcher/n885_490_adventureMountainIterativeDeepeningLoop.hpp"
#include "../../header/n887_nodeKind/n887_500_adventurePlainNodekindPrograms.hpp"//FIXME:


using namespace std;
extern const InFrontMaskBb g_inFrontMaskBb;
extern AdventureNodekindAbstract* g_NODEKIND_PROGRAMS[];
//extern RepetitionTypeModels g_repetitionTypes;


/// <summary>
/// 最初の設定（初期化）を行うぜ☆（＾▽＾）
/// </summary>
void OurCarriage::initialize_10a500b_search() {
	EngineOptionSetup engineOptionSetup;
	engineOptionSetup.initialize_10a500b100c( &m_engineOptions, this);

	this->m_pub.initialize_10a500b500c(this);
	this->m_tt.setSize(this->m_engineOptions["USI_Hash"]);
}


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <param name="depth"></param>
/// <param name="alpha"></param>
/// <param name="beta"></param>
/// <returns></returns>
std::string OurCarriage::PvInfoToUSI(Position& pos, const Ply depth, const ScoreValue alpha, const ScoreValue beta) {

	// 思考時間（ミリ秒。読み筋表示用）
	const int time = m_stopwatch.GetElapsed();

	const size_t usiPVSize = m_pvSize;
	Ply selDepth = 0; // 選択的に読んでいる部分の探索深さ。
	std::stringstream ss;

	for (size_t i = 0; i < m_pub.m_monkies.size(); ++i) {
		if (selDepth < m_pub.m_monkies[i]->m_maxPly) {
			selDepth = m_pub.m_monkies[i]->m_maxPly;
		}
	}

	for (size_t i = usiPVSize-1; 0 <= static_cast<int>(i); --i) {
		const bool update = (i <= m_pvIdx);

		if (depth == 1 && !update) {
			continue;
		}

		const Ply d = (update ? depth : depth - 1);
		const ScoreValue s = (update ? m_rootMoves[i].m_score_ : m_rootMoves[i].m_prevScore_);

		ss << "info depth " << d
		   << " seldepth " << selDepth
		   << " score " << (i == m_pvIdx ? scoreToUSI(s, alpha, beta) : scoreToUSI(s))
		   << " nodes " << pos.getNodesSearched()
		   << " nps " << (0 < time ? pos.getNodesSearched() * 1000 / time : 0)
		   << " time " << time
		   << " multipv " << i + 1
		   << " pv ";

		for (int j = 0; !m_rootMoves[i].m_pv_[j].IsNone(); ++j) {
			ss << " " << m_rootMoves[i].m_pv_[j].ToUSI();
		}

		ss << std::endl;
	}
	return ss.str();
}


#if defined INANIWA_SHIFT
/// <summary>
/// 稲庭判定
/// </summary>
/// <param name="GetPos"></param>
void OurCarriage::detectInaniwa(const Position& GetPos) {
	if (inaniwaFlag == NotInaniwa && 20 <= GetPos.GetGamePly()) {
		const Rank TRank7 = (GetPos.GetTurn() == Black ? Rank7 : Rank3); // not constant
		const Bitboard mask = g_rankMaskBb.GetRankMask(TRank7) & ~g_fileMaskBb.GetFileMask(FileA) & ~g_fileMaskBb.GetFileMask(FileI);
		if ((GetPos.GetBbOf(N01_Pawn, ConvColor::OPPOSITE_COLOR10(GetPos.GetTurn())) & mask) == mask) {
			inaniwaFlag = (GetPos.GetTurn() == Black ? InaniwaIsWhite : InaniwaIsBlack);
			m_tt.Clear();
		}
	}
}
#endif


#if defined BISHOP_IN_DANGER
/// <summary>
/// 
/// </summary>
/// <param name="GetPos"></param>
void OurCarriage::detectBishopInDanger(const Position& GetPos) {
	if (bishopInDangerFlag == NotBishopInDanger && GetPos.GetGamePly() <= 50) {
		const Color them = ConvColor::OPPOSITE_COLOR10(GetPos.GetTurn());
		if (GetPos.m_hand(GetPos.GetTurn()).Exists<HBishop>()
			&& GetPos.GetBbOf(N04_Silver, them).IsSet(INVERSE_IF_WHITE20(them, H3))
			&& (GetPos.GetBbOf(N08_King  , them).IsSet(INVERSE_IF_WHITE20(them, F2))
				|| GetPos.GetBbOf(N08_King  , them).IsSet(INVERSE_IF_WHITE20(them, F3))
				|| GetPos.GetBbOf(N08_King  , them).IsSet(INVERSE_IF_WHITE20(them, E1)))
			&& GetPos.GetBbOf(N01_Pawn  , them).IsSet(INVERSE_IF_WHITE20(them, G3))
			&& GetPos.GetPiece(INVERSE_IF_WHITE20(them, H2)) == N00_Empty
			&& GetPos.GetPiece(INVERSE_IF_WHITE20(them, G2)) == N00_Empty
			&& GetPos.GetPiece(INVERSE_IF_WHITE20(them, G1)) == N00_Empty)
		{
			bishopInDangerFlag = (GetPos.GetTurn() == Black ? BlackBishopInDangerIn28 : WhiteBishopInDangerIn28);
			//tt.clear();
		}
		else if (GetPos.m_hand(GetPos.GetTurn()).Exists<HBishop>()
				 && GetPos.m_hand(them).Exists<HBishop>()
				 && GetPos.GetPiece(INVERSE_IF_WHITE20(them, C2)) == N00_Empty
				 && GetPos.GetPiece(INVERSE_IF_WHITE20(them, C1)) == N00_Empty
				 && GetPos.GetPiece(INVERSE_IF_WHITE20(them, D2)) == N00_Empty
				 && GetPos.GetPiece(INVERSE_IF_WHITE20(them, D1)) == N00_Empty
				 && GetPos.GetPiece(INVERSE_IF_WHITE20(them, A2)) == N00_Empty
				 && (ConvPiece::TO_PIECE_TYPE10(GetPos.GetPiece(INVERSE_IF_WHITE20(them, C3))) == N04_Silver
					 || ConvPiece::TO_PIECE_TYPE10(GetPos.GetPiece(INVERSE_IF_WHITE20(them, B2))) == N04_Silver)
				 && (ConvPiece::TO_PIECE_TYPE10(GetPos.GetPiece(INVERSE_IF_WHITE20(them, C3))) == N03_Knight
					 || ConvPiece::TO_PIECE_TYPE10(GetPos.GetPiece(INVERSE_IF_WHITE20(them, B1))) == N03_Knight)
				 && ((ConvPiece::TO_PIECE_TYPE10(GetPos.GetPiece(INVERSE_IF_WHITE20(them, E2))) == N07_Gold
					  && ConvPiece::TO_PIECE_TYPE10(GetPos.GetPiece(INVERSE_IF_WHITE20(them, E1))) == N08_King)
					 || ConvPiece::TO_PIECE_TYPE10(GetPos.GetPiece(INVERSE_IF_WHITE20(them, E1))) == N07_Gold))
		{
			bishopInDangerFlag = (GetPos.GetTurn() == Black ? BlackBishopInDangerIn78 : WhiteBishopInDangerIn78);
			//tt.clear();
		}
	}
}
#endif


/// <summary>
/// 
/// </summary>
/// <param name="DO"></param>
/// <param name="backUpSt"></param>
void Position::DoNullMove(bool DO, StateInfo& backUpSt) {
	assert(!inCheck());

	StateInfo* src = (DO ? m_st_ : &backUpSt);
	StateInfo* dst = (DO ? &backUpSt : m_st_);

	dst->m_boardKey      = src->m_boardKey;
	dst->m_handKey       = src->m_handKey;
	dst->m_pliesFromNull = src->m_pliesFromNull;
	dst->m_hand = GetHand(GetTurn());
	m_turn_ = ConvColor::OPPOSITE_COLOR10b(GetTurn());

	if (DO) {
		m_st_->m_boardKey ^= GetZobTurn();
		prefetch(GetConstOurCarriage()->m_tt.FirstEntry(m_st_->GetKey()));
		m_st_->m_pliesFromNull = 0;
		m_st_->m_continuousCheck[GetTurn()] = 0;
	}
	m_st_->m_hand = GetHand(GetTurn());

	assert(IsOK());
}


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
void RootMove::ExtractPvFromTT(Position& pos) {
	StateInfo state[g_maxPlyPlus2];
	StateInfo* st = state;
	TTEntry* tte;
	Ply ply = 0;
	Move m = m_pv_[0];

    // XXX: エラー出た分からん: assert(!m.IsNone() && pos.MoveIsPseudoLegal(m, false)); // XXX: なんか分からんから、MoveIsPseudoLegal の第二引数はとりあえず false にした。

	m_pv_.clear();

	do {
		m_pv_.push_back(m);

		assert(pos.MoveIsLegal(m_pv_[ply]));

		pos.GetTurn()==Color::Black
			?
			pos.DoMove<Color::Black,Color::White>(m_pv_[ply++], *st++)
			:
			pos.DoMove<Color::White,Color::Black>(m_pv_[ply++], *st++)
			;

		tte = pos.GetConstOurCarriage()->m_tt.Probe(pos.GetKey());
	} while (tte != nullptr
		// このチェックは少し無駄。駒打ちのときはmove16toMove() 呼ばなくて良い。
		&&
		(
			pos.GetTurn() == Color::Black
			?
			pos.MoveIsPseudoLegal<Color::Black,Color::White>(m = UtilMoveStack::Move16toMove(tte->GetMove(), pos))
			:
			pos.MoveIsPseudoLegal<Color::White,Color::Black>(m = UtilMoveStack::Move16toMove(tte->GetMove(), pos))
		)				
		   &&
				(
					pos.GetTurn()==Color::Black
					?
					pos.IsPseudoLegalMoveIsLegal<false, false,Color::Black,Color::White>(m, pos.GetPinnedBB())
					:
					pos.IsPseudoLegalMoveIsLegal<false, false,Color::White,Color::Black>(m, pos.GetPinnedBB())
					)
		   && ply < g_maxPly
		   && (!pos.IsRepetition(20) || ply < 6));

	m_pv_.push_back(g_MOVE_NONE);
	while (ply) {
		pos.UndoMove(m_pv_[--ply]);
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
void RootMove::InsertPvInTT(Position& pos) {
	StateInfo state[g_maxPlyPlus2];
	StateInfo* st = state;
	TTEntry* tte;
	Ply ply = 0;

	do {
		tte = pos.GetConstOurCarriage()->m_tt.Probe(pos.GetKey());

		if (tte == nullptr
			|| UtilMoveStack::Move16toMove(tte->GetMove(), pos) != m_pv_[ply])
		{
			pos.GetOurCarriage()->m_tt.Store(pos.GetKey(), ScoreNone, BoundNone, DepthNone, m_pv_[ply], ScoreNone);
		}

		assert(pos.MoveIsLegal(m_pv_[ply]));

		pos.GetTurn()==Color::Black
			?
			pos.DoMove<Color::Black,Color::White>(m_pv_[ply++], *st++)
			:
			pos.DoMove<Color::White,Color::Black>(m_pv_[ply++], *st++)
			;

	} while (!m_pv_[ply].IsNone());

	while (ply) {
		pos.UndoMove(m_pv_[--ply]);
	}
}


/// <summary>
/// 
/// </summary>
void initialize_10a300b_searchTable() {
	// todo: パラメータは改善の余地あり。

	g_reductions.Initialize();

	g_futilityMargins.Initialize();

	// initOptions futility move counts
	//int iDepth;  // depth (ONE_PLY == 2)
	for (int iDepth = 0; iDepth < 32; ++iDepth) {
		g_futilityMoveCounts.m_futilityMoveCounts[iDepth] = static_cast<int>(3.001 + 0.3 * pow(static_cast<double>(iDepth), 1.8));
	}
}


/// <summary>
/// 
/// </summary>
void OurCarriage::CheckTime() {
	if (m_limits.m_canPonder) { return; }

	s64 nodes = 0;
	if (m_limits.m_visitedNodesNum) {
		std::unique_lock<Mutex> lock(m_pub.m_mutex_);

		nodes = m_rootPosition.getNodesSearched();
		for (size_t i = 0; i < m_pub.m_monkies.size(); ++i) {
			for (int j = 0; j < m_pub.m_monkies[i]->m_splitedNodesSize; ++j) {
				SplitedNode& splitedNode = m_pub.m_monkies[i]->m_SplitedNodes[j];
				std::unique_lock<Mutex> spLock(splitedNode.m_mutex);
				nodes += splitedNode.m_nodes;
				u64 slvMask = splitedNode.m_slavesMask;
				while (slvMask) {
					const int index = firstOneFromLSB(slvMask);
					slvMask &= slvMask - 1;
					Position* pos = m_pub.m_monkies[index]->m_activePosition;
					if (pos != nullptr) {
						nodes += pos->getNodesSearched();
					}
				}
			}
		}
	}

	// 経過時間☆？
	const int elapsed = m_stopwatch.GetElapsed();

	// まだ最初の指し手☆？（＾～＾）？
	const bool isStillAtFirstMove =
		// 最初の指し手で☆
		m_signals.m_firstRootMove
		// フェイル・ロウではなくて☆？
		&& !m_signals.m_failedLowAtRoot
		&& m_timeMgr.IsTimeBudgetOver(elapsed);

	// これ以上の時間がないか☆？（＾ｑ＾）？
	const bool noMoreTime =
		m_timeMgr.IsNoMoreTime(TimerResolution , elapsed)
		|| isStillAtFirstMove;

	if (
		(m_limits.IsBrandnewTimeMgr() && noMoreTime)//反復深化探索をしたいときに、もう時間がない☆？（＾ｑ＾）
		||
		(m_limits.GetMoveTime() != 0 && m_limits.GetMoveTime() < elapsed)
		||
		(m_limits.m_visitedNodesNum != 0 && m_limits.m_visitedNodesNum < nodes)
	){
		m_signals.m_stop = true;
	}
}


/// <summary>
/// ワーカースレッド開始
/// </summary>
void Monkie::workAsMonkey() {
	SplitedNode* thisSp = m_splitedNodesSize ? m_activeSplitedNode : nullptr;
	assert(!thisSp || (thisSp->m_masterThread == this && m_isBeingSearched));

	while (true) {

		// ［手の空いてる猿は寝かす］フラグが立っているケースで。
		while ((!m_isBeingSearched && this->m_pOurCarriage->m_pub.m_isIdleMonkeyToSleep_) || m_isEndOfSearch)
		{
			if (m_isEndOfSearch) {
				assert(thisSp == nullptr);
				return;
			}

			std::unique_lock<Mutex> lock(m_sleepLock);
			if (thisSp != nullptr && !thisSp->m_slavesMask) { break; }

			if (!m_isBeingSearched && !m_isEndOfSearch) {
				m_sleepCond.wait(lock);
			}
		}

		if (m_isBeingSearched) {
			assert(!m_isEndOfSearch);

			this->m_pOurCarriage->m_pub.m_mutex_.lock();
			assert(m_isBeingSearched);
			SplitedNode* pSplitedNode = m_activeSplitedNode;
			this->m_pOurCarriage->m_pub.m_mutex_.unlock();

			Flashlight ss[g_maxPlyPlus2];
			Position pos(*pSplitedNode->m_position, this);

			memcpy(ss, pSplitedNode->m_pFlashlightBox - 1, 4 * sizeof(Flashlight));
			(ss+1)->m_splitedNode = pSplitedNode;

			pSplitedNode->m_mutex.lock();

			assert(m_activePosition == nullptr);

			m_activePosition = &pos;


			// スプリット・ポイント用の検索に変えるぜ☆（＾ｑ＾）
			pSplitedNode->m_pSword01->startSearch_asSplitedNode(
				*pSplitedNode, *this->m_pOurCarriage, pos, ss);


			assert(m_isBeingSearched);
			m_isBeingSearched = false;
			m_activePosition = nullptr;
			assert(pSplitedNode->m_slavesMask & (UINT64_C(1) << m_idx));
			pSplitedNode->m_slavesMask ^= (UINT64_C(1) << m_idx);
			pSplitedNode->m_nodes += pos.getNodesSearched();

			// ［手の空いてる猿は寝かす］フラグが立っているケースで
			if (this->m_pOurCarriage->m_pub.m_isIdleMonkeyToSleep_
				&& this != pSplitedNode->m_masterThread
				&& !pSplitedNode->m_slavesMask)
			{
				assert(!pSplitedNode->m_masterThread->m_isBeingSearched);
				pSplitedNode->m_masterThread->NotifyOne();
			}

			pSplitedNode->m_mutex.unlock();
		}

		if (thisSp != nullptr && !thisSp->m_slavesMask) {
			thisSp->m_mutex.lock();
			const bool finished = !thisSp->m_slavesMask;
			thisSp->m_mutex.unlock();
			if (finished) { return; }
		}
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="ssCmd"></param>
void OurCarriage::SetOption(std::istringstream& ssCmd) {
	std::string token;
	std::string name;
	std::string value;

	ssCmd >> token; // "name" が入力されるはず。

	ssCmd >> name;
	// " " が含まれた名前も扱う。
	while (ssCmd >> token && token != "value") {
		name += " " + token;
	}

	ssCmd >> value;
	// " " が含まれた値も扱う。
	while (ssCmd >> token) {
		value += " " + token;
	}

	if (!m_engineOptions.IsLegalOption(name)) {
		std::cout << "No such option: " << name << std::endl;
	}
	else {
		m_engineOptions[name] = value;
	}
}
