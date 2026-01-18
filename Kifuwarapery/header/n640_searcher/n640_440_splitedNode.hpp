#pragma once


#include "../n080_100_sysWorld/n080_100_500_common.hpp"	//Mutexなど
#include "../n119_score___/n119_090_scoreIndex.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n220_position/n220_650_position.hpp"
#include "../n223_move____/n223_200_depth.hpp"
#include "../n223_move____/n223_500_flashlight.hpp"
#include "../n440_movStack/n440_500_nextmoveEvent.hpp"
#include "../n640_searcher/n640_040_nodeKind.hpp"


class Monkie;
class SwordAbstract;


/// <summary>
///		<pre>
/// 元の名前は ＳｐｌｉｔＰｏｉｎｔ☆
/// ツリーノードの、分岐しているところだろうか☆（＾ｑ＾）？
///		</pre>
/// </summary>
struct SplitedNode {


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
	ScoreIndex				m_beta;

	/// <summary>
	/// スプリット・ポイントは　ノード・タイプを持っている☆？（＾ｑ＾）
	/// </summary>
	const SwordAbstract*		m_pSword01;

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
	/// 
	/// </summary>
	SplitedNode*		m_pParentSplitedNode;

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
	volatile ScoreIndex		m_alpha;

	/// <summary>
	/// 
	/// </summary>
	volatile ScoreIndex		m_bestScore;

	/// <summary>
	/// 
	/// </summary>
	volatile Move		m_bestMove;

	/// <summary>
	/// 
	/// </summary>
	volatile int		m_moveCount;
};
