#pragma once

#include "../n165_movStack/n165_300_movegenType.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n374_genMove_/n374_040_pieceMoveEvent.hpp"
#include "../n374_genMove_/n374_350_PieceMovesGenerator.hpp"
#include "n405_070_mtAbstract.hpp"


/// <summary>
/// 
/// </summary>
class MovegenTypeCapture : public MovegenTypeAbstract{


public:


	/// <summary>
	///		<pre>
	/// 指し手生成 functor
	/// テンプレート引数が複数あり、部分特殊化したかったので、関数ではなく、struct にした。
	/// ALL == true のとき、歩、飛、角の不成、香の2段目の不成、香の3段目の駒を取らない不成も生成する。
	///		</pre>
	/// </summary>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="all"></param>
	/// <returns></returns>
	DeliciousBanana* GenerateMove(
		DeliciousBanana* pDeliBanana,
		const Position& pos,
		bool isAll = false) const override
	{
		// 黒番
		if (pos.getTurn()==Color::Black)
		{
			pDeliBanana = MovegenTypeCapture::GENERATE_MOVE_<Color::Black, Color::White>(pDeliBanana, pos, isAll);
		}
		// 白番
		else
		{
			pDeliBanana = MovegenTypeCapture::GENERATE_MOVE_<Color::White, Color::Black>(pDeliBanana, pos, isAll);
		}

		return pDeliBanana;
	}


private:


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <typeparam name="THEM"></typeparam>
	/// <param name="moveStackList"></param>
	/// <param name="pos"></param>
	/// <param name="all"></param>
	/// <returns></returns>
	template<Color US,Color THEM>
	static inline DeliciousBanana* GENERATE_MOVE_(DeliciousBanana* moveStackList, const Position& pos, bool all = false
		) {

		// Txxx は先手、後手の情報を吸収した変数。数字は先手に合わせている。
		const Rank TRank6 = (US == Black ? Rank6 : Rank4);
		const Rank TRank7 = (US == Black ? Rank7 : Rank3);
		const Rank TRank8 = (US == Black ? Rank8 : Rank2);
		const Bitboard TRank789BB = g_inFrontMaskBb.GetInFrontMask(US, TRank6);
		const Bitboard TRank1_6BB = g_inFrontMaskBb.GetInFrontMask(THEM, TRank7);
		const Bitboard TRank1_7BB = g_inFrontMaskBb.GetInFrontMask(THEM, TRank8);

		const Bitboard targetPawn = pos.GetBbOf10(THEM);
		const Bitboard targetOther = pos.GetBbOf10(THEM);
		const Square ksq = pos.GetKingSquare(THEM);


		// FIXME: 色をテンプレート化するのは良さげ☆
		const PieceMoveEvent pmEvent(MovegenType::N00_Capture, all, pos, ksq);
		moveStackList = PieceMovesGenerator::GeneratePieceMoves_N01_Pawn<US>(moveStackList, pmEvent, targetPawn);
		moveStackList = PieceMovesGenerator::GeneratePieceMoves_N02_Lance<US>(moveStackList, pmEvent, targetOther);
		moveStackList = PieceMovesGenerator::GeneratePieceMoves_N03_Knight<US>(moveStackList, pmEvent, targetOther);
		moveStackList = PieceMovesGenerator::GeneratePieceMoves_N04_Silver<US>(moveStackList, pmEvent, targetOther);
		moveStackList = PieceMovesGenerator::GeneratePieceMoves_N05_Bishop<US>(moveStackList, pmEvent, targetOther);
		moveStackList = PieceMovesGenerator::GeneratePieceMoves_N06_Rook<US>(moveStackList, pmEvent, targetOther);
		moveStackList = PieceMovesGenerator::GeneratePieceMoves_N16_GoldHorseDragon<US>(moveStackList, pmEvent, targetOther);
		moveStackList = PieceMovesGenerator::GeneratePieceMoves_N08_King<US>(moveStackList, pmEvent, targetOther);

		return moveStackList;
	}
};
