#include "../../header/n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../../header/n480_tt______/n480_280_tTEntry.hpp"


/// <summary>
/// 
/// </summary>
/// <returns></returns>
u32 TTEntry::GetKey() const
{
	return this->m_key32_;
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
Depth TTEntry::GetDepth() const
{
	return static_cast<Depth>(this->m_depth16_);
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
Sweetness TTEntry::GetSweetness() const
{
	return static_cast<Sweetness>(this->m_sweetness16_);
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
Move TTEntry::GetMove() const
{
	return static_cast<Move>(this->m_move16_);
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
Bound TTEntry::GetBoundKind() const
{
	return static_cast<Bound>(this->m_bound_);
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
u8 TTEntry::GetGeneration() const
{
	return this->m_generation8_;
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
Sweetness TTEntry::GetEvalSweetness() const
{
	return static_cast<Sweetness>(this->m_evalSweetness_);
}


/// <summary>
/// 
/// </summary>
/// <param name="g"></param>
void TTEntry::SetGeneration(const u8 g)
{
	this->m_generation8_ = g;
}


/// <summary>
/// 
/// </summary>
/// <param name="depth"></param>
/// <param name="score"></param>
/// <param name="move"></param>
/// <param name="posKeyHigh32"></param>
/// <param name="bound"></param>
/// <param name="generation"></param>
/// <param name="evalScore"></param>
void TTEntry::SetSave(const Depth depth, const Sweetness score, const Move move, const u32 posKeyHigh32, const Bound bound, const u8 generation, const Sweetness evalScore)
{
	this->m_key32_ = posKeyHigh32;
	this->m_move16_ = static_cast<u16>(move.GetValue());
	this->m_bound_ = static_cast<u8>(bound);
	this->m_generation8_ = generation;
	this->m_sweetness16_ = static_cast<s16>(score);
	this->m_depth16_ = static_cast<s16>(depth);
	this->m_evalSweetness_ = static_cast<s16>(evalScore);
}
