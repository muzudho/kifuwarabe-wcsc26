#pragma once
#include "../n080_common__/n080_085_prefetch.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ハッシュテーブル
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// よく使われているが何だろう？ 局面ハッシュに関係ある（＾～＾）？
/// </summary>
using Key = u64;


/// <summary>
/// ハッシュテーブル
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="Size">2のべき乗であること</typeparam>
template <typename T, size_t Size>
struct HashTable {


	/// <summary>
	/// 生成
	/// </summary>
	HashTable() {
		//entries_ = (T*)(boost::alignment::aligned_alloc(sizeof(T), sizeof(T)*Size));
		clear();
	}


	/// <summary>
	/// インデックス・アクセス
	/// </summary>
	/// <param name="k"></param>
	/// <returns></returns>
	T* operator [] (const Key k) { return entries_ + (static_cast<size_t>(k) & (Size - 1)); }


	/// <summary>
	/// クリアー
	/// </summary>
	void clear()
	{
		memset(entries_, 0, sizeof(T) * Size);
	}


	/// <summary>
	/// Size が 2のべき乗であることのチェック
	/// </summary>
	static_assert((Size& (Size - 1)) == 0, "");


private:


	/// <summary>
	/// ハッシュテーブルの中身の各項目。
	/// </summary>
	T entries_[Size];
	//T* entries_;
};
