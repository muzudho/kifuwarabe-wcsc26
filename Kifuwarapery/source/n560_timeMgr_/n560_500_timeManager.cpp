#include <algorithm> // std::min
#include "../../header/n119_score___/n119_090_scoreIndex.hpp"
#include "../../header/n560_timeMgr_/n560_100_limitsDuringGo.hpp"
#include "../../header/n560_timeMgr_/n560_500_timeManager.hpp"
#include "../../header/n885_searcher/n885_040_ourCarriage.hpp"


namespace {


	//────────────────────────────────────────────────────────────────────────────────
	// MoveHorizon …… 消費する思考時間の配分にだけ関係するみたいだが☆？（＾ｑ＾）？ 初期値47☆
	// MaxRatio …… 1.0 より大きくする感じ☆？ 最大延長時間にだけ関係するみたいだが☆？（＾ｑ＾）？ 5.0 で 長考は 通常の3倍☆？
	//
	// 知見
	// ・長考し過ぎて良い手を指しても、長考してないときに凡打を指して悪くしてしまう☆　続きを打てない☆
	//────────────────────────────────────────────────────────────────────────────────

	// いろいろ試したが、適当に改造するんで、精密なことはできね（＾～＾）
	// 例えば［15分切れ負け用］とか、［2時間切れ負け用］とか、レギュレーションで変えるといいかもしれないが、めんどくさいよな（＾～＾）
	// 気分で決めろだぜ（＾▽＾）

	/// <summary>
	/// 自分が何手読むかの予測値。 (2026-01-13-tue) 勘で 125手 とか設定してたがそんな読まんだろ、31 手に減らそ☆（＾－＾）オリジナルでは 47手（＾～＾）
	/// </summary>
	const int g_MOVE_NUM_HORIZON = 31;
	const float g_MAX_RATIO = 5.0f;


	/// <summary>
	///		<pre>
	/// 次回の残り時間☆ 
	/// 
	///		- 旧名：ｒｅｍａｉｎｉｎｇ
	///		</pre>
	/// </summary>
	/// <param name="movesToGo">ムーブ・ホライズン以下の値☆（＾ｑ＾）</param>
	/// <returns></returns>
	inline float G_TimeBairitu_YoteiSiko(
		const int movesToGo)
	{
		// 旧名：ｏｔｈｅｒＭｏｖｅＩｍｐｏｒｔａｎｃｅ
		// 残りの手の、ムーブ・インポータンスの合計☆（＾ｑ＾）
		float nokoriOmomiRuikei = movesToGo - 1;
		if (nokoriOmomiRuikei < 0) {
			nokoriOmomiRuikei = 0;
		}

		//   １
		// ───────
		// 1 + 累計
		return 
			1
			/
			static_cast<float>(1 + nokoriOmomiRuikei);
	}


	/// <summary>
	/// スティール率とは何なのか☆？（＾ｑ＾）？
	/// </summary>
	const float g_STEAL_RATIO = 0.33;


	/// <summary>
	/// 
	/// </summary>
	/// <param name="movesToGo"></param>
	/// <returns></returns>
	inline float G_TimeBairitu_SaidaiEncho(
		const int movesToGo	//ムーブ・ホライズン以下の値☆（＾ｑ＾）
		) {

		// 旧名：ｏｔｈｅｒＭｏｖｅＩｍｐｏｒｔａｎｃｅ
		// 残りの手の、ムーブ・インポータンスの合計☆（＾ｑ＾）
		float nokoriOmomiRuikei = movesToGo - 1;
		if (nokoriOmomiRuikei < 0) {
			nokoriOmomiRuikei = 0;
		}

		// ２種類の比率を調べて、小さい方を取るぜ☆（＾ｑ＾）

		//   比率
		// ───────
		// 比率 + 累計
		const float ratio1 =
			g_MAX_RATIO
			/
			static_cast<float>(g_MAX_RATIO + nokoriOmomiRuikei);

		//   スティール率 * 累計 + 1
		// ───────────────────────────
		//           累計 + 1
		const float ratio2 =
			(g_STEAL_RATIO * nokoriOmomiRuikei + 1)
			/
			static_cast<float>(nokoriOmomiRuikei + 1);

		return std::min(ratio1, ratio2);
	}
}


