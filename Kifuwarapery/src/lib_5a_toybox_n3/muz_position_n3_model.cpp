#include "muz_position_n3_model.hpp"


// ========================================
// 主要メソッド
// ========================================


bool MuzPositionN3Model::ParseBoard(std::string_view board_str)
{

	/*
	// 盤上の駒
	while (ss.get(token) && token != ' ') {
		if (isdigit(token)) {
			sq += SquareDelta::DeltaE * (token - '0');
		}
		else if (token == '/') {
			sq += (SquareDelta::DeltaW * 9) + SquareDelta::DeltaS;
		}
		else if (token == '+') {
			promoteFlag = Promoted;
		}
		else if (g_charToPieceUSI.IsLegalChar(token)) {
			if (ConvSquare::CONTAINS_OF10(sq)) {
				SetPiece(g_charToPieceUSI.GetValue(token) + promoteFlag, sq);
				promoteFlag = Piece::UnPromoted;
				sq += SquareDelta::DeltaE;
			}
			else {
				goto INCORRECT;
			}
		}
		else {
			goto INCORRECT;
		}
	}
	*/

	Square sq = A9;               // 仮の初期位置
	Piece promote = Piece::UnPromoted;

	for (char ch : board_str)
	{
		if (std::isdigit(ch))
		{
			sq = static_cast<Square>(
				static_cast<int>(sq) +
				static_cast<int>(SquareDelta::DeltaE) * (ch - '0')
				);
		}
		else if (ch == '/')
		{
			sq = static_cast<Square>(
				static_cast<int>(sq) +
				static_cast<int>(SquareDelta::DeltaW) * 9 +
				static_cast<int>(SquareDelta::DeltaS)
				);
		}
		else if (ch == '+')
		{
			promote = Piece::Promoted;
		}
		else if (g_charToPieceUSI.IsLegalChar(ch))
		{
			if (!ConvSquare::CONTAINS_OF10(sq)) return false;

			Piece p = (Piece)(g_charToPieceUSI.GetValue(ch) + promote);
			SetPiece(p, sq);

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
