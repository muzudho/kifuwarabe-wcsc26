#pragma once

#include "../n080_common__/n080_100_common.hpp"	//u32
#include "../n105_color___/n105_100_color.hpp"
#include "../n119_score___/n119_090_scoreIndex.hpp"	//Ply


/// <summary>
///		<pre>
/// 元の名前：ＬｉｍｉｔｓＴｙｐｅ
/// 時間や探索深さの制限を格納する為の構造体
///		</pre>
/// </summary>
class LimitsOfThinking {


public:


	/// <summary>
	/// 生成。
	/// </summary>
	LimitsOfThinking() {
		//memset(this, 0, sizeof(LimitsOfThinking));
	}


	/// <summary>
	///		<pre>
	/// 元の名前：　ｕｓｅＴｉｍｅＭａｎａｇｅｍｅｎｔ
	/// 時間管理が新品かどうか☆（＾ｑ＾）？
	/// 反復深化探索に潜るために真であることが必要☆
	///		</pre>
	/// </summary>
	/// <returns></returns>
	bool IsBrandnewTimeManagement() const {
		// 以下の全てが 0 の場合に真☆？（＾ｑ＾）
		return !(
			this->m_depth
			|
			this->m_nodes01
			|
			this->GetMoveTime()
			|
			static_cast<int>(this->m_infinite)
			);
	}


	/// <summary>
	/// 深さ☆？
	/// </summary>
	Ply m_depth = 0;

	/// <summary>
	/// 
	/// </summary>
	u32 m_nodes01 = 0;

	/// <summary>
	/// 
	/// </summary>
	bool m_infinite = false;

	/// <summary>
	/// 相手の思考時間中に、自分も思考するか☆？（＾ｑ＾）
	/// </summary>
	bool m_ponder = false;


public:


	/// <summary>
	/// 多分、フィッシャータイムの追加時間☆？（＾ｑ＾）
	/// </summary>
	int m_increment[g_COLOR_NUM] = { 0 };


	/// <summary>
    /// 多分、フィッシャータイムの追加時間を取得する☆？（＾ｑ＾）
	/// </summary>
	/// <param name="us"></param>
	/// <returns></returns>
	inline int GetIncrement(Color us) const {
		return this->m_increment[us];
	}


	/// <summary>
    ///		<pre>
	/// 残り時間だぜ☆（＾ｑ＾）
	/// 元の名前：ｔｉｍｅ
	/// ミリ秒単位だぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	int m_nokoriTime[g_COLOR_NUM] = { 0 };


	/// <summary>
	/// 
	/// </summary>
	/// <param name="us"></param>
	/// <returns></returns>
	inline int GetNokoriTime(Color us)const {
		return this->m_nokoriTime[us];
	}


	/// <summary>
	/// btime, wtime コマンドをそのまま受け取るぜ☆（＾ｑ＾）
	/// </summary>
	/// <param name="us"></param>
	/// <param name="ssCmd"></param>
	inline void SetNokoriTimeByStream(Color us, std::istringstream& ssCmd) {
		ssCmd >> this->m_nokoriTime[us];
	}


	//────────────────────────────────────────────────────────────────────────────────
	// ムーブス・ツー・ゴーって何☆？（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	// FIXME: movesToGo というプロパティを持っていたが、"movesToGo" なんていうコマンドは USI から飛んでこないと思ったので削除したぜ☆（＾ｑ＾）
	// 時間管理の movesToGo の最大値だったみたいだぜ☆


	/// <summary>
	/// ムーブタイムって何☆？（＾ｑ＾）
	/// </summary>
	/// <returns></returns>
	inline int GetMoveTime() const {
		return this->m_moveTime_;
	}


	/// <summary>
	/// 思考開始時、初期化を行った際にある条件下で０クリアする☆？
	/// </summary>
	inline void ZeroClearMoveTime() {
		this->m_moveTime_ = 0;
	}


	/// <summary>
	/// ポンダーヒットをしたときに、ムーブタイムが０でなければ、消費した時間分、加算するのに使います。
	/// </summary>
	/// <param name="value"></param>
	inline void IncreaseMoveTime(int value) {
		this->m_moveTime_ += value;
	}


	/// <summary>
	/// go byoyomi 等の場合に、マージン分減らすのに使う☆？
	/// </summary>
	/// <param name="value"></param>
	inline void DecrementMoveTime(int value) {
		this->m_moveTime_ -= value;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ssCmd"></param>
	inline void SetMoveTimeFromStream(std::istringstream& ssCmd) {
		ssCmd >> this->m_moveTime_;
	}


private:


	/// <summary>
	/// ☆？ ポンダー・ヒットの経過時間が足しこまれる☆？（＾ｑ＾）
	/// 秒読みマージンは引かれる☆
	/// </summary>
	int m_moveTime_ = 0;
};
