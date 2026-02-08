#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"


//────────────────────────────────────────────────────────────────────────────────
// ビットボード
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
///		<pre>
/// 将棋盤（ビットボード）
/// 
///		- ２つのバイトで表現
///		</pre>
/// </summary>
class Bitboard {


private:


#if defined (HAVE_SSE2) || defined (HAVE_SSE4)
	union {
		u64 m_part_[2];
		__m128i m_m_;
	};
#else
	/// <summary>
	/// m_part_[0] : 先手から見て、1一から7九までを縦に並べたbit. 63bit使用. right と呼ぶ。
	/// m_part_[1] : 先手から見て、8一から1九までを縦に並べたbit. 18bit使用. left  と呼ぶ。
	/// </summary>
	u64 m_part_[2];
#endif


public:


#if defined (HAVE_SSE2) || defined (HAVE_SSE4)
	/// <summary>
	/// 
	/// </summary>
	/// <param name="rhs"></param>
	/// <returns></returns>
	Bitboard& operator = (const Bitboard& rhs) {
		_mm_store_si128(&this->m_m_, rhs.m_m_);
		return *this;
	}
	Bitboard(const Bitboard& bb) {
		_mm_store_si128(&this->m_m_, bb.m_m_);
	}
#endif


	/// <summary>
	/// 
	/// </summary>
	Bitboard() {}

	Bitboard(const u64 v0, const u64 v1);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	u64 GetP(const int index) const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="index"></param>
	/// <param name="val"></param>
	void SetP(const int index, const u64 val);

	/// <summary>
	/// マジックナンバーを作るのに使う☆
	/// </summary>
	/// <returns></returns>
	u64 MergeP() const;

	/// <summary>
	/// どこかにビットが立っていれば真☆(IsNot0)
	/// </summary>
	/// <returns></returns>
	bool Exists1Bit() const;

	/// <summary>
	/// 高速化をラッピング☆ これはコードが見難くなるけど仕方ない。
	/// </summary>
	/// <param name="bb"></param>
	/// <returns></returns>
	bool AndIsNot0( const Bitboard& bb)const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	Bitboard operator ~ () const;

	Bitboard operator &= (const Bitboard& rhs);

	Bitboard operator |= (const Bitboard& rhs);

	Bitboard operator ^= (const Bitboard& rhs);

	Bitboard operator <<= (const int i);

	Bitboard operator >>= (const int i);

	Bitboard operator & (const Bitboard& rhs) const;

	Bitboard operator | (const Bitboard& rhs) const;

	Bitboard operator ^ (const Bitboard& rhs) const;

	Bitboard operator << (const int i) const;

	Bitboard operator >> (const int i) const;

	bool operator == (const Bitboard& rhs) const;

	bool operator != (const Bitboard& rhs) const;


	/// <summary>
	/// 高速化をラッピング☆ これはコードが見難くなるけど仕方ない。
	/// </summary>
	/// <param name="bb"></param>
	/// <returns></returns>
	Bitboard AndEqualNot(const Bitboard& bb);


	/// <summary>
	/// 高速化をラッピング☆ これはコードが見難くなるけど仕方ない。
	/// </summary>
	/// <param name="bb"></param>
	/// <returns></returns>
	Bitboard NotThisAnd(const Bitboard& bb) const;


	/// <summary>
	///		<pre>
	/// Bitboard の right 側だけの要素を調べて、最初に 1 であるマスの index を返す。
	/// そのマスを 0 にする。
	/// Bitboard の right 側が 0 でないことを前提にしている。
	///		</pre>
	/// </summary>
	/// <returns></returns>
	FORCE_INLINE Square PopFirstOneRightOfBoard() {
		const Square sq = static_cast<Square>(firstOneFromLSB(this->GetP(0)));
		// LSB 側の最初の 1 の bit を 0 にする
		this->m_part_[0] &= this->GetP(0) - 1;
		return sq;
	}


	/// <summary>
	///		<pre>
	/// Bitboard の left 側だけの要素を調べて、最初に 1 であるマスの index を返す。
	/// そのマスを 0 にする。
	/// Bitboard の left 側が 0 でないことを前提にしている。
	///		</pre>
	/// </summary>
	FORCE_INLINE Square PopFirstOneLeftOfBoard() {
		const Square sq = static_cast<Square>(firstOneFromLSB(this->GetP(1)) + 63);
		// LSB 側の最初の 1 の bit を 0 にする
		this->m_part_[1] &= this->GetP(1) - 1;
		return sq;
	}


