#pragma once
#include <algorithm>	//std::max
#include "../n119_score___/n119_090_ScoreValue.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n223_move____/n223_200_depth.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "n885_040_ourCarriage.hpp"	// FIXME:


/// <summary>
/// 静止探索の抽象クラス（＾▽＾）
/// </summary>
class AdventureBattlefieldQsearchAbstract {


public:


	/// <summary>
	///		<pre>
	/// Ｑサーチな大冒険（＾▽＾）！
	/// N01_PV か、N02_NonPV でだけ使うことができるぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="INCHECK"></param>
	/// <param name="pos"></param>
	/// <param name="ss"></param>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	/// <param name="depth"></param>
	/// <returns></returns>
	virtual ScoreValue ExploreAsQsearch(
		OurCarriage& ourCarriage,
		bool INCHECK,
		Position& pos,
		Flashlight* ss,
		ScoreValue alpha,
		ScoreValue beta,
		const Depth depth
		) const ;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void DoAssert(
		ScoreValue alpha,
		ScoreValue beta
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="alpha"></param>
	virtual inline void SetOldAlpha(
		ScoreValue& oldAlpha,
		ScoreValue alpha
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppTtEntry"></param>
	/// <param name="beta"></param>
	/// <param name="ttScore"></param>
	/// <returns></returns>
	virtual inline bool GetCondition01(
		const TTEntry** ppTtEntry,
		ScoreValue beta,
		ScoreValue ttScore
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="bestScore"></param>
	virtual inline void SetAlpha(
		ScoreValue& alpha,
		ScoreValue bestScore
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="INCHECK"></param>
	/// <param name="givesCheck"></param>
	/// <param name="move"></param>
	/// <param name="ttMove"></param>
	/// <param name="futilityScore"></param>
	/// <param name="futilityBase"></param>
	/// <param name="pos"></param>
	/// <param name="beta"></param>
	/// <param name="bestScore"></param>
	/// <param name="depth"></param>
	virtual inline void DoFutilityPruning01(
		bool& isContinue,
		bool& INCHECK,
		bool& givesCheck,
		Move& move,
		Move& ttMove,
		ScoreValue& futilityScore,
		ScoreValue& futilityBase,
		Position& pos,
		ScoreValue& beta,
		ScoreValue& bestScore,
		const Depth depth
		)const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="INCHECK"></param>
	/// <param name="evasionPrunable"></param>
	/// <param name="move"></param>
	/// <param name="ttMove"></param>
	/// <param name="pos"></param>
	virtual inline void DoContinue01(
		bool& isContinue,
		bool& INCHECK,
		bool& evasionPrunable,
		Move& move,
		Move& ttMove,
		Position& pos
		)const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isReturnWithScore"></param>
	/// <param name="returnScore"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="score"></param>
	/// <param name="beta"></param>
	/// <param name="alpha"></param>
	/// <param name="bestMove"></param>
	/// <param name="posKey"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="ttDepth"></param>
	/// <param name="move"></param>
	virtual inline void DoByNewScore(
		bool& isReturnWithScore,
		ScoreValue& returnScore,
		OurCarriage& ourCarriage,
		ScoreValue& score,
		ScoreValue& beta,
		ScoreValue& alpha,
		Move& bestMove,
		Key& posKey,
		Flashlight** ppFlashlight,
		Depth ttDepth,
		Move move
		)const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="bestScore"></param>
	/// <returns></returns>
	virtual inline Bound GetBound01(
		ScoreValue& oldAlpha,
		ScoreValue& bestScore
		)const = 0;
};
