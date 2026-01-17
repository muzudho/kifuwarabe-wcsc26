#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n480_tt______/n480_285_tTCluster.hpp"


/// <summary>
/// トランスポジション・テーブル☆（＾ｑ＾）
/// </summary>
class TranspositionTable {


public:


	/// <summary>
	/// 生成。
	/// </summary>
	TranspositionTable() : m_size_(0), m_entries_(nullptr), m_generation_(0) {}


	/// <summary>
	/// 破棄。
	/// </summary>
	~TranspositionTable() {
		delete[] m_entries_;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="mbSize">Mega Byte 指定</param>
	void SetSize(const size_t mbSize);


	/// <summary>
	/// 
	/// </summary>
	void Clear();


	/// <summary>
	/// 
	/// </summary>
	/// <param name="posKey"></param>
	/// <param name="score"></param>
	/// <param name="bound"></param>
	/// <param name="depth"></param>
	/// <param name="move"></param>
	/// <param name="evalScore"></param>
	void Store(const Key posKey, const ScoreNumber score, const Bound bound, Depth depth,
			   Move move, const ScoreNumber evalScore);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="posKey"></param>
	/// <returns></returns>
	TTEntry* Probe(const Key posKey) const;


	/// <summary>
	/// 
	/// </summary>
	void NewSearch() {
		++m_generation_;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="posKey"></param>
	/// <returns></returns>
	TTEntry* FirstEntry(const Key posKey) const {
		// (size() - 1) は置換表で使用するバイト数のマスク
		// posKey の下位 (size() - 1) ビットを hash key として使用。
		// ここで posKey の下位ビットの一致を確認。
		// posKey の上位32ビットとの一致は probe, store 内で確認するので、
		// ここでは下位32bit 以上が確認出来れば完璧。
		// 置換表のサイズを小さく指定しているときは下位32bit の一致は確認出来ないが、
		// 仕方ない。
		return m_entries_[posKey & (GetSize() - 1)].m_data;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="tte"></param>
	void Refresh(const TTEntry* tte) const {
		const_cast<TTEntry*>(tte)->SetGeneration(this->GetGeneration());
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	size_t GetSize() const {
		return m_size_;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	TTCluster* GetEntries() const { return m_entries_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	u8 GetGeneration() const { return m_generation_; }


private:


	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	TranspositionTable(const TranspositionTable&);


	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	TranspositionTable& operator = (const TranspositionTable&);


	/// <summary>
	/// 置換表のバイト数。2のべき乗である必要がある。
	/// </summary>
	size_t m_size_;

	/// <summary>
	/// 
	/// </summary>
	TTCluster* m_entries_;

	/// <summary>
	/// iterative deepening していくとき、過去の探索で調べたものかを判定する。
	/// </summary>
	u8 m_generation_;
};
