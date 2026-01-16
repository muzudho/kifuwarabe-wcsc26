#pragma once


#include <string>
#include <sstream>
#include <fstream>
#include "../n080_100_sysWorld/n080_100_500_common.hpp"
#include "../n105_180_piece___/n105_180_150_piece.hpp"
#include "../n223_move____/n223_300_moveAndScoreIndex.hpp"
#include "../n600_book____/n600_100_mt64bit.hpp"


// 依存関係の回避
class GameStats;
class Position;


/// <summary>
/// 定跡。
/// </summary>
class Book : private std::ifstream {


public:


	/// <summary>
	/// 生成。
	/// </summary>
	Book() : m_random_(std::chrono::system_clock::now().time_since_epoch().count()) {}


	/// <summary>
	/// 確率を取得？
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="fName"></param>
	/// <param name="pickBest"></param>
	/// <returns></returns>
	MoveAndScoreIndex GetProbe(const Position& pos, const std::string& fName, const bool pickBest);


	/// <summary>
	/// 
	/// </summary>
	static void Init();


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	static Key GetBookKey(const Position& pos);


private:


	/// <summary>
	/// 旧名：Ｏｐｅｎ
	/// </summary>
	/// <param name="fName"></param>
	/// <returns></returns>
	bool OpenBook(const char* fName);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="key"></param>
	void Binary_search(const Key key);


	/// <summary>
	/// 定跡のhash生成用なので、seedは固定でデフォルト値を使う。
	/// </summary>
	static MT64bit	m_mt64bit_;

	/// <summary>
	/// 時刻をseedにして色々指すようにする。
	/// </summary>
	MT64bit			m_random_;

	/// <summary>
	/// ファイル名。
	/// </summary>
	std::string		m_fileName_;

	/// <summary>
	/// サイズ。
	/// </summary>
	size_t			m_size_;

	/// <summary>
	/// 
	/// </summary>
	static Key m_ZobPiece[N31_PieceNone][SquareNum];

	/// <summary>
	/// 
	/// </summary>
	static Key m_ZobHand[HandPieceNum][19];

	/// <summary>
	/// 
	/// </summary>
	static Key m_ZobTurn;
};


/// <summary>
/// 定跡作成。
/// </summary>
/// <param name="pos"></param>
/// <param name="ssCmd"></param>
void MakeBook(GameStats& gameStats, Position& pos, std::istringstream& ssCmd);
