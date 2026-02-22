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


// ========================================
// 主要メソッド
// ========================================


/// <summary>
///		<pre>
/// 局面をセットします。
/// sfen 形式の文字列を解析して、盤上の駒の配置、手番、持ち駒、次の手数などを Position クラスのメンバ変数に設定します。
/// また、ゲームエンジンのストレージモデルもセットします。
/// 解析に失敗した場合はエラーメッセージを出力します。
///		</pre>
/// </summary>
/// <param name="sfen"></param>
void MuzPositionBaseModel::Set(const std::string& sfen)
{
	Piece promoteFlag = UnPromoted;
	std::istringstream ss(sfen);
	char token;
	Square sq = A9;

	MuzGameEngineStorageModel* s = std::move(gameEngineStore__);
	this->Clear();
	this->SetGameEngineStore(s);

	// 盤上の駒
	while (ss.get(token) && token != ' ') {
		if (isdigit(token)) {
			sq += SquareDelta::DeltaE * (token - '0');
		}
		else if (token == '/') {
			sq += (SquareDelta::DeltaW * 9) + SquareDelta::DeltaS;
		}
		else if (token == '+') {
			promoteFlag = Promoted;
		}
		else if (g_charToPieceUSI.IsLegalChar(token)) {
			if (ConvSquare::CONTAINS_OF10(sq)) {
				SetPiece(g_charToPieceUSI.GetValue(token) + promoteFlag, sq);
				promoteFlag = Piece::UnPromoted;
				sq += SquareDelta::DeltaE;
			}
			else {
				goto INCORRECT;
			}
		}
		else {
			goto INCORRECT;
		}
	}

	// 手番
	while (ss.get(token) && token != ' ')
	{
		if (token == 'b') {
			this->m_turn_ = Black;
		}
		else if (token == 'w') {
			this->m_turn_ = White;
		}
		else {
			goto INCORRECT;
		}
	}

	// 持ち駒
	for (int digits = 0; ss.get(token) && token != ' '; ) {
		if (token == '-') {
			memset(m_hand_models_, 0, sizeof(m_hand_models_));
		}
		else if (isdigit(token)) {
			digits = digits * 10 + token - '0';
		}
		else if (g_charToPieceUSI.IsLegalChar(token)) {
			// 持ち駒を32bit に pack する
			const Piece piece = g_charToPieceUSI.GetValue(token);
			this->SetHand(piece, (digits == 0 ? 1 : digits));

			digits = 0;
		}
		else {
			goto INCORRECT;
		}
	}

	// 次の手が何手目か
	ss >> this->m_gamePly_;
	this->m_gamePly_ = std::max(2 * (this->m_gamePly_ - 1), 0) + static_cast<int>(this->GetTurn() == White);

	return;
INCORRECT:
	std::cout << "incorrect SFEN string : " << sfen << std::endl;
}
