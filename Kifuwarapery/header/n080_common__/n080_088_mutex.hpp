#pragma once
#include "../n080_common__/n080_087_random.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ミューテックス
//────────────────────────────────────────────────────────────────────────────────


#if defined _WIN32 && !defined _MSC_VER
#ifndef NOMINMAX
#define NOMINMAX
#endif

#define WIN32_LEAN_AND_MEAN

// FIXME: C++14 から C++17 へ上げたいので、なるべくファイルの冒頭に定義したい。
#include <windows.h>

#undef WIN32_LEAN_AND_MEAN
#undef NOMINMAX


/// <summary>
/// ミューテックス
/// </summary>
struct Mutex {


	/// <summary>
	/// 生成
	/// </summary>
	Mutex() { InitializeCriticalSection(&cs); }


	/// <summary>
	/// 破棄
	/// </summary>
	~Mutex() { DeleteCriticalSection(&cs); }


	/// <summary>
	/// ロック
	/// </summary>
	void lock() { EnterCriticalSection(&cs); }


	/// <summary>
	/// アンロック
	/// </summary>
	void unlock() { LeaveCriticalSection(&cs); }


private:


	/// <summary>
	/// 
	/// </summary>
	CRITICAL_SECTION cs;
};


/// <summary>
/// 条件変数
/// </summary>
using ConditionVariable = std::condition_variable_any;


#else
/// <summary>
/// ミューテックス（Mutex 型）は標準のものを使う
/// </summary>
using Mutex = std::mutex;

/// <summary>
/// 条件変数は標準のものを使う
/// </summary>
using ConditionVariable = std::condition_variable;
#endif
