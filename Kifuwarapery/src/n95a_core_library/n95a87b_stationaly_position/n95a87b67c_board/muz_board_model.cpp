#include "muz_board_model.hpp"
#include <cctype>   // これだけで std::isdigit(int ch) が使える


// ========================================
// 生成／破棄
// ========================================


MuzBoardModel::MuzBoardModel()
{
	// 盤面をクリアー（＾～＾）
	this->clear();
}


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// マスにある駒を取得
/// </summary>
/// <param name="sq">マス番号</param>
/// <returns></returns>
const Piece MuzBoardModel::get_piece(const Square sq) const
{
	return this->piece_[sq];
}


/// <summary>
/// マスに駒を置く。
/// </summary>
void MuzBoardModel::set_piece(const Square sq, const Piece piece)
{
	this->piece_[sq] = piece;
}


// ========================================
// 主要メソッド
// ========================================


bool MuzBoardModel::update_from_string(std::string_view board_str)
{
	// 盤面をクリアーしないといけない（＾～＾）
    this->clear();

	Square sq = M91;               // 先手から見て左上隅（９筋一段目）。SFENの最初のマス。オリジナルでは A9 だったが、わたしは M91 を入れるぜ（＾～＾）
	Piece promote = Piece::UnPromoted;

	for (char ch : board_str)
	{
		// 数値が入っていたら、その分だけ西へ進めだぜ（＾～＾）
		if (std::isdigit(ch))
		{
			sq = static_cast<Square>(
				static_cast<int>(sq) +
				static_cast<int>(SquareDelta::DeltaE) * (ch - '0'));
		}
        // 次の段の左端隅へ進めだぜ（＾～＾）つまり西に９マス、南に１マス進めだぜ（＾～＾）
		else if (ch == '/')
		{
			sq = static_cast<Square>(
				static_cast<int>(sq) +
				static_cast<int>(SquareDelta::DeltaW) * 9 +
				static_cast<int>(SquareDelta::DeltaS));
		}
        // 駒の前に「+」があったら、その駒は成っているぜ（＾～＾）
		else if (ch == '+')
		{
			promote = Piece::Promoted;
		}
		// 駒を表す文字なら（＾～＾）
		else if (g_charToPieceUSI.IsLegalChar(ch))
		{
            // 盤の外に飛び出てたらおかしいぜ（＾～＾）
			if (!ConvSquare::CONTAINS_OF10(sq)) return false;

			Piece p = (Piece)(g_charToPieceUSI.GetValue(ch) + promote);
			this->set_piece(sq, p);

			promote = Piece::UnPromoted;

			sq = static_cast<Square>(
				static_cast<int>(sq) +
				static_cast<int>(SquareDelta::DeltaE)
				);
		}
		else
		{
			return false;
		}
	}
	return true;
}
