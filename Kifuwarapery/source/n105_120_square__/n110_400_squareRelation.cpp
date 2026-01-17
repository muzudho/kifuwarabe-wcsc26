#include "../../header/n105_120_square__/n105_120_400_squareRelation.hpp"
#include "../../header/n105_120_square__/n105_120_500_convSquare.hpp"


/// <summary>
/// ２つのマスの位置関係が［同筋］［同段］［同右肩上がり］［同右肩下がり］［その他］かを区別するビットボード（＾～＾）！
/// </summary>
SquareRelation g_squareRelation;


/// <summary>
/// ２つのマスの位置関係が［同筋］［同段］［同右肩上がり］［同右肩下がり］［その他］かを区別するビットボード（＾～＾）！
/// </summary>
void SquareRelation::Initialize()
{
	for (Square sq1 = I9; sq1 < SquareNum; ++sq1) {
		const File file1 = ConvSquare::ToFile_n10(sq1);
		const Rank rank1 = ConvSquare::ToRank_n10(sq1);
		for (Square sq2 = I9; sq2 < SquareNum; ++sq2) {
			const File file2 = ConvSquare::ToFile_n10(sq2);
			const Rank rank2 = ConvSquare::ToRank_n10(sq2);
			this->m_squareRelation_[sq1][sq2] = N00_DirecMisc;

			// 同マスはその他扱い
			if (sq1 == sq2) { continue; }

			// 同筋
			if (file1 == file2)
			{
				this->m_squareRelation_[sq1][sq2] = N02_DirecFile;
			}
			// 同段
			else if (rank1 == rank2)
			{
				this->m_squareRelation_[sq1][sq2] = N03_DirecRank;
			}
			// 同右肩上がり
			else if (static_cast<int>(rank1 - rank2) == static_cast<int>(file1 - file2))
			{
				this->m_squareRelation_[sq1][sq2] = N04_DirecDiagNESW;
			}
			// 同右肩下がり
			else if (static_cast<int>(rank1 - rank2) == static_cast<int>(file2 - file1))
			{
				this->m_squareRelation_[sq1][sq2] = N05_DirecDiagNWSE;
			}
			// その他
		}
	}
}
