#pragma once
#include <algorithm>	//std::max
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n223_move____/n223_200_depth.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"


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
	virtual Sweetness ExploreAsQsearch(
		MuzGameEngineStorageModel& ourCarriage,
		bool INCHECK,
		Position& pos,
		Flashlight* ss,
		Sweetness alpha,
		Sweetness beta,
		const Depth depth
		) const ;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="beta"></param>
	virtual inline void DoAssert(
		Sweetness alpha,
		Sweetness beta
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="oldAlpha"></param>
	/// <param name="alpha"></param>
	virtual inline void SetOldAlpha(
		Sweetness& oldAlpha,
		Sweetness alpha
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ppTtEntry"></param>
	/// <param name="beta"></param>
	/// <param name="ttSweetness"></param>
	/// <returns></returns>
	virtual inline bool GetCondition01(
		const TTEntry** ppTtEntry,
		Sweetness beta,
		Sweetness ttSweetness
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="alpha"></param>
	/// <param name="bestSweetness"></param>
	virtual inline void SetAlpha(
		Sweetness& alpha,
		Sweetness bestSweetness
		) const = 0;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="isContinue"></param>
	/// <param name="INCHECK"></param>
	/// <param name="givesCheck"></param>
	/// <param name="move"></param>
	/// <param name="ttMove"></param>
	/// <param name="futilitySweetness"></param>
	/// <param name="futilityBase"></param>
	/// <param name="pos"></param>
	/// <param name="beta"></param>
	/// <param name="bestSweetness"></param>
	/// <param name="depth"></param>
	virtual inline void DoFutilityPruning01(
		bool& isContinue,
		bool& INCHECK,
		bool& givesCheck,
		Move& move,
		Move& ttMove,
		Sweetness& futilitySweetness,
		Sweetness& futilityBase,
		Position& pos,
		Sweetness& beta,
		Sweetness& bestSweetness,
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
	/// <param name="isReturnWithSweetness"></param>
	/// <param name="returnSweetness"></param>
	/// <param name="ourCarriage">わたしたちの馬車</param>
	/// <param name="sweetness"></param>
	/// <param name="beta"></param>
	/// <param name="alpha"></param>
	/// <param name="bestMove"></param>
	/// <param name="posKey"></param>
	/// <param name="ppFlashlight"></param>
	/// <param name="ttDepth"></param>
	/// <param name="move"></param>
	virtual inline void doByNewSweetness(
		bool& isReturnWithSweetness,
		Sweetness& returnSweetness,
		MuzGameEngineStorageModel& ourCarriage,
		Sweetness& sweetness,
		Sweetness& beta,
		Sweetness& alpha,
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
	/// <param name="bestSweetness"></param>
	/// <returns></returns>
	virtual inline Bound GetBound01(
		Sweetness& oldAlpha,
		Sweetness& bestSweetness
		)const = 0;
};
