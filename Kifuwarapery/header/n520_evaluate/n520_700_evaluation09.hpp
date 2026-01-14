#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n080_150_overEnum/n080_150_500_overloadEnumOperators.hpp"
#include "../n105_140_colorSq_/n105_140_ColorFileRank.h"
#include "../n119_score___/n119_200_pieceScore.hpp"
#include "../n119_score___/n119_500_EvalSum.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n220_position/n220_750_charToPieceUSI.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"


/// <summary>
/// 134MB
/// </summary>
const size_t EvaluateTableSize = 0x400000;
//const size_t EvaluateTableSize = 0x10000000; // 8GB
//const size_t EvaluateTableSize = 0x20000000; // 17GB

using EvaluateHashEntry = EvalSum;
struct EvaluateHashTable : HashTable<EvaluateHashEntry, EvaluateTableSize> {};
extern EvaluateHashTable g_evalTable;


/// <summary>
/// 評価関数の本体だぜ☆（＾ｑ＾）
/// </summary>
class Evaluation09 {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	ScoreIndex evaluateUnUseDiff(const Position& pos);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="ss"></param>
	/// <returns></returns>
	ScoreIndex evaluate(Position& pos, Flashlight* ss);


private:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="index"></param>
	/// <returns></returns>
	EvalSum doapc(const Position& pos, const int index[2]);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="index"></param>
	/// <returns></returns>
	std::array<s32, 2> doablack(const Position& pos, const int index[2]);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="index"></param>
	/// <returns></returns>
	std::array<s32, 2> doawhite(const Position& pos, const int index[2]);


#if defined INANIWA_SHIFT
	/// <summary>
	/// 稲庭。
	/// </summary>
	/// <param name="GetPos"></param>
	/// <returns></returns>
	ScoreIndex inaniwaScoreBody(const Position& GetPos);


	/// <summary>
	/// 稲庭。
	/// </summary>
	/// <param name="GetPos"></param>
	/// <returns></returns>
	inline ScoreIndex inaniwaScore(const Position& GetPos);
#endif


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="ss"></param>
	/// <returns></returns>
	bool calcDifference(Position& pos, Flashlight* ss);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="list0"></param>
	/// <param name="list1"></param>
	/// <param name="nlist"></param>
	/// <returns></returns>
	int make_list_unUseDiff(const Position& pos, int list0[EvalList::m_ListSize], int list1[EvalList::m_ListSize], int nlist);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="ss"></param>
	void evaluateBody(Position& pos, Flashlight* ss);
};
