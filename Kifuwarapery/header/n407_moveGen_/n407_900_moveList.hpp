#pragma once
#include "../n165_movStack/n165_300_movegenType.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n220_position/n220_665_utilMoveStack.hpp"
#include "../n250_pieceTyp/n350_030_makePromoteMove.hpp"
#include "n407_800_moveGenerator200.hpp"


/// <summary>
///		<pre>
/// 局面の（点数付き）指し手のコレクション
/// 
///		- 旧名： `ＭoveList`
///		</pre>
/// </summary>
/// <typeparam name="MT">指し手生成の区別</typeparam>
template <MovegenType MT>
class DeliciousBananaCollection
{


public:


	// ========================================
	// 軽い生成／破棄
	// ========================================


	/// <summary>
	/// 生成
	/// </summary>
	/// <param name="pos"></param>
	explicit DeliciousBananaCollection(const Position& pos) :
		// 指し手スタック
		m_curr_(m_deliciousBananaArray_),
		// 指し手生成
		m_last_(g_moveGenerator200.generateDeliciousBanana_n2(MT,m_deliciousBananaArray_, pos))
	{
	}


	// ========================================
	// 演算子のオーバーロード
	// ========================================


	/// <summary>
	/// 次の要素へ
	/// </summary>
	void operator ++ ()
	{
		++m_curr_;
	}


	// ========================================
	// メソッド
	// ========================================


	// クエスチョン・メソッド


	/// <summary>
	/// 最後の要素か
	/// </summary>
	/// <returns></returns>
	bool IsEnd() const { return (m_curr_ == m_last_); }


	/// <summary>
	/// 指し手を含むか
	/// </summary>
	/// <param name="move"></param>
	/// <returns></returns>
	bool Contains(const Move move) const {
		for (const DeliciousBanana* pDeliBanana(m_deliciousBananaArray_); pDeliBanana != m_last_; ++pDeliBanana) {
			if (pDeliBanana->m_move == move) {
				return true;
			}
		}
		return false;
	}


	// アクセッサ


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Move GetMove() const { return m_curr_->m_move; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t GetSize() const { return static_cast<size_t>(m_last_ - m_deliciousBananaArray_); }


private:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	/// ［指し手］と点数のペアの配列
	/// </summary>
	DeliciousBanana m_deliciousBananaArray_[Move::m_MAX_LEGAL_MOVES];

	/// <summary>
	/// 
	/// </summary>
	DeliciousBanana* m_curr_;

	/// <summary>
	/// 
	/// </summary>
	DeliciousBanana* m_last_;
};
