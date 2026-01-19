#pragma once

#include "../n119_score___/n119_090_ScoreValue.hpp"	//Ply,ScoreIndex
#include "../n119_score___/n119_500_EvalSum.hpp"
#include "../n165_movStack/n165_400_move.hpp"
#include "../n223_move____/n223_200_depth.hpp"


/// <summary>
/// Flashlight（ＳｅａｒｃｈＳｔａｃｋ）,NextmoveEvent(ＭｏｖｅＰｉｃｋｅｒ),ＳｐｌｉｔＰｏｉｎｔ が三つ巴になっている☆（＾ｑ＾）
/// </summary>
struct SplitedNode;


/// <summary>
///		<pre>
/// 元の名前： ＳｅａｒｃｈＳｔａｃｋ
/// スタックに積み上げていくもの。
/// とりあえず、フラッシュライト（懐中電灯）に改名。
///		</pre>
/// </summary>
class Flashlight {


public:


	/// <summary>
	/// 分岐ノードか☆
	/// </summary>
	SplitedNode*	m_splitedNode;

	/// <summary>
	/// 手数か☆？
	/// </summary>
	Ply				m_ply;

	/// <summary>
	/// 現在の指し手か、予想手か☆？
	/// </summary>
	Move			m_currentMove;

	/// <summary>
	/// TODO: これは必要？
	/// トランスポジション・テーブルと関連☆？
	/// </summary>
	Move			m_excludedMove;

	/// <summary>
	/// [0]新しいベストムーブ☆？
	/// [1]１個前のベストムーブ☆？（１個前を覚えている☆？）
	/// </summary>
	Move			m_killers[2];

	/// <summary>
	/// 削減とは☆？（＾ｑ＾）？
	/// </summary>
	Depth			m_reduction;

	/// <summary>
	/// 静的な評価値とは☆？
	/// </summary>
	ScoreValue			m_staticEval;

	/// <summary>
	/// 一時的にヌル・ムーブをせずに検索させたいときのために設定するもの☆
	/// </summary>
	bool			m_skipNullMove;

	/// <summary>
	/// 評価関数の差分計算用、値が入っていないときは [0] を ScoreNotEvaluated にしておく。
	/// 常に Black 側から見た評価値を入れておく。
	/// 0: 双玉に対する評価値, 1: 先手玉に対する評価値, 2: 後手玉に対する評価値
	/// </summary>
	EvalSum			m_staticEvalRaw;
};
