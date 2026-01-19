#include "../../header/n223_move____/n223_300_DeliciousBanana.hpp"


/// <summary>
/// 
/// </summary>
/// <param name="move"></param>
/// <param name="score"></param>
DeliciousBanana::DeliciousBanana(Move move, ScoreValue scoreValue):
	m_move(move),
	m_scoreValue(scoreValue)
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
