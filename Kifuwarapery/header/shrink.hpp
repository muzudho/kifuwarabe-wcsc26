#pragma once


// 大平野の冒険をシュリンクするぜ（＾～＾）


// ルートノード


// なんか分からんが再帰探索（＾～＾）
// これを定義するとバグが取れるけど、指し手が全然ダメになるぜ（＾～＾）
//#define SHRINK_R_NODEKIND_EXPLORE_PLAIN_400N500_RECURSIVE_SEARCH


// なんか分からんが再帰探索（＾～＾）
// シュリンクすると１手の深さしか読まなくなるようだぜ（＾～＾）
//#define SHRINK_R_NODEKIND_EXPLORE_PLAIN_500N500_RECURSIVE_SEARCH


// NonPV扱いで再帰するみたいなんだがなんだこれだぜ☆（＾～＾）？
// シュリンクすると１手の深さしか読まなくなるようだぜ（＾～＾）しかも端歩をただ突くだけ（＾～＾）
//#define SHRINK_R_NODEKIND_EXPLORE_PLAIN_500N600_NON_PV_RECURSIVE_SEARCH


// でかいβ値も深掘りしないぜ（＾～＾）
// バグは取れないぜ（＾～＾）
//#define SHRINK_R_NODEKIND_EXPLORE_PLAIN_600N900_LARGE_BETA_RECURSIVE_SEARCH


// 猿を増やすの、止めるぜ（＾～＾）
// バグは取れないぜ（＾～＾）
//#define SHRINK_R_NODEKIND_EXPLORE_PLAIN_700N750_FORK_NEW_MONKEY


// 非PVノード


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_200N600_NON_PV_RAZORING


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_200N700_NON_PV_RECURSIVE_SEARCH

// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_200N750_RECURSIVE_SEARCH


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_200N800_INTERNAL_ID


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_400N500_RECURSIVE_SEARCH


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_400N550_FUTILITY_PRUNING


// これを定義すると、読み筋の駒が貫通するバグが出るぜ（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_500N500_RECURSIVE_SEARCH


// バグは取れるけど、１手、２手しか読まなくなるぜ（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_500N600_NON_PV_RECURSIVE_SEARCH


// 猿を増やすの、止めるぜ（＾～＾）
// シュリンクすると１手の深さしか読まなくなるようだぜ（＾～＾）
//#define SHRINK_NP_NODEKIND_EXPLORE_PLAIN_700N750_FORK_NEW_MONKEY


// 分岐ルートノード


// 分岐本筋ノード


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_SPLITED__PV_NODE_EXPLORE_PLAIN_360_RECURSIVE_SEARCH


// これを定義してもバグは取れない（＾～＾）
//#define SHRINK_SPLITED_PV_NODE_EXPLORE_PLAIN_380_NON_PV_RECURSIVE_SEARCH


