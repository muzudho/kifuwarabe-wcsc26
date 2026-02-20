#pragma once

#include "../n113_piece___/n113_155_convPiece.hpp"
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../../src/lib_bitboard/n160_100_bitboard.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../../src/lib_toybox_base/char_to_piece_usi.hpp"
#include "../n225_movPhase/n225_050_generateMovePhase.hpp"
#include "../n223_move____/n223_060_stats.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"


using History = Stats<false>;


/// <summary>
/// 
/// </summary>
class NextmoveEvent {


public:


	/// <summary>
	/// 生成。
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="ttm"></param>
	/// <param name="depth"></param>
	/// <param name="history"></param>
	/// <param name="pFlashlightBox"></param>
	/// <param name="beta"></param>
	NextmoveEvent(
		const Position& pos,
		const Move ttm,
		const Depth depth,
		const History& history,
		Flashlight* pFlashlightBox,
		const Sweetness beta
	);
	NextmoveEvent(const Position& pos, Move ttm, const Depth depth, const History& history, const Square sq);
	NextmoveEvent(const Position& pos, const Move ttm, const History& history, const PieceType pt);


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Move GetNextMove_MonkeySplitedPlace();


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Move GetNextMove_NonMonkeySplitedPlace();


	/// <summary>
	/// 
	/// </summary>
	inline void IncrementCurMove() {
		++this->m_currMove_;
	};


	/// <summary>
	/// 
	/// </summary>
	inline void DecrementCurMove() {
		--this->m_currMove_;
	};


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	inline Move GetTranspositionTableMove() {
		return this->m_ttMove_;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	MoveStack* GetCurrMove() const { return this->m_currMove_; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	void SetCurrMove(MoveStack* value) { this->m_currMove_ = value; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	MoveStack* GetLastMove() const { return this->m_lastMove_; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	void SetLastMove(MoveStack* value) { this->m_lastMove_ = value; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	void SetLastMoveAndLastNonCaputre(MoveStack* value) {
		this->m_lastMove_ = value;
		this->m_lastNonCapture_ = value;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const Position& GetPos() const { return this->m_pos_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int GetCaptureThreshold() const { return this->m_captureThreshold_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	MoveStack* GetEndBadCaptures() const { return this->m_endBadCaptures_; }


	/// <summary>
	/// 
	/// </summary>
	void DecrementEndBadCaptures() { this->m_endBadCaptures_--; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	MoveStack* GetKillerMoves() const { return (MoveStack*)this->m_killerMoves_; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	MoveStack GetKillerMove(int index) const { return this->m_killerMoves_[index]; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Square GetRecaptureSquare()const { return this->m_recaptureSquare_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Depth GetDepth() const { return this->m_depth_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	MoveStack* GetLegalMoves() { return this->m_legalMoves_; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="value"></param>
	void SetPhase(GenerateMovePhase value) { this->m_phase_ = value; }


public:// もともと本当はプライベート・メソッド☆

	// template <bool IsDrop>
	// void NextmoveEvent::SweetnessNonCapturesMinusPro() {
	//
	//template <bool IsDrop> void SweetnessNonCapturesMinusPro();
	template <bool IsDrop>
	void SweetnessNonCapturesMinusPro() {
		for (MoveStack* curr = GetCurrMove(); curr != GetLastMove(); ++curr) {
			const Move move = curr->m_move;
			curr->m_sweetness =
				GetHistory().GetValue(IsDrop,
					ConvPiece::FROM_COLOR_AND_PIECE_TYPE10(GetPos().GetTurn(),
						(IsDrop ? move.GetPieceTypeDropped() : move.GetPieceTypeFrom())),
					move.To());
		}
	}


	/// <summary>
	/// 
	/// </summary>
	void SweetnessCaptures();


	/// <summary>
	/// [0] は番兵
	/// </summary>
	/// <returns></returns>
	MoveStack* GetFirstMove() { return &m_legalMoves_[1]; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	MoveStack* GetLastNonCapture() const { return m_lastNonCapture_; }


	/// <summary>
	/// 
	/// </summary>
	void SweetnessEvasions();


private:


	/// <summary>
	/// 
	/// </summary>
	void GoNextPhase();


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	GenerateMovePhase GetPhase() const { return m_phase_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const History& GetHistory() const { return m_history_; }


	/// <summary>
	/// 
	/// </summary>
	const Position&		m_pos_;

	/// <summary>
	/// 
	/// </summary>
	const History&		m_history_;

	/// <summary>
	/// サーチ・スタック☆
	/// </summary>
	Flashlight*			m_pFlashlightBox_;

	/// <summary>
	/// 
	/// </summary>
	Depth				m_depth_;

	/// <summary>
	/// transposition table move
	/// </summary>
	Move				m_ttMove_;

	/// <summary>
	/// 
	/// </summary>
	MoveStack			m_killerMoves_[2];

	/// <summary>
	/// 
	/// </summary>
	Square				m_recaptureSquare_;

	/// <summary>
	/// int で良いのか？
	/// </summary>
	int					m_captureThreshold_;

	/// <summary>
	/// 
	/// </summary>
	GenerateMovePhase	m_phase_;

	/// <summary>
	/// 
	/// </summary>
	MoveStack*			m_currMove_;

	/// <summary>
	/// 
	/// </summary>
	MoveStack*			m_lastMove_;

	/// <summary>
	/// 
	/// </summary>
	MoveStack*			m_lastNonCapture_;

	/// <summary>
	/// 
	/// </summary>
	MoveStack*			m_endBadCaptures_;

	/// <summary>
	/// std::array にした方が良さそう。
	/// </summary>
	MoveStack			m_legalMoves_[Move::m_MAX_LEGAL_MOVES];
};
