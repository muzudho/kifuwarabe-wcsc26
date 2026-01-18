#pragma once


//────────────────────────────────────────────────────────────────────────────────
// 列挙型に演算子を追加（＾▽＾）
//────────────────────────────────────────────────────────────────────────────────


// enum 型に演算子を定義しています。
// 
//		- `T` は enum 型を渡してください。
//		- `#define` は複数行に渡って書くものではないから、末尾に `\` を付けて、次の行に続いているとみなしている。
#define OverloadEnumOperators(T)										\
	inline void operator += (T& lhs, const int rhs) { lhs  = static_cast<T>(static_cast<int>(lhs) + rhs); } \
	inline void operator += (T& lhs, const T   rhs) { lhs += static_cast<int>(rhs); } \
	inline void operator -= (T& lhs, const int rhs) { lhs  = static_cast<T>(static_cast<int>(lhs) - rhs); } \
	inline void operator -= (T& lhs, const T   rhs) { lhs -= static_cast<int>(rhs); } \
	inline void operator *= (T& lhs, const int rhs) { lhs  = static_cast<T>(static_cast<int>(lhs) * rhs); } \
	inline void operator /= (T& lhs, const int rhs) { lhs  = static_cast<T>(static_cast<int>(lhs) / rhs); } \
	inline constexpr T operator + (const T   lhs, const int rhs) { return static_cast<T>(static_cast<int>(lhs) + rhs); } \
	inline constexpr T operator + (const T   lhs, const T   rhs) { return lhs + static_cast<int>(rhs); } \
	inline constexpr T operator - (const T   lhs, const int rhs) { return static_cast<T>(static_cast<int>(lhs) - rhs); } \
	inline constexpr T operator - (const T   lhs, const T   rhs) { return lhs - static_cast<int>(rhs); } \
	inline constexpr T operator * (const T   lhs, const int rhs) { return static_cast<T>(static_cast<int>(lhs) * rhs); } \
	inline constexpr T operator * (const int lhs, const T   rhs) { return rhs * lhs; } \
	inline constexpr T operator * (const T   lhs, const T   rhs) { return lhs * static_cast<int>(rhs); } \
	inline constexpr T operator / (const T   lhs, const int rhs) { return static_cast<T>(static_cast<int>(lhs) / rhs); } \
	inline constexpr T operator - (const T   rhs) { return static_cast<T>(-static_cast<int>(rhs)); } \
	inline T operator ++ (T& lhs) { lhs += 1; return lhs; } /* 前置 */	\
	inline T operator -- (T& lhs) { lhs -= 1; return lhs; } /* 前置 */	\
	inline T operator ++ (T& lhs, int) { const T temp = lhs; lhs += 1; return temp; } /* 後置 */ \
	/* inline T operator -- (T& lhs, int) { const T temp = lhs; lhs -= 1; return temp; } */ /* 後置 */

