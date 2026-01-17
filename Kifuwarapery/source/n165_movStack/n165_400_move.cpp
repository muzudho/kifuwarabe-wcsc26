#include <string>
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n105_120_square__/n105_120_100_square.hpp"
#include "../../header/n105_120_square__/n105_120_155_convFile.hpp"
#include "../../header/n105_120_square__/n105_120_205_convRank.hpp"
#include "../../header/n105_120_square__/n105_120_500_convSquare.hpp"
#include "../../header/n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../../header/n105_180_piece___/n105_180_105_convPieceType.hpp"
#include "../../header/n105_180_piece___/n105_180_200_handPiece.hpp"
#include "../../header/n165_movStack/n165_400_move.hpp"


/// <summary>
/// デフォルト・コンストラクタは空っぽだぜ☆（＾ｑ＾）
/// </summary>
Move::Move()
{
}


/// <summary>
/// 移動先マス。
/// </summary>
/// <returns></returns>
Square Move::To() const
{
	return static_cast<Square>((this->GetValue() >> 0) & 0x7f);
}


/// <summary>
/// 移動元マス。
/// </summary>
/// <returns></returns>
Square Move::From() const
{
	return static_cast<Square>((this->GetValue() >> 7) & 0x7f);
}


/// <summary>
/// 移動元、移動先
/// </summary>
/// <returns></returns>
u32 Move::FromAndTo() const
{
	return (this->GetValue() >> 0) & 0x3fff;
}


/// <summary>
/// 成り、移動元、移動先
/// </summary>
/// <returns></returns>
u32 Move::ProFromAndTo() const
{
	return (this->GetValue() >> 0) & 0x7fff;
}


/// <summary>
/// 取った駒。
/// </summary>
/// <returns></returns>
PieceType Move::GetCap() const
{
	return static_cast<PieceType>((this->GetValue() >> 20) & 0xf);
}


/// <summary>
/// 成ったか。
/// </summary>
/// <returns></returns>
u32 Move::IsPromotion() const
{
	return this->GetValue() & m_PROMOTE_FLAG;
}


/// <summary>
/// 移動元の駒種類。
/// </summary>
/// <returns></returns>
PieceType Move::GetPieceTypeFrom() const
{
	return static_cast<PieceType>((this->GetValue() >> 16) & 0xf);
}


/// <summary>
/// 移動先の駒種類。
/// </summary>
/// <returns></returns>
PieceType Move::GetPieceTypeTo() const
{
	return (this->IsDrop() ? this->GetPieceTypeDropped() : this->GetPieceTypeTo(this->GetPieceTypeFrom()));
}


/// <summary>
/// 移動先の駒種類。
/// </summary>
/// <param name="ptFrom"></param>
/// <returns></returns>
PieceType Move::GetPieceTypeTo(const PieceType ptFrom) const
{
	// これらは同じ意味。
#if 1
	return (ptFrom + static_cast<PieceType>((this->GetValue() & m_PROMOTE_FLAG) >> 11));
#else
	return (IsPromotion()) ? ptFrom + PTPromote : ptFrom;
#endif
}


/// <summary>
/// 打か。
/// </summary>
/// <returns></returns>
bool Move::IsDrop() const
{
	return this->From() >= 81;
}


/// <summary>
/// 駒を取ったか。
/// </summary>
/// <returns></returns>
bool Move::IsCapture() const
{
	return (this->GetValue() & 0xf00000) ? true : false;
}


/// <summary>
/// 駒を取ったか、または成ったか。
/// </summary>
/// <returns></returns>
bool Move::IsCaptureOrPromotion() const
{
	return (this->GetValue() & 0xf04000) ? true : false;
}


/// <summary>
/// 駒を取ったか、または歩の成りか。
/// </summary>
/// <returns></returns>
bool Move::IsCaptureOrPawnPromotion() const
{
	return this->IsCapture() || (this->IsPromotion() && this->GetPieceTypeFrom() == PieceType::N01_Pawn);
}


/// <summary>
/// 打つ駒の種類。
/// </summary>
/// <returns></returns>
PieceType Move::GetPieceTypeDropped() const
{
	return static_cast<PieceType>(this->From() - Square::SquareNum + 1);
}


/// <summary>
/// 移動元の駒種類、または打つ駒の種類。
/// </summary>
/// <returns></returns>
PieceType Move::GetPieceTypeFromOrDropped() const
{
	return (this->IsDrop() ? this->GetPieceTypeDropped() : this->GetPieceTypeFrom());
}


/// <summary>
/// 打つ駒の種類。
/// </summary>
/// <returns></returns>
HandPiece Move::GetHandPieceDropped() const
{
	assert(this->IsDrop());
	return ConvHandPiece::FromPieceType(this->GetPieceTypeDropped());
}


