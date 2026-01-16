#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n220_position/n220_650_position.hpp" //FIXME:


//class Position;


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class IBonaDirectable {


public:


	/// <summary>
	/// インターフェースのメソッド
	/// </summary>
	/// <param name="squareDistance"></param>
	/// <param name="sq0"></param>
	/// <param name="sq1"></param>
	virtual void InitializeSquareDistance(SquareDistance& squareDistance, Square sq0, Square sq1) const = 0;


	/// <summary>
	///		<pre>
	/// インターフェースのメソッド
	/// 
	///		- checkerBb を調べるためのもの。
	///		- 第一引数の position は更新にも使う。
	///			- 返り値を `std::unique_ptr<Bitboard>` 型の checkerBB にするのも試してみたが、探索が止まってしまった。
	///		</pre>
	/// </summary>
	/// <param name="position"></param>
	/// <param name="from"></param>
	/// <param name="ksq"></param>
	/// <param name="us"></param>
	virtual void Do2Move(Position& position, Square from, const Square ksq, const Color us) const = 0;
};
