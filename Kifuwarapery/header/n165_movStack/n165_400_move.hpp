#pragma once

#include <string>
#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n105_120_square__/n105_120_100_square.hpp"
#include "../../header/n105_120_square__/n105_120_500_convSquare.hpp"
#include "../../header/n112_pieceTyp/n112_050_pieceType.hpp"
#include "../../header/n113_piece___/n113_200_handPiece.hpp"
#include "../../header/n113_piece___/n113_205_convHandPiece.hpp"




/// <summary>
///		<pre>
/// 指し手を表すクラス
/// 
///		xxxxxxxx xxxxxxxx xxxxxxxx x1111111  移動先
///		xxxxxxxx xxxxxxxx xx111111 1xxxxxxx  移動元。駒打ちの際には、PieceType + SquareNum - 1
///		xxxxxxxx xxxxxxxx x1xxxxxx xxxxxxxx  1 なら成り
///		xxxxxxxx xxxx1111 xxxxxxxx xxxxxxxx  移動する駒の PieceType 駒打ちの際には使用しない。
///		xxxxxxxx 1111xxxx xxxxxxxx xxxxxxxx  取られた駒の PieceType
///
///		todo: piece to move と captured piece は指し手としてパックする必要あるの？
///		      from, to , promo だけだったら、16bit で済む。
///			</pre>
/// </summary>
class Move {


public:


	/// <summary>
	/// 生成
	/// </summary>
	Move();

	explicit Move(const u32 u) : m_value(u) {}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="m"></param>
	/// <returns></returns>
	Move& operator = (const Move& m) { m_value = m.m_value; return *this; }

	Move& operator = (const volatile Move& m) { m_value = m.m_value; return *this; }

	// volatile Move& 型の *this を返すとなぜか警告が出るので、const Move& 型の m を返すことにする。
	const Move& operator = (const Move& m) volatile { m_value = m.m_value; return m; }

	Move(const Move& m) { m_value = m.m_value; }

	Move(const volatile Move& m) { m_value = m.m_value; }


	/// <summary>
	/// 移動先
	/// </summary>
	/// <returns></returns>
	Square To() const;


	/// <summary>
	/// 移動元
	/// </summary>
	/// <returns></returns>
	Square From() const;


	/// <summary>
	/// 移動元、移動先
	/// </summary>
	/// <returns></returns>
	u32 FromAndTo() const;


	/// <summary>
	/// 成り、移動元、移動先
	/// </summary>
	/// <returns></returns>
	u32 ProFromAndTo() const;


	/// <summary>
	/// 取った駒の種類
	/// </summary>
	/// <returns></returns>
	PieceType GetCap() const;


	/// <summary>
	/// 成るかどうか
	/// </summary>
	/// <returns></returns>
	u32 IsPromotion() const;


	/// <summary>
	/// 移動する駒の種類
	/// </summary>
	/// <returns></returns>
	PieceType GetPieceTypeFrom() const;


	/// <summary>
	/// 移動した後の駒の種類
	/// </summary>
	/// <returns></returns>
	PieceType GetPieceTypeTo() const;


	/// <summary>
	///		<pre>
	/// 移動前の PieceType を引数に取り、移動後の PieceType を返す。
	/// 高速化の為、ptFrom が確定しているときに使用する。
	///		</pre>
	/// </summary>
	/// <param name="ptFrom"></param>
	/// <returns></returns>
	PieceType GetPieceTypeTo(const PieceType ptFrom) const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool IsDrop() const;


	/// <summary>
	/// 0xf00000 は 取られる駒のマスク
	/// </summary>
	/// <returns></returns>
	bool IsCapture() const;


	/// <summary>
	/// 0xf04000 は 取られる駒と成のマスク
	/// </summary>
	/// <returns></returns>
	bool IsCaptureOrPromotion() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool IsCaptureOrPawnPromotion() const;


	/// <summary>
	/// 打つ駒の種類
	/// </summary>
	/// <returns></returns>
	PieceType GetPieceTypeDropped() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	PieceType GetPieceTypeFromOrDropped() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	HandPiece GetHandPieceDropped() const;


	/// <summary>
	/// 値が入っているか。
	/// </summary>
	/// <returns></returns>
	bool IsNone() const;


	/// <summary>
	/// メンバ変数 value_ の取得
	/// </summary>
	/// <returns></returns>
	u32 GetValue() const;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="rhs"></param>
	/// <returns></returns>
	Move operator |= (const Move rhs);

	Move operator | (const Move rhs) const;

	bool operator == (const Move rhs) const;
	bool operator != (const Move rhs) const;
	bool operator < (const Move rhs) const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::string GetPromoteFlagToStringUSI() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::string ToUSI() const;


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::string ToCSA() const;


public:


	/// <summary>
	///		<pre>
	/// position sfen R8/2K1S1SSk/4B4/9/9/9/9/9/1L1L1L3 b PLNSGBR17p3n3g 1
	/// の局面が最大合法手局面で 593 手。番兵の分、+ 1 しておく。
	///		</pre>
	/// </summary>
	static const int m_MAX_LEGAL_MOVES = 593 + 1;

	/// <summary>
	/// 成りフラグ
	/// </summary>
	static const u32 m_PROMOTE_FLAG = 1 << 14;

	/// <summary>
	/// 
	/// </summary>
	static const u32 m_NONE = 0;

	/// <summary>
	/// 
	/// </summary>
	static const u32 m_NULL = 129;

	/// <summary>
	///		<pre>
	/// for learn
	/// 
	/// 学習時に、正解の手のPV、その他の手のPVを MoveNone で区切りながら 1 次元配列に格納していく。
	/// 格納するその他のPVの最後に MovePVsEnd を格納する。それをフラグに次の指し手に遷移する。
	/// 正解のPV, MoveNone, その他0のPV, MoveNone, その他1のPV, MoveNone, MovePVsEnd という感じに並ぶ。
	///		</pre>
	/// </summary>
	static const u32 m_PVS_END = 1 << 15;


private:


	/// <summary>
	/// 
	/// </summary>
	u32 m_value;
};


//────────────────────────────────────────────────────────────────────────────────
// 非クラスメンバ 静的グローバル・オブジェクト
//────────────────────────────────────────────────────────────────────────────────

/// <summary>
/// 成りフラグ
/// </summary>
static const Move g_MOVE_PROMOTE_FLAG = Move(Move::m_PROMOTE_FLAG);

/// <summary>
/// 
/// </summary>
static const Move g_MOVE_NONE = Move(Move::m_NONE);

/// <summary>
/// 
/// </summary>
static const Move g_MOVE_NULL = Move(Move::m_NULL);

/// <summary>
/// PVs end
/// </summary>
static const Move g_MOVE_PVS_END = Move(Move::m_PVS_END);
