#pragma once

#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_100_square.hpp"
#include "../n105_200_sqDistan/n105_200_500_squareDistance.hpp"
#include "../n220_position/n220_650_position.hpp" //FIXME:


//class Position;


/// <summary>
/// Bonanzaで使われている［向き］。
/// </summary>
class BonaDirAbstract {


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
	///		- FIXME: checkerBb を返り値にすれば、 Position& position は要らないのでは？
	///		</pre>
	/// </summary>
	/// <param name="position"></param>
	/// <param name="from"></param>
	/// <param name="ksq"></param>
	/// <param name="us"></param>
	/// <returns>checkerBB</returns>
	virtual Bitboard* Do2Move(Position& position, Square from, const Square ksq, const Color us) const = 0;
};
