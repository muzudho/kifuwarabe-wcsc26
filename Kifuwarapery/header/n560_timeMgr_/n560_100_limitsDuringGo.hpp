#pragma once
#include "../n080_100_sysWorld/n080_100_500_common.hpp"	//u32
#include "../n105_100_color___/n105_100_100_color.hpp"
#include "../n210_score___/n119_090_scoreIndex.hpp"	//Ply


/// <summary>
///		<pre>
/// 時間や探索深さの制限を格納する為の構造体
/// 
///		- 元の名前：ＬｉｍｉｔｓＴｙｐｅ。
///		- `go` コマンドが呼び出されるたびに生成されるぜ（＾～＾）
///		</pre>
/// </summary>
class LimitsDuringGo {


public:


	// ========================================
	// 生成／破棄
	// ========================================


	/// <summary>
	/// 生成。
	/// </summary>
	LimitsDuringGo() {
		//memset(this, 0, sizeof(LimitsDuringGo));
	}


	// ========================================
	// フィールド
	// ========================================


	// クエスチョン・フィールド


	/// <summary>
	/// 時間無制限で思考させてるか（＾▽＾）
	/// </summary>
	bool m_isInfinite = false;

	/// <summary>
	/// 相手の思考時間中に、自分も思考するか☆？（＾ｑ＾）
	/// </summary>
	bool m_canPonder = false;


	// メイン・フィールド


	/// <summary>
	/// 反復深化探索中の深さ☆？
	/// </summary>
	Ply m_depth = 0;

	/// <summary>
	/// 探索中の訪問ノード数。
	/// </summary>
	u32 m_visitedNodesNum = 0;

	/// <summary>
	/// 多分、フィッシャータイムの追加時間☆？（＾ｑ＾）
	/// </summary>
	int m_increment[g_COLOR_NUM] = { 0 };

	/// <summary>
	///		<pre>
	/// 残り時間（ミリ秒）だぜ☆（＾ｑ＾）
	/// 
	///		- 元の名前：ｔｉｍｅ
	///		- ミリ秒単位だぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	int m_millisecondsLeft[g_COLOR_NUM] = { 0 };


	// ========================================
	// メソッド
	// ========================================


	// クエスチョン・メソッド


	/// <summary>
	///		<pre>
	/// 元の名前：　ｕｓｅＴｉｍｅＭａｎａｇｅｍｅｎｔ
	/// 時間管理が新品かどうか☆（＾ｑ＾）？
	/// 反復深化探索に潜るために真であることが必要☆
	///		</pre>
	/// </summary>
	/// <returns></returns>
	bool IsBrandnewTimeMgr() const {
		// 以下の全てが 0 の場合に真☆？（＾ｑ＾）
		return !(
			this->m_depth
			|
			this->m_visitedNodesNum
			|
			this->getMoveTime()
			|
			static_cast<int>(this->m_isInfinite)
			);
	}


	// アクセッサ


	/// <summary>
	/// 多分、フィッシャータイムの追加時間を取得する☆？（＾ｑ＾）
	/// </summary>
	/// <param name="us"></param>
	/// <returns></returns>
	inline int GetIncrement(Color us) const {
		return this->m_increment[us];
	}


	/// <summary>
	/// 残り時間（ミリ秒）だぜ（＾▽＾）
	/// </summary>
	/// <param name="us"></param>
	/// <returns></returns>
	inline int GetMillisecondsLeft(Color us)const {
		return this->m_millisecondsLeft[us];
	}


	/// <summary>
	///		<pre>
	/// btime, wtime コマンドをそのまま受け取るぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	/// <param name="us"></param>
	/// <param name="ssCmd"></param>
	inline void setTimeLeftFromStream(Color us, long long milliseconds) {
		this->m_millisecondsLeft[us] = milliseconds;
	}


	/// <summary>
	/// USI原案にあって、将棋所で実装されていない謎の［ムーブタイム］を取得☆（＾ｑ＾）
	/// </summary>
	/// <returns></returns>
	inline int getMoveTime() const {
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
	inline void increaseMoveTime(int value) {
		this->m_moveTime_ += value;
	}


	/// <summary>
	/// go byoyomi 等の場合に、マージン分減らすのに使う☆？
	/// </summary>
	/// <param name="value"></param>
	inline void decrementMoveTime(int value) {
		this->m_moveTime_ -= value;
	}


	/// <summary>
	/// 
	/// </summary>
	/// <param name="ssCmd"></param>
	inline void setMoveTimeFromStream(std::istringstream& ssCmd) {
		ssCmd >> this->m_moveTime_;
	}


	//────────────────────────────────────────────────────────────────────────────────
	// ムーブス・ツー・ゴーって何☆？（＾ｑ＾）
	//────────────────────────────────────────────────────────────────────────────────
	// FIXME: movesToGo というプロパティを持っていたが、"movesToGo" なんていうコマンドは USI から飛んでこないと思ったので削除したぜ☆（＾ｑ＾）
	// 時間管理の movesToGo の最大値だったみたいだぜ☆


private:


	// ========================================
	// フィールド
	// ========================================


	/// <summary>
	///		<pre>
	/// USI原案にあって、将棋所で実装されていない謎の［ムーブタイム］☆（＾ｑ＾）
	/// 
	///		- チェス（UCI）によると、動作試験目的で思考時間を強制的に設定したいときに使うみたいだぜ☆（＾ｑ＾）
	///		- ☆？ ポンダー・ヒットの経過時間が足しこまれる☆？（＾ｑ＾）
	///		- 秒読みマージンは引かれる☆
	///		</pre>
	/// </summary>
	int m_moveTime_ = 0;
};
