#pragma once

#include "../n080_100_sysWorld/n080_100_500_common.hpp"


/// <summary>
///		<pre>
/// メルセンヌツイスター
/// 
///		- 64bit のランダムな値を返す為のクラス
///		</pre>
/// </summary>
class MT64bit : public std::mt19937_64 {


public:


	/// <summary>
	/// 生成。
	/// </summary>
	MT64bit() : std::mt19937_64() {}


	/// <summary>
	/// 生成。
	/// </summary>
	/// <param name="seed"></param>
	explicit MT64bit(const unsigned int seed) : std::mt19937_64(seed) {}


	/// <summary>
	/// 乱数取得。
	/// </summary>
	/// <returns></returns>
	u64 GetRandom() {
		return (*this)();
	}


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	u64 GetRandomFewBits() {
		return GetRandom() & GetRandom() & GetRandom();
	}
};


/// <summary>
/// 
/// </summary>
extern MT64bit g_mt64bit;
