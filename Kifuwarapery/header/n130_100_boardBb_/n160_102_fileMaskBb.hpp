#pragma once
#include "../n105_120_square__/n105_120_150_file.hpp"
#include "../n105_120_square__/n105_120_500_convSquare.hpp"
#include "../n130_100_boardBb_/n160_100_bitboard.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード　＞　筋のマスク
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 列を指すビットボード
/// </summary>
class FileMaskBb {


public:


	/// <summary>
	/// 
	/// </summary>
	const Bitboard m_I = Bitboard(UINT64_C(0x1ff) << (9 * 0), 0);
	const Bitboard m_H = Bitboard(UINT64_C(0x1ff) << (9 * 1), 0);
	const Bitboard m_G = Bitboard(UINT64_C(0x1ff) << (9 * 2), 0);
	const Bitboard m_F = Bitboard(UINT64_C(0x1ff) << (9 * 3), 0);
	const Bitboard m_E = Bitboard(UINT64_C(0x1ff) << (9 * 4), 0);
	const Bitboard m_D = Bitboard(UINT64_C(0x1ff) << (9 * 5), 0);
	const Bitboard m_C = Bitboard(UINT64_C(0x1ff) << (9 * 6), 0);
	const Bitboard m_B = Bitboard(0, 0x1ff << (9 * 0));
	const Bitboard m_A = Bitboard(0, 0x1ff << (9 * 1));

	/// <summary>
	/// 
	/// </summary>
	const Bitboard m_fileMask[FileNum] = {
		this->m_I,
		this->m_H,
		this->m_G,
		this->m_F,
		this->m_E,
		this->m_D,
		this->m_C,
		this->m_B,
		this->m_A
	};


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	inline Bitboard GetFileMask(const File f) const {
		return this->m_fileMask[f];
	}


	/// <summary>
	/// 直接テーブル引きすべきだと思う。
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	inline Bitboard GetSquareFileMask(const Square sq) const {
		const File f = ConvSquare::TO_FILE10(sq);
		return this->GetFileMask(f);
	}
};


/// <summary>
/// クラス定義のあとに書くとビルドできるぜ☆（＾ｑ＾）
/// </summary>
extern const FileMaskBb g_fileMaskBb;
