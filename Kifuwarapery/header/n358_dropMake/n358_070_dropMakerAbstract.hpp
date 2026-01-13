#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_color___/n105_100_color.hpp"
#include "../n110_square__/n110_100_square.hpp"
#include "../n110_square__/n110_205_convRank.hpp"
#include "../n112_pieceTyp/n112_050_pieceType.hpp"
#include "../n160_board___/n160_100_bitboard.hpp"
#include "../n160_board___/n160_230_setMaskBB.hpp"
#include "../n160_board___/n160_600_bitboardAll.hpp"
#include "../n165_movStack/n165_500_moveStack.hpp"
#include "../n165_movStack/n165_600_convMove.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "n358_040_dropMakerEvent.hpp"


/// <summary>
/// 
/// </summary>
class DropMakerAbstract {


public:


	/// <summary>
    /// ９段目への打ち手を生成する。ただし桂馬、香車以外。
	/// </summary>
	/// <param name="pMovestack"></param>
	/// <param name="dmEvent"></param>
	/// <param name="haveHandArr"></param>
	/// <returns></returns>
	virtual MoveStack* MakeDropMovesToRank9ExceptNL(
		MoveStack* pMovestack,
		const DropMakerEvent& dmEvent,
		Move haveHandArr[6] // TODO: これ打ムーブにできないかだぜ☆？（＾ｑ＾）
	) const = 0;


	/// <summary>
    /// ８段目への打ち手を生成する。ただし桂馬以外。
	/// </summary>
	/// <param name="pMovestack"></param>
	/// <param name="dmEvent"></param>
	/// <param name="haveHandArr"></param>
	/// <returns></returns>
	virtual MoveStack* MakeDropMovesToRank8ExceptN(
		MoveStack* pMovestack,
		const DropMakerEvent& dmEvent,
		Move haveHandArr[6] // TODO: これ打ムーブにできないかだぜ☆？（＾ｑ＾）
	) const = 0;


	/// <summary>
    /// １〜７段目への打ち手を生成する。
	/// </summary>
	/// <param name="pMovestack"></param>
	/// <param name="dmEvent"></param>
	/// <param name="haveHandArr"></param>
	/// <returns></returns>
	virtual MoveStack* MakeDropMovesToRank1234567(
		MoveStack* pMovestack,
		const DropMakerEvent& dmEvent,
		Move haveHandArr[6] // TODO: これ打ムーブにできないかだぜ☆？（＾ｑ＾）
	) const = 0;
};
