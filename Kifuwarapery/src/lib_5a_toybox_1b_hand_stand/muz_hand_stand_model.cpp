#include "muz_hand_stand_model.hpp"


// ========================================
// アクセッサー
// ========================================


unsigned int MuzHandStandModel::get_count(const HandPiece handPiece) const
{
    switch (handPiece)
    {
    case HPawn:  return pawn_;
    case HLance: return lance_;
    case HKnight:return knight_;
    case HSilver:return silver_;
    case HGold:  return gold_;
    case HBishop:return bishop_;
    case HRook:  return rook_;
    default:
        // XXX: ここは本来は例外を投げるべきだが、今回はとりあえず0を返す
        return 0;
    }
}
void MuzHandStandModel::set_count(const HandPiece handPiece, unsigned int count)
{
    switch (handPiece)
    {
    case HPawn:  pawn_ = count; break;
    case HLance: lance_ = count; break;
    case HKnight:knight_ = count; break;
    case HSilver:silver_ = count; break;
    case HGold:  gold_ = count; break;
    case HBishop:bishop_ = count; break;
    case HRook:  rook_ = count; break;
    default:
        // XXX: ここは本来は例外を投げるべきだが、今回はとりあえず0を返す
        break;
    }
}
