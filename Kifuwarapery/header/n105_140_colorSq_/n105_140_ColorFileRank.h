#pragma once
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n105_120_square__/n105_120_150_file.hpp"
#include "../n105_120_square__/n105_120_200_rank.hpp"


//────────────────────────────────────────────────────────────────────────────────
// 手番、筋、段
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// 手番、筋、段
/// </summary>
class ColorFileRank {


public:


	/// <summary>
	/// 
	/// </summary>
	Color m_color;

	/// <summary>
	/// 
	/// </summary>
	File m_file;

	/// <summary>
	/// 
	/// </summary>
	Rank m_rank;


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="color"></param>
	/// <param name="file"></param>
	/// <param name="rank"></param>
	ColorFileRank(Color color, File file, Rank rank);

	/// <summary>
	/// ソート用の数字。
	/// </summary>
	/// <returns></returns>
	int GetOrder();
};