/// <summary>
///		時間の使い方を不安定にする度数だぜ（＾▽＾）
/// </summary>
/// <param name="currBestMovePlyChanges"></param>
/// <param name="prevBestMovePlyChanges"></param>
void TimeManager::SetPvInstability(
	const Ply currBestMovePlyChanges,
	const Ply prevBestMovePlyChanges
) {
	this->SetBufferThinkSeconds(
		currBestMovePlyChanges * (this->GetPlanPayBothPlayersSeconds() / 2)
		+
		prevBestMovePlyChanges * (this->GetPlanPayBothPlayersSeconds() / 3)
		);
}


/// <summary>
///		<pre>
/// 最初の設定（初期化）
/// 
///		- ヒッチハイカーのThink開始時に初期設定をするぜ☆（＾▽＾）
///		</pre>
/// </summary>
/// <param name="isMoveTime0Clear">false を入れてくれ☆（＾ｑ＾）</param>
/// <param name="limits">m_moveTimeを 0にする場合があるぜ☆（＾ｑ＾）</param>
/// <param name="currentPly"></param>
/// <param name="us"></param>
/// <param name="pRucksack"></param>
void TimeManager::Initialize(
	bool& isMoveTime0Clear,
	const LimitsDuringGo& limits,
	const Ply currentPly,
	const Color us,
	OurCarriage* pRucksack)
{
	const Color them = ConvColor::OPPOSITE_COLOR10b(us);	// 相手の手番の色

	const int emergencyMoveHorizon = pRucksack->m_engineOptions["Emergency_Move_Horizon"];	// 何か急ぐんかな（＾～＾）？
	const int nokositeokuTime      = pRucksack->m_engineOptions["Minimum_Thinking_Time"];	// 手番で、使わずに残しておく思考時間☆

	//this->ZeroclearTemeBonusTime();
	this->ZeroclearBufferThinkSeconds();
	this->ZeroclearPredictOpponentPaySeconds();
	this->SetPlanPayOwnSeconds( limits.GetMillisecondsLeft(us));// 予定思考時間は、残り時間をそのまんま入れて初期化☆？（＾ｑ＾）？
	this->SetSaidaiEnchoTime( limits.GetMillisecondsLeft(us));// 最大延長時間も☆？（＾ｑ＾）？


	//────────────────────────────────────────────────────────────────────────────────
	// 消費時間シミュレーション
	//────────────────────────────────────────────────────────────────────────────────
	//
	// 例えば 47 手先に詰めると　仮定し、
	// その 47 手を、指定の割合で　持ち時間を消費していくのを　試し、
	// 47手目に残ってあるであろう時間を調べます。
	//
	for (
		// ムーブス・ツー・ゴー
		int iMovesToGo = 1; // ループ・カウンター☆
		iMovesToGo <= g_MOVE_NUM_HORIZON;	// 初期設定で 47☆
		++iMovesToGo
	) {
		// 元の名前：ｈｙｐＭｙＴｉｍｅ
		// マイ・タイム☆　叩き台となる時間だぜ☆（＾ｑ＾）

		// 0秒で指し続けたとしたときの、自分の手番での持ち時間☆（＾ｑ＾）
		int motiTime =
			limits.GetMillisecondsLeft(us)
			+ limits.GetIncrement(us) * (iMovesToGo - 1)	// 今後追加されるインクリメントの累計☆
			//- emergencyBaseTime	// 緊急時用に残しておこうというタイム（ミリ秒）か☆？
			//- emergencyMoveTime	// 緊急時用に残しておこうというタイム（ミリ秒）か☆？
			//+ std::min(iHypMtg, emergencyMoveHorizon) // 1～255 ミリ秒を加算してどうするのか☆？（＾ｑ＾）
			;

		motiTime = std::max(motiTime, 0); // 0以上を確保するぜ☆（＾ｑ＾）

		// 思考予定タイムが、少なくなっていれば更新します。
		this->SmallUpdate_YoteiMyTurnTime(

			// 手番 i での、消費後の残り時間
			static_cast<int>(motiTime * G_TimeBairitu_YoteiSiko(iMovesToGo)) + nokositeokuTime// (消費時間は倍率で指定) + 残しておく時間
			); 

		// 最大延長タイムが、少なくなっていれば更新します。
		this->SmallUpdate_SaidaiEnchoTime(
			static_cast<int>(motiTime * G_TimeBairitu_SaidaiEncho(iMovesToGo)) + nokositeokuTime// (消費時間は倍率で指定) + 残しておく時間
		);
	}

	// 相手の思考中にも読み続ける設定の場合☆（＾ｑ＾）
	if (pRucksack->m_engineOptions["USI_Ponder"]) {

		// 相手が何秒考えるかなんて分からないので☆（＾～＾）
		// FIXME: 相手の思考タイム推測は、自分の考える時間の 4分の1 にしておくぜ☆（＾▽＾）
		// TODO: 相手の消費時間って見れないのかだぜ（＾～＾）？
		long long seconds = pRucksack->m_gameStats.GetPredictPayMilliseconds(them) / 1000;
		this->SetPredictOpponentPaySeconds(
			seconds
			//this->GetPlanPayOwnSeconds() / 4
		);

		// 独自実装☆（＾▽＾）：相手の残り時間より　多めに設定している場合は、相手の残り時間の最大値に合わせるんだぜ☆（＾▽＾）
		int opponentNokoriTime = limits.GetMillisecondsLeft(them);
		if (opponentNokoriTime < this->GetPredictOpponentPaySeconds()) {
			this->SetPredictOpponentPaySeconds(opponentNokoriTime);
		}
	}


	// 独自実装☆（＾▽＾）： 終盤ほど時間を使ってもいいように、緩くするぜ☆
	//this->SetTemeBonusTime( (currentPly-20) * 200);


	// 「予定思考時間＋予想ポンダー時間」よりも「残しておく時間」の方が大きいようなら、「予定思考時間＋予想ポンダー時間」は、「予定思考時間」を調整し、「残しておく時間」と等しくします。
	this->LargeUpdate_YoteiMyTurnTime( nokositeokuTime);
	// 「予定思考時間＋予想ポンダー時間」よりも「最大延長時間」の方が小さいようなら、「予定思考時間＋予想ポンダー時間」は、「予定思考時間」を調整し、は「最大延長時間」と等しくします。
	this->SmallUpdate_YoteiMyTurnTime( this->GetSaidaiEnchoTime() );


	// 独自実装☆（＾▽＾）：自分の残り時間 - 4　（4という数字は適当。大会会場の通信遅延を４秒と想定）より　予定自分手番時間を　多めに設定している場合は、
	// 予定自分手番時間を　自分の残り時間 - 4　に合わせるぜ☆　予想相手手番時間は　いじらないぜ☆（＾ｑ＾）
	int myNokoriTime = limits.GetMillisecondsLeft(us);
	if (myNokoriTime - 4 < this->GetPlanPayOwnSeconds()) {
		this->SetPlanPayOwnSeconds(myNokoriTime - 4);
	}


	if (limits.GetMoveTime() != 0) {//（＾ｑ＾）いつも　０　な気がするぜ☆
		// こんなとこ、実行されないんじゃないかだぜ☆？（＾ｑ＾）？
		if (this->GetPlanPayBothPlayersSeconds() < limits.GetMoveTime()) {
			this->SetPlanPayOwnSeconds( std::min(limits.GetMillisecondsLeft(us), limits.GetMoveTime()) - this->GetPredictOpponentPaySeconds() );
		}
		if (this->GetSaidaiEnchoTime() < limits.GetMoveTime()) {
			this->SetSaidaiEnchoTime( std::min(limits.GetMillisecondsLeft(us), limits.GetMoveTime()) );
		}
		this->IncreasePlanPayOwnSeconds( limits.GetMoveTime());
		this->IncreaseSaidaiEnchoTime( limits.GetMoveTime());
		if (limits.GetMillisecondsLeft(us) != 0) {
			isMoveTime0Clear = true;
		}
	}

	// ここは仕様になく、勝手に表示している情報だぜ（＾▽＾）
	//旧表示：optimum_search_time
	//旧表示：maximum_search_time	
	SYNCCOUT << "info string old limits move time " << limits.GetMoveTime() << SYNCENDL;
	// SYNCCOUT << "info string limits inc time " << limits.GetIncrement(us) << SYNCENDL; // 加算時間はちゃんと取得できていたぜ☆
	SYNCCOUT << "info string think seconds budget " << this->GetPlanThinkSeconds()
		<< " ( plan think seconds " << this->GetPlanPayOwnSeconds()
		<< " + predict opponent think seconds " << this->GetPredictOpponentPaySeconds()
		//<< " + teme bonus "	<< this->GetTemeBonusTime()
		<< " + asobi " << this->GetBufferThinkSeconds()
		<< ")" << SYNCENDL;
	SYNCCOUT << "info string saidai encho " << this->GetSaidaiEnchoTime() << SYNCENDL;
}
