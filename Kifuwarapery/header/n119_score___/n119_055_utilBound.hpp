#pragma once

#include "n119_050_bound.hpp"


/// <summary>
/// 
/// </summary>
class UtilBound {


public:


	/// <summary>
	/// 使ってない？
	/// </summary>
	/// <param name="st"></param>
	/// <returns></returns>
	static inline bool ExactOrLower(const Bound st) {
		return (st & BoundLower ? true : false);
	}


	/// <summary>
	/// 使ってない？
	/// </summary>
	/// <param name="st"></param>
	/// <returns></returns>
	static inline bool ExactOrUpper(const Bound st) {
		return (st & BoundUpper ? true : false);
	}
};
