#pragma once


// 大平野の冒険をシュリンクするぜ（＾～＾）


// ルートノード


// なんか分からんが再帰探索（＾～＾）
// これを定義するとバグが取れるけど、指し手が全然ダメになるぜ（＾～＾）
//#define SHRINK_ROOT_NODE_EXPLORE_PLAIN_260_RECURSIVE_SEARCH


// なんか分からんが再帰探索（＾～＾）
// シュリンクすると１手の深さしか読まなくなるようだぜ（＾～＾）
//#define SHRINK_ROOT_NODE_EXPLORE_PLAIN_360_RECURSIVE_SEARCH


// NonPV扱いで再帰するみたいなんだがなんだこれだぜ☆（＾～＾）？
// シュリンクすると１手の深さしか読まなくなるようだぜ（＾～＾）しかも端歩をただ突くだけ（＾～＾）
//#define SHRINK_ROOT_NODE_EXPLORE_PLAIN_NON_PV_RECURSIVE_SEARCH


// でかいβ値も深掘りしないぜ（＾～＾）
// バグは取れないぜ（＾～＾）
//#define SHRINK_ROOT_NODE_EXPLORE_PLAIN_LARGE_BETA_RECURSIVE_SEARCH


// 猿を増やすの、止めるぜ（＾～＾）
// バグは取れないぜ（＾～＾）
//#define SHRINK_ROOT_NODE_EXPLORE_PLAIN_FORK_NEW_MONKEY


// 非PVノード


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NON_PV_NODE_EXPLORE_PLAIN_125_NON_PV_RECURSIVE_SEARCH

// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NON_PV_NODE_EXPLORE_PLAIN_127_RECURSIVE_SEARCH


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NON_PV_NODE_EXPLORE_PLAIN_130_INTERNAL_ID


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NON_PV_NODE_EXPLORE_PLAIN_260_RECURSIVE_SEARCH


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NON_PV_NODE_EXPLORE_PLAIN_273_FUTILITY_PRUNING


// これを定義すると、読み筋の駒が貫通するバグが出るぜ（＾～＾）
//#define SHRINK_NON_PV_NODE_EXPLORE_PLAIN_360_RECURSIVE_SEARCH


// バグは取れるけど、１手、２手しか読まなくなるぜ（＾～＾）
//#define SHRINK_NON_PV_NODE_EXPLORE_PLAIN_380_NON_PV_RECURSIVE_SEARCH


// 猿を増やすの、止めるぜ（＾～＾）
// シュリンクすると１手の深さしか読まなくなるようだぜ（＾～＾）
//#define SHRINK_NON_PV_NODE_EXPLORE_PLAIN_FORK_NEW_MONKEY


// 分岐ルートノード


// 分岐本筋ノード


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_SPLITED__PV_NODE_EXPLORE_PLAIN_360_RECURSIVE_SEARCH


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_SPLITED_PV_NODE_EXPLORE_PLAIN_380_NON_PV_RECURSIVE_SEARCH


