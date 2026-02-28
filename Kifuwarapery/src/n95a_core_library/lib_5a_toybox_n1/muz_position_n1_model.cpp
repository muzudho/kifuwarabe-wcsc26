//
// 📄 局面の状態を表すクラス
//
#include "muz_position_n1_model.hpp"


// ========================================
// 生成／破棄
// ========================================


MuzPositionN1Model::MuzPositionN1Model()
{
	// 盤上を空っぽにするぜ（＾～＾）
    this->board_ = MuzBoardModel{};
}


// ========================================
// アクセッサ
// ========================================


void MuzPositionN1Model::SetStartPosRadixHalfPly(const RadixHalfPly radix_half_ply)
{
	this->ply_obj_.set_radix_half_ply(radix_half_ply);
}


RadixHalfPly MuzPositionN1Model::GetRadixHalfPly()
{
	return this->ply_obj_.get_radix_half_ply();
}


Color MuzPositionN1Model::GetTurn()
{
	return this->turn_.get_color();
}
