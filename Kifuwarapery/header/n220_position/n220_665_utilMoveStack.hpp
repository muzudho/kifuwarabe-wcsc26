#pragma once

#include <algorithm> //std::swap std::max_element
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_160_pieceTyp/n105_160_500_pieceType.hpp"
#include "../n105_180_piece___/n105_180_105_convPieceType.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n220_position/n220_660_utilMovePos.hpp"


/// <summary>
/// 
/// </summary>
class UtilMoveStack {


public:


	/// <summary>
	/// 汎用的な insertion sort. 要素数が少ない時、高速にソートできる。
	/// 降順(大きいものが先頭付近に集まる)
	/// *(first - 1) に 番兵(sentinel) として MAX 値が入っていると仮定して高速化してある。
	/// T には ポインタかイテレータを使用出来る。
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <typeparam name="UseSentinel"></typeparam>
	/// <param name="first"></param>
	/// <param name="last"></param>
	template <typename T, bool UseSentinel = false>
	static inline void InsertionSort(T first, T last) {
		if (UseSentinel) {
			assert(std::max_element(first - 1, last) == first - 1); // 番兵が最大値となることを確認
		}
		if (first != last) {
			for (T curr = first + 1; curr != last; ++curr) {
				if (*(curr - 1) < *curr) {
					const auto tmp = std::move(*curr);
					do {
						*curr = *(curr - 1);
						--curr;
					} while ((UseSentinel || curr != first)
						&& *(curr - 1) < tmp);
					*curr = std::move(tmp);
				}
			}
		}
	}


	/// <summary>
	/// 最も score の高い moveStack のポインタを返す。
	/// MoveStack の数が多いとかなり時間がかかるので、
	/// 駒打ちを含むときに使用してはならない。
	/// </summary>
	/// <param name="currMove"></param>
	/// <param name="lastMove"></param>
	/// <returns></returns>
	static inline MoveStack* PickBest(MoveStack* currMove, MoveStack* lastMove) {
		std::swap(*currMove, *std::max_element(currMove, lastMove));
		return currMove;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="move"></param>
	/// <param name="pos"></param>
	/// <returns></returns>
	static inline Move Move16toMove(const Move move, const Position& pos) {
		if (move.IsNone()) {
			return g_MOVE_NONE;
		}
		if (move.IsDrop()) {
			return move;
		}
		const Square from = move.From();
		const PieceType ptFrom = ConvPiece::TO_PIECE_TYPE10(pos.GetPiece(from));
		return move | ConvMove::FROM_PIECETYPE_ONBOARD10(ptFrom) | UtilMovePos::GET_CAPTURED_PIECE_FROM_SQ(move.To(), pos);
	}
};
