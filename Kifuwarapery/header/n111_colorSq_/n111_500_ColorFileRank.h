#pragma once

#include "../../src/lib_toybox_base/color.hpp"
#include "../../src/lib_toybox_base/file.hpp"
#include "../../src/lib_toybox_base/rank.hpp"


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
