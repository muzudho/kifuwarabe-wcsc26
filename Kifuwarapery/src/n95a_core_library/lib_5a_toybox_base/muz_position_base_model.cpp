//
// 📄 局面の状態を表すクラス
//
#include "muz_position_base_model.hpp"


// ========================================
// アクセッサ
// ========================================


/// <summary>
/// 
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
MuzHandModel MuzPositionBaseModel::GetHand(const Color c) const
{
	return this->m_hand_models_[c];
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
const MuzGameEngineStorageModel* MuzPositionBaseModel::GetConstGameEngineStore() const
{
	return this->gameEngineStore__;
}


/// <summary>
/// 
/// </summary>
/// <returns></returns>
MuzGameEngineStorageModel* MuzPositionBaseModel::GetGameEngineStore() const
{
	return this->gameEngineStore__;
}


/// <summary>
/// 
/// </summary>
/// <param name="s"></param>
void MuzPositionBaseModel::SetGameEngineStore(MuzGameEngineStorageModel* pGameEngineStore)
{
	this->gameEngineStore__ = pGameEngineStore;
}
