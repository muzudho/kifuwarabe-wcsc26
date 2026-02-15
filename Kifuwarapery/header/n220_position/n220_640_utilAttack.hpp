#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../../src/lib_toybox_base/square.hpp"
#include "../../src/lib_toybox_base/piece_type.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"


/// <summary>
/// 
/// </summary>
class UtilAttack {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <typeparam name="US"></typeparam>
	/// <param name="pType"></param>
	/// <param name="sq"></param>
	/// <param name="occupied"></param>
	/// <returns></returns>
	template<const Color US>
	static inline Bitboard GetAttacksFrom(const PieceType pType, const Square sq, const Bitboard& occupied) {//const																														  
		const PieceTypeEvent ptEvent1(occupied, US, sq);
		return PiecetypePrograms::m_PIECETYPE_PROGRAMS[pType]->GetAttacks2From(ptEvent1);// FIXME: 配列の範囲チェックをしてないぜ☆（＾ｑ＾）
	}


	/// <summary>
	/// TODO: inline にするには、positon と utilAttackの依存関係の解消が必要☆？（＾ｑ＾）
	///static
	///inline
	/// </summary>
	/// <param name="pt"></param>
	/// <param name="c"></param>
	/// <param name="sq"></param>
	/// <param name="occupied"></param>
	/// <returns></returns>
	static Bitboard GetAttacksFrom(const PieceType pt, const Color c, const Square sq, const Bitboard& occupied);//const
};


//extern UtilAttack g_utilAttack;
