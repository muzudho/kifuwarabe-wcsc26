#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_100_color___/n105_100_500_convColor.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_120_square__/n105_120_150_file.hpp"
#include "../n105_120_square__/n105_120_155_convFile.hpp"
#include "../n105_120_square__/n105_120_200_rank.hpp"
#include "../n105_120_square__/n105_120_205_convRank.hpp"
#include "../n105_120_square__/n105_120_250_squareDelta.hpp"
#include "../n105_120_square__/n105_120_300_direction.hpp"


//────────────────────────────────────────────────────────────────────────────────
// マス番号の操作
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// マス番号の操作
/// </summary>
class ConvSquare {


public:


	/// <summary>
	///		<pre>
	/// 指定の駒（黒または白）の段の前に target があるか。
	///		</pre>
	/// </summary>
	/// <param name="us"></param>
	/// <param name="bRank"></param>
	/// <param name="wRank"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	static inline bool isInFrontOf_n10(Color us, Rank rankIfB, Rank rankIfW, const Rank target)
	{
		return (us == Color::Black ? (target < rankIfB) : (rankIfW < target));
	}


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <param name="bRank"></param>
	/// <param name="wRank"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	template<Color US>
	static inline bool isBehind_n10(Rank rankIfB, Rank rankIfW, const Rank target)
	{
		return (US == Black ? (rankIfB < target) : (target < rankIfW));
	}


	/// <summary>
	/// 未使用☆？
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <param name="bFile"></param>
	/// <param name="wFile"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	template<Color US>
	static inline bool isLeftOf_n10(File fileIfB, File fileIfW, const File target)
	{
		return (US == Black ? (fileIfB < target) : (target < fileIfW));
	}


	/// <summary>
	/// 未使用☆？
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <param name="bFile"></param>
	/// <param name="wFile"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	template<Color US>
	static inline bool isRightOf_n10(File fileIfB, File fileIfW, const File target)
	{
		return (US == Black ? (target < fileIfB) : (fileIfW < target));
	}


	/// <summary>
	/// s が Square の中に含まれているか判定
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	static inline bool containsOf_n10(const Square sq)
	{
		return (0 <= sq) && (sq < SquareNum);
	}


	/// <summary>
	/// File, Rank のどちらかがおかしいかも知れない時は、
	/// こちらを使う。
	/// こちらの方が遅いが、どんな File, Rank にも対応している。
	/// </summary>
	/// <param name="f"></param>
	/// <param name="r"></param>
	/// <returns></returns>
	static inline bool containsOf_n20(const File f, const Rank r)
	{
		return ConvFile::CONTAINS_OF10(f) && ConvRank::CONTAINS_OF10(r);
	}


	/// <summary>
	/// 速度が必要な場面で使用するなら、テーブル引きの方が有効だと思う。
	/// </summary>
	/// <param name="f"></param>
	/// <param name="r"></param>
	/// <returns></returns>
	static inline constexpr Square fromFileRank_n10(const File f, const Rank r)
	{
		return static_cast<Square>(static_cast<int>(f) * 9 + static_cast<int>(r));
	}


	/// <summary>
	/// 速度が必要な場面で使用する。
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	static inline Rank toRank_n10(const Square s)
	{
		assert(ConvSquare::containsOf_n10(s));
		// 計算せず、テーブル引き☆（＾ｑ＾）
		return g_squareToRank[s];
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	static inline File toFile_n10(const Square s)
	{
		assert(ConvSquare::containsOf_n10(s));
		return g_squareToFile[s];
	}


	/// <summary>
	/// 末尾の改行付きで☆
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	static inline std::string to2CharsNoString_USI40(const Square sq)
	{
		const Rank r = ConvSquare::toRank_n10(sq);
		const File f = ConvSquare::toFile_n10(sq);
		const char ch[] = { ConvFile::TO_CHAR_USI10(f), ConvRank::TO_CHAR_USI10(r), '\0' };
		return std::string(ch);
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	static inline std::string toString_CSA40(const Square sq)
	{
		const Rank r = ConvSquare::toRank_n10(sq);
		const File f = ConvSquare::toFile_n10(sq);
		const char ch[] = { ConvFile::TO_CHAR_CSA10(f), ConvRank::TO_CHAR_CSA10(r), '\0' };
		return std::string(ch);
	}


	/// <summary>
	/// 後手の位置を先手の位置へ変換
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	static inline constexpr Square inverse_n10(const Square sq)
	{
		return SquareNum - 1 - sq;
	}


	/// <summary>
	/// Square の左右だけ変換
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	static inline Square inverseFile_n40(const Square sq)
	{
		return ConvSquare::fromFileRank_n10(
			ConvFile::INVERSE10(
				ConvSquare::toFile_n10(sq)
			),
			ConvSquare::toRank_n10(sq)
		);
	}


	/// <summary>
	/// ビショップ・イン・デンジャーで使用☆
	/// </summary>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <returns></returns>
	static inline constexpr Square inverseIfWhite_n20(const Color c, const Square sq)
	{
		return (c == Black ? sq : inverse_n10(sq));
	}


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <param name="fromOrToRank"></param>
	/// <returns></returns>
	template<Color US>
	static inline bool canPromote_n10(const Rank fromOrToRank)
	{
#if 1
		static_assert(Black == 0, "");
		static_assert(Rank9 == 0, "");
		return static_cast<bool>(0x1c00007u & (1u << ((US << 4) + fromOrToRank)));
#else
		// 同じ意味。
		return (US == Black ? IsInFrontOf<Black, Rank6, Rank4>(fromOrToRank) : IsInFrontOf<White, Rank6, Rank4>(fromOrToRank));
#endif
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="c"></param>
	/// <param name="fromOrToRank"></param>
	/// <returns></returns>
	static inline bool canPromote_n10b(const Color c, const Rank fromOrToRank)
	{
#if 1
		static_assert(Black == 0, "");
		static_assert(Rank9 == 0, "");
		return static_cast<bool>(0x1c00007u & (1u << ((c << 4) + fromOrToRank)));
#else
		// 同じ意味。
		return (c == Black ? IsInFrontOf<Black, Rank6, Rank4>(fromOrToRank) : IsInFrontOf<White, Rank6, Rank4>(fromOrToRank));
#endif
	}
};


/// <summary>
/// 
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
static inline Square operator + (const Square lhs, const SquareDelta rhs) { return lhs + static_cast<Square>(rhs); }
static inline void operator += (Square& lhs, const SquareDelta rhs) { lhs = lhs + static_cast<Square>(rhs); }
static inline Square operator - (const Square lhs, const SquareDelta rhs) { return lhs - static_cast<Square>(rhs); }
static inline void operator -= (Square& lhs, const SquareDelta rhs) { lhs = lhs - static_cast<Square>(rhs); }