/// <summary>
/// 値が入っていないか。
/// </summary>
/// <returns></returns>
bool Move::IsNone() const
{
	return GetValue() == Move::m_NONE;
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
u32 Move::GetValue() const
{
	return this->m_value;
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Move Move::operator|=(const Move rhs)
{
	this->m_value |= rhs.GetValue();
	return *this;
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Move Move::operator|(const Move rhs) const
{
	return Move(*this) |= rhs;
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
bool Move::operator==(const Move rhs) const
{
	return this->GetValue() == rhs.GetValue();
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
bool Move::operator!=(const Move rhs) const
{
	return !(*this == rhs);
}


/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
bool Move::operator<(const Move rhs) const
{
	return this->GetValue() < rhs.GetValue();
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
std::string Move::GetPromoteFlagToStringUSI() const
{
	return (this->IsPromotion() ? "+" : "");
}


/// <summary>
/// (^q^)エイプリーはストリング型だったんだが、なのは風のキャラ配列に変えてみるぜ☆
/// </summary>
/// <returns></returns>
std::string Move::ToUSI() const {

	// （Ａ）指さないとき☆（＾ｑ＾）
	if (this->IsNone()) {
		return "None";
	}
	// （Ｂ）無いとき☆（＾ｑ＾）
	// 未設定ムーブはない。
	//
	// （Ｃ）持ち駒のとき
	else if (this->IsDrop()) {
		const Square to = this->To();

		// （＾ｑ＾）2の倍数がいいのか☆？ｗｗ なのははバッファーサイズを 8byte にしていたが、
		// 構わず　きつきつ　にしてみようぜ☆ｗｗｗｗ
		char buf[5];//8

		// （イ）持ち駒の種類☆（＾ｑ＾）
		buf[0] = g_CONV_HAND_PIECE_1CHAR_TABLE[this->GetHandPieceDropped()];

		// （ロ）持ち駒を打つ表示☆（＾ｑ＾）
		buf[1] = '*';

		// （ハ）移動先の筋☆（＾ｑ＾）
		buf[2] = ConvFile::TO_CHAR_USI10(ConvSquare::toFile_n10(to));

		// （ニ）移動先の段☆（＾ｑ＾）
		buf[3] = ConvRank::TO_CHAR_USI10(ConvSquare::toRank_n10(to));

		// （ホ）終端子☆
		buf[4] = '\0';

		return std::string(buf);
	}
	// （Ｄ）成りのとき
	else if (this->IsPromotion()) {

		const Square to = this->To();
		const Square from = this->From();

		// （＾ｑ＾）2の倍数がいいのか☆？ｗｗ なのははバッファーサイズを 8byte にしていたが、
		// 構わず　きつきつ　にしてみようぜ☆ｗｗｗｗ
		char buf[6];//8

		// （イ）移動元の筋☆（＾ｑ＾）
		buf[0] = ConvFile::TO_CHAR_USI10(ConvSquare::toFile_n10(from));

		// （ロ）移動元の段☆（＾ｑ＾）
		buf[1] = ConvRank::TO_CHAR_USI10(ConvSquare::toRank_n10(from));

		// （ハ）移動先の筋☆（＾ｑ＾）
		buf[2] = ConvFile::TO_CHAR_USI10(ConvSquare::toFile_n10(to));

		// （ニ）移動先の段☆（＾ｑ＾）
		buf[3] = ConvRank::TO_CHAR_USI10(ConvSquare::toRank_n10(to));

		// （ホ）成りだぜ☆（＾ｑ＾）
		buf[4] = '+';

		// （へ）終端子☆
		buf[5] = '\0';

		return std::string(buf);
	}
	// （Ｅ）成らないとき
	else
	{
		const Square to = this->To();
		const Square from = this->From();

		// （＾ｑ＾）2の倍数がいいのか☆？ｗｗ なのははバッファーサイズを 8byte にしていたが、
		// 構わず　きつきつ　にしてみようぜ☆ｗｗｗｗ
		char buf[5];//8

		// （イ）移動元の筋☆（＾ｑ＾）
		buf[0] = ConvFile::TO_CHAR_USI10(ConvSquare::toFile_n10(from));

		// （ロ）移動元の段☆（＾ｑ＾）
		buf[1] = ConvRank::TO_CHAR_USI10(ConvSquare::toRank_n10(from));

		// （ハ）移動先の筋☆（＾ｑ＾）
		buf[2] = ConvFile::TO_CHAR_USI10(ConvSquare::toFile_n10(to));

		// （ニ）移動先の段☆（＾ｑ＾）
		buf[3] = ConvRank::TO_CHAR_USI10(ConvSquare::toRank_n10(to));

		// （ホ）終端子☆
		buf[4] = '\0';

		return std::string(buf);
	}
}


/// <summary>
///
/// </summary>
/// <returns></returns>
std::string Move::ToCSA() const {

	if (this->IsNone()) { return "None"; }

	std::string s = (
		this->IsDrop() ?
		std::string("00") :
		ConvSquare::toString_CSA40(this->From())
	);

	// 移動先の筋☆（＾ｑ＾）
	// 移動先の段☆（＾ｑ＾）
	s += ConvSquare::toString_CSA40(this->To()) +
		// 駒の種類☆（＾ｑ＾）
		ConvPieceType::GET_STRING(this->GetPieceTypeTo());

	return s;
}