	/// <summary>
	///		<pre>
	/// Bitboard を I9 から A1 まで調べて、最初に 1 であるマスの index を返す。
	/// そのマスを 0 にする。
	/// Bitboard が allZeroBB() でないことを前提にしている。
	/// VC++ の _BitScanForward() は入力が 0 のときに 0 を返す仕様なので、
	/// 最初に 0 でないか判定するのは少し損。
	///		</pre>
	/// </summary>
	FORCE_INLINE Square PopFirstOneFromI9()
	{
		if (this->GetP(0)) {
			return PopFirstOneRightOfBoard();
		}
		return PopFirstOneLeftOfBoard();
	}


	/// <summary>
	/// 返す位置を 0 にしないバージョン。
	/// </summary>
	/// <returns></returns>
	FORCE_INLINE Square GetFirstOneRightFromI9() const
	{
		return static_cast<Square>(firstOneFromLSB(this->GetP(0)));
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	FORCE_INLINE Square GetFirstOneLeftFromB9() const
	{
		return static_cast<Square>(firstOneFromLSB(this->GetP(1)) + 63);
	}


	/// <summary>
	/// 最初の１つを取得☆（＾～＾）？
	/// </summary>
	/// <returns></returns>
	FORCE_INLINE Square GetFirstOneFromI9() const
	{
		if (this->GetP(0)) {
			return GetFirstOneRightFromI9();
		}
		return GetFirstOneLeftFromB9();
	}


	/// <summary>
	/// Bitboard の 1 の bit を数える。
	/// Crossover は、MergeP() すると 1 である bit が重なる可能性があるなら true
	/// </summary>
	/// <typeparam name="Crossover"></typeparam>
	/// <returns></returns>
	template <bool Crossover = true>
	int PopCount() const {
		return (Crossover ? count1s(GetP(0)) + count1s(GetP(1)) : count1s(MergeP()));
	}


	/// <summary>
	/// bit が 1 つだけ立っているかどうかを判定する。
	/// Crossover は、MergeP() すると 1 である bit が重なる可能性があるなら true
	/// </summary>
	/// <typeparam name="Crossover"></typeparam>
	/// <returns></returns>
	template <bool Crossover = true>
	bool IsOneBit() const {
#if defined (HAVE_SSE42)
		return (this->PopCount<Crossover>() == 1);
#else
		if (!this->Exists1Bit()) {
			return false;
		}
		else if (this->GetP(0)) {
			return !((this->GetP(0) & (this->GetP(0) - 1)) | this->GetP(1));
		}
		return !(this->GetP(1) & (this->GetP(1) - 1));
#endif
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="part"></param>
	void PrintTable(const int part) const;


	/// <summary>
	/// 指定した位置が Bitboard のどちらの u64 変数の要素か
	/// </summary>
	/// <param name="sq"></param>
	/// <returns></returns>
	static int Part(const Square sq);


public://(^q^)


	/// <summary>
	/// 実際に使用する部分の全て bit が立っている Bitboard
	/// </summary>
	/// <returns></returns>
	static inline Bitboard CreateAllOneBB() {
		return Bitboard(UINT64_C(0x7fffffffffffffff), UINT64_C(0x000000000003ffff));
	}


	static inline Bitboard CreateAllZeroBB() { return Bitboard(0, 0); }


public://(^q^)


#if defined HAVE_BMI2
	/// <summary>
	/// PEXT bitboard.
	/// </summary>
	/// <param name="mask"></param>
	/// <returns></returns>
	inline u64 OccupiedToIndex( const Bitboard& mask) const {
		return _pext_u64(this->MergeP(), mask.MergeP());
	}

#else
	/// <summary>
	/// magic bitboard.
	/// magic number を使って block の模様から利きのテーブルへのインデックスを算出
	/// </summary>
	/// <param name="magic"></param>
	/// <param name="shiftBits"></param>
	/// <returns></returns>
	inline u64 OccupiedToIndex( const u64 magic, const int shiftBits) const {
		return (this->MergeP() * magic) >> shiftBits;
	}
#endif


	/// <summary>
	/// Bitboard で直接利きを返す関数。
	/// 1段目には歩は存在しないので、1bit シフトで別の筋に行くことはない。
	/// ただし、from に歩以外の駒の Bitboard を入れると、別の筋のビットが立ってしまうことがあるので、
	/// 別の筋のビットが立たないか、立っても問題ないかを確認して使用すること。
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <param name="thisBitboard"></param>
	/// <returns></returns>
	template <Color US>
	static inline Bitboard PawnAttack(const Bitboard& thisBitboard) { // thisはfrom
		return (US == Black ? (thisBitboard >> 1) : (thisBitboard << 1));
	}
	static inline Bitboard PawnAttack(const Bitboard& thisBitboard, Color US) { // thisはfrom
		return (US == Black ? (thisBitboard >> 1) : (thisBitboard << 1));
	}

};


/// <summary>
/// (^q^)追加☆
/// </summary>
extern Bitboard g_nullBitboard;
