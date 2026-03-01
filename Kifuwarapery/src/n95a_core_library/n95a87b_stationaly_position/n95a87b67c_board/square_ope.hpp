//
// 📄 マスの操作
// 
//      - 循環参照を避けるため、マスの操作はここで定義する。
//

#pragma once

#include "../n95a87b79c_turn/color.hpp"
#include "squares.hpp"
#include <string>

/// <summary>
/// マス番号の操作
/// </summary>
class ConvSquare {


public:


    /// <summary>
    /// 先手のときは BRANK, 後手のときは WRANK より target が前の段にあるなら true を返す。
    /// </summary>
    /// <param name="us"></param>
    /// <param name="bRank"></param>
    /// <param name="wRank"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    static inline bool IS_IN_FRONT_OF10(Color us, Rank bRank, Rank wRank, const Rank target) {
        return (us == Color::Black ? (target < bRank) : (wRank < target));
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
    static inline bool IS_BEHIND10(Rank bRank, Rank wRank, const Rank target)
    {
        return (US == Black ? (bRank < target) : (target < wRank));
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
    static inline bool IS_LEFT_OF10(File bFile, File wFile, const File target) {
        return (US == Black ? (bFile < target) : (target < wFile));
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
    static inline bool IS_RIGHT_OF10(File bFile, File wFile, const File target) {
        return (US == Black ? (target < bFile) : (wFile < target));
    }


    /// <summary>
    /// s が Square の中に含まれているか判定
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    static inline bool CONTAINS_OF10(const Square s) {
        return (0 <= s) && (s < SquareNum);
    }


    /// <summary>
    /// File, Rank のどちらかがおかしいかも知れない時は、
    /// こちらを使う。
    /// こちらの方が遅いが、どんな File, Rank にも対応している。
    /// </summary>
    /// <param name="f"></param>
    /// <param name="r"></param>
    /// <returns></returns>
    static inline bool CONTAINS_OF20(const File f, const Rank r) {
        return ConvFile::CONTAINS_OF10(f) && ConvRank::CONTAINS_OF10(r);
    }


    /// <summary>
    /// 速度が必要な場面で使用するなら、テーブル引きの方が有効だと思う。
    /// </summary>
    /// <param name="f"></param>
    /// <param name="r"></param>
    /// <returns></returns>
    static inline constexpr Square FROM_FILE_RANK10(const File f, const Rank r) {
        return static_cast<Square>(static_cast<int>(f) * 9 + static_cast<int>(r));
    }


    /// <summary>
    /// 速度が必要な場面で使用する。
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    static inline Rank TO_RANK10(const Square s) {
        //assert(ConvSquare::CONTAINS_OF10(s));
        // 計算せず、テーブル引き☆（＾ｑ＾）
        return g_squareToRank[s];
    }


    /// <summary>
    /// 
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    static inline File TO_FILE10(const Square s) {
        //assert(ConvSquare::CONTAINS_OF10(s));
        return g_squareToFile[s];
    }


    /// <summary>
    /// 末尾の改行付きで☆
    /// </summary>
    /// <param name="sq"></param>
    /// <returns></returns>
    static inline std::string TO_2CHARS_N0_STRING_USI40(const Square sq) {
        const Rank r = ConvSquare::TO_RANK10(sq);
        const File f = ConvSquare::TO_FILE10(sq);
        const char ch[] = { ConvFile::TO_CHAR_USI10(f), ConvRank::TO_CHAR_USI10(r), '\0' };
        return std::string(ch);
    }


    /// <summary>
    /// 
    /// </summary>
    /// <param name="sq"></param>
    /// <returns></returns>
    static inline std::string TO_STRING_CSA40(const Square sq) {
        const Rank r = ConvSquare::TO_RANK10(sq);
        const File f = ConvSquare::TO_FILE10(sq);
        const char ch[] = { ConvFile::TO_CHAR_CSA10(f), ConvRank::TO_CHAR_CSA10(r), '\0' };
        return std::string(ch);
    }


    /// <summary>
    /// 後手の位置を先手の位置へ変換
    /// </summary>
    /// <param name="sq"></param>
    /// <returns></returns>
    static inline constexpr Square INVERSE10(const Square sq) {
        return (Square)(SquareNum - 1 - sq);
    }


    /// <summary>
    /// Square の左右だけ変換
    /// </summary>
    /// <param name="sq"></param>
    /// <returns></returns>
    static inline Square INVERSE_FILE40(const Square sq) {
        return ConvSquare::FROM_FILE_RANK10(
            ConvFile::INVERSE10(
                ConvSquare::TO_FILE10(sq)
            ),
            ConvSquare::TO_RANK10(sq)
        );
    }


    /// <summary>
    /// ビショップ・イン・デンジャーで使用☆
    /// </summary>
    /// <param name="c"></param>
    /// <param name="sq"></param>
    /// <returns></returns>
    static inline constexpr Square INVERSE_IF_WHITE20(const Color c, const Square sq) {
        return (c == Black ? sq : INVERSE10(sq));
    }


    /// <summary>
    /// 
    /// </summary>
    /// <typeparam name="US"></typeparam>
    /// <param name="fromOrToRank"></param>
    /// <returns></returns>
    template<Color US>
    static inline bool CAN_PROMOTE10(const Rank fromOrToRank) {
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
    static inline bool CAN_PROMOTE10b(const Color c, const Rank fromOrToRank) {
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

template<typename E>
constexpr auto underlying(E e) noexcept -> std::underlying_type_t<E> {
    return static_cast<std::underlying_type_t<E>>(e);
}

// sq + delta
constexpr Square operator+(Square sq, SquareDelta delta) noexcept {
    return static_cast<Square>(underlying(sq) + underlying(delta));
}

// sq += delta
constexpr Square& operator+=(Square& sq, SquareDelta delta) noexcept {
    sq = static_cast<Square>(underlying(sq) + underlying(delta));
    return sq;
}

// sq - delta
constexpr Square operator-(Square sq, SquareDelta delta) noexcept {
    return static_cast<Square>(underlying(sq) - underlying(delta));
}

// sq -= delta
constexpr Square& operator-=(Square& sq, SquareDelta delta) noexcept {
    sq = static_cast<Square>(underlying(sq) - underlying(delta));
    return sq;
}
