#pragma once


#include "../n080_100_sysWorld/n080_100_500_common.hpp"	//Mutexなど
#include "../n119_500_sweetnes/n119_090_Sweetness.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../../src/lib_toybox_medium/muz_position_medium_model.hpp"
#include "../n223_move____/n223_200_depth.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"


class Monkie;
class WhistleAbstract;


/// <summary>
///		<pre>
/// スプリット・ポイント
/// ［一緒に走る猿たちが分かれた所］☆（＾ｑ＾）
/// 
///		- 旧名： `ＳplitPoint`
///		</pre>
/// </summary>
struct MonkeySplitedPlace {


	// ========================================
	// フィールド
	// ========================================


	// クエスチョン・フィールド


	/// <summary>
	/// これは無用なノードだ。カットオフされたノードだ。
	/// </summary>
	volatile bool		m_isUselessNode;


	// メイン・フィールド


	/// <summary>
	/// 局面か☆
	/// </summary>
	const Position*		m_position;

	/// <summary>
	/// サーチ・スタック☆
	/// </summary>
	const Flashlight*	m_pFlashlightBox;

	/// <summary>
	/// マスター・スレッド☆
	/// </summary>
	Monkie*				m_masterThread;

	/// <summary>
	/// 深さ。
	/// </summary>
	Depth				m_depth;

	/// <summary>
	/// ベータ。
	/// </summary>
	Sweetness				m_beta;

	/// <summary>
	/// スプリット・ポイントは　ノード・タイプを持っている☆？（＾ｑ＾）
	/// </summary>
	const WhistleAbstract*		m_pWhistle01;

	/// <summary>
	/// 
	/// </summary>
	Move				m_threatMove;

	/// <summary>
	/// 
	/// </summary>
	bool				m_cutNode;

	/// <summary>
	/// 
	/// </summary>
	NextmoveEvent*		m_pNextmoveEvent;

	/// <summary>
	/// 親要素☆（＾～＾）
	/// </summary>
	MonkeySplitedPlace*		m_pParentMonkeySplitedPlace;

	/// <summary>
	/// 
	/// </summary>
	Mutex				m_mutex;

	/// <summary>
	/// 
	/// </summary>
	volatile u64		m_slavesMask;

	/// <summary>
	/// 
	/// </summary>
	volatile s64		m_nodes;

	/// <summary>
	/// 
	/// </summary>
	volatile Sweetness		m_alpha;

	/// <summary>
	/// 評価値
	/// </summary>
	volatile Sweetness		m_bestSweetness;

	/// <summary>
	/// 
	/// </summary>
	volatile Move		m_bestMove;

	/// <summary>
	/// 
	/// </summary>
	volatile int		m_moveCount;
};
