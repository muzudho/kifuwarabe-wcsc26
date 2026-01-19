#include "../../header/n223_move____/n223_300_DeliciousBanana.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="move"></param>
/// <param name="sweetness"></param>
DeliciousBanana::DeliciousBanana(Move move, Sweetness sweetness):
	m_move(move),
	m_sweetness(sweetness)
{
}


/// <summary>
/// 
/// </summary>
/// <param name=""></param>
/// <returns></returns>
Move DeliciousBanana::GetMove(void)
{
	return this->m_move;
}
