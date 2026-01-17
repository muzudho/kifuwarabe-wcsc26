#pragma once
#pragma once


// 大平野の冒険をシュリンクするぜ（＾～＾）


// なんか分からんが再帰探索（＾～＾）
// これを定義するとバグが取れるけど、指し手が全然ダメになるぜ（＾～＾）
#define SHRINK_EXPLORE_PLAIN_260_RECURSIVE_SEARCH


// なんか分からんが再帰探索（＾～＾）
// シュリンクすると１手の深さしか読まなくなるようだぜ（＾～＾）
//#define SHRINK_EXPLORE_PLAIN_360_RECURSIVE_SEARCH


// NonPV扱いで再帰するみたいなんだがなんだこれだぜ☆（＾～＾）？
// シュリンクすると１手の深さしか読まなくなるようだぜ（＾～＾）しかも端歩をただ突くだけ（＾～＾）
//#define SHRINK_EXPLORE_PLAIN_NON_PV_RECURSIVE_SEARCH


// でかいβ値も深掘りしないぜ（＾～＾）
#define SHRINK_EXPLORE_PLAIN_LARGE_BETA_RECURSIVE_SEARCH


// 猿を増やすの、止めるぜ（＾～＾）
#define SHRINK_EXPLORE_PLAIN_FORK_NEW_MONKEY

