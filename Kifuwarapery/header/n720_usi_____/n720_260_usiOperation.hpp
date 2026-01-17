#pragma once


#include <string>
#include <sstream>
#include "../n220_position/n220_645_gameStats.hpp"
#include "../n220_position/n220_650_position.hpp"


using namespace std;


/// <summary>
/// USI 操作☆
/// </summary>
class UsiOperation {


public:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="ssCmd"></param>
	void Go(GameStats& gameStats, const Position& pos, std::istringstream& ssCmd);


#if defined LEARN
	void Go(const Position& GetPos, const Ply GetDepth, const Move GetMove);
#endif


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="ssCmd"></param>
	void SetPositionToOrangutans(Position& pos, std::istringstream& ssCmd);


#if !defined NDEBUG
	/// <summary>
	/// for debug
	/// </summary>
	/// <param name="GetPos"></param>
	/// <param name="moveStr"></param>
	/// <returns></returns>
	Move usiToMoveDebug(const Position& GetPos, const std::string& moveStr);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="GetPos"></param>
	/// <param name="moveStr"></param>
	/// <returns></returns>
	Move csaToMoveDebug(const Position& GetPos, const std::string& moveStr);
#endif


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="moveStr"></param>
	/// <returns></returns>
	Move CsaToMove(const Position& pos, const std::string& moveStr);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="moveStr"></param>
	/// <returns></returns>
	Move UsiToMove(const Position& pos, const std::string& moveStr);


private:


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="moveStr"></param>
	/// <returns></returns>
	Move UsiToMoveBody(const Position& pos, const std::string& moveStr);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="moveStr"></param>
	/// <returns></returns>
	Move CsaToMoveBody(const Position& pos, const std::string& moveStr);
};
