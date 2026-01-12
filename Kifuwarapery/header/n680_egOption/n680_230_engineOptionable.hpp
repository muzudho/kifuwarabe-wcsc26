#pragma once

#include "../n080_common__/n080_100_common.hpp"


class OurCarriage;


/// <summary>
/// エンジン・オプション的☆（＾ｑ＾）
/// </summary>
class EngineOptionable {


protected:


	/// <summary>
	/// 
	/// </summary>
	using Fn = void(OurCarriage*, const EngineOptionable&);


public:


	EngineOptionable(												Fn* = nullptr, OurCarriage* s = nullptr);
	EngineOptionable(const char* v,								    Fn* = nullptr, OurCarriage* s = nullptr);
	EngineOptionable(const bool  v,								    Fn* = nullptr, OurCarriage* s = nullptr);
	EngineOptionable(const int   v, const int min, const int max,	Fn* = nullptr, OurCarriage* s = nullptr);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	EngineOptionable& operator = (const std::string& v);


	/// <summary>
	/// 
	/// </summary>
	operator int() const {
		assert(m_type_ == "check" || m_type_ == "spin");
		return (m_type_ == "spin" ? atoi(m_currentValue_.c_str()) : m_currentValue_ == "true");
	}


	/// <summary>
    /// 文字列化☆
	/// </summary>
	operator std::string() const {
		assert(m_type_ == "string");
		return m_currentValue_;
	}


public:


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::string	GetDefaultValue()	const { return this->m_defaultValue_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	std::string	GetType()			const { return this->m_type_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int			GetMin()			const { return this->m_min_; }


	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	int			GetMax()			const { return this->m_max_; }


protected:


	/// <summary>
	/// 
	/// </summary>
	std::string m_defaultValue_;

	/// <summary>
	/// 
	/// </summary>
	std::string m_currentValue_;

	/// <summary>
	/// 
	/// </summary>
	std::string m_type_;

	/// <summary>
	/// 
	/// </summary>
	int m_min_;

	/// <summary>
	/// 
	/// </summary>
	int m_max_;

	/// <summary>
	/// 
	/// </summary>
	Fn* m_onChange_;

	/// <summary>
	/// 
	/// </summary>
	OurCarriage* m_searcher_;
};
