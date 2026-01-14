#include "../../header/n105_140_colorSq_/n105_140_ColorFileRank.h"


/// <summary>
/// 
/// </summary>
/// <param name="color"></param>
/// <param name="file"></param>
/// <param name="rank"></param>
ColorFileRank::ColorFileRank(Color color, File file, Rank rank)
{
	this->m_color = color;
	this->m_file = file;
	this->m_rank = rank;
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
int ColorFileRank::GetOrder()
{
	return this->m_color*10000 + this->m_file*100 + this->m_rank;
}
