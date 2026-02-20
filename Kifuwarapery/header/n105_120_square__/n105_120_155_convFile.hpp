#pragma once

#include "../../src/lib_toybox_base/file.hpp"

//────────────────────────────────────────────────────────────────────────────────
// 列の操作
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 筋の数
/// </summary>
class ConvFile {


public:


	/// <summary>
	/// 左右変換
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	static inline constexpr File INVERSE10(const File f) { return FileNum - 1 - f; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	static inline bool CONTAINS_OF10(const File f) { return (0 <= f) && (f < FileNum); }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	static inline char TO_CHAR_USI10(const File f) { return '1' + f; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	static inline char TO_CHAR_CSA10(const File f) { return '1' + f; }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	static inline File FROM_CHAR_CSA10(const char c) { return static_cast<File>(c - '1'); }


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	static inline File FROM_CHAR_USI10(const char c) { return static_cast<File>(c - '1'); }
};
