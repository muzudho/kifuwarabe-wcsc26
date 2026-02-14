#pragma once


// 探索用変数
class MuzGameEngineStorageModel;


/// <summary>
/// エンジン・オプション的☆（＾ｑ＾）
/// </summary>
class EngineOptionable {


protected:


	/// <summary>
	/// 
	/// </summary>
	using Fn = void(MuzGameEngineStorageModel*, const EngineOptionable&);


public:


	EngineOptionable(												Fn* = nullptr, MuzGameEngineStorageModel* s = nullptr);
	EngineOptionable(const char* v,								    Fn* = nullptr, MuzGameEngineStorageModel* s = nullptr);
	EngineOptionable(const bool  v,								    Fn* = nullptr, MuzGameEngineStorageModel* s = nullptr);
	EngineOptionable(const int   v, const int min, const int max,	Fn* = nullptr, MuzGameEngineStorageModel* s = nullptr);


	/// <summary>
    /// 代入演算子☆
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	EngineOptionable& operator = (const std::string& v);


	/// <summary>
    /// 整数化☆
	/// </summary>
	operator int() const {
		assert(m_type_ == "check" || m_type_ == "spin");
		return (m_type_ == "spin" ? atoi(m_currentValue_.c_str()) : m_currentValue_ == "true");
	}


	/// <summary>
    /// 文字列化☆
	/// </summary>
	operator std::string() const {
		assert(this->m_type_ == "string");
		return this->m_currentValue_;
	}


public:


	/// <summary>
	/// 既定値
	/// </summary>
	/// <returns></returns>
	std::string	GetDefaultValue()	const { return this->m_defaultValue_; }


	/// <summary>
	/// 型
	/// </summary>
	/// <returns></returns>
	std::string	GetType()			const { return this->m_type_; }


	/// <summary>
	/// 最小値
	/// </summary>
	/// <returns></returns>
	int			GetMin()			const { return this->m_min_; }


	/// <summary>
	/// 最大値
	/// </summary>
	/// <returns></returns>
	int			GetMax()			const { return this->m_max_; }


protected:


	/// <summary>
	/// 既定値
	/// </summary>
	std::string m_defaultValue_;

	/// <summary>
	/// 現在値
	/// </summary>
	std::string m_currentValue_;

	/// <summary>
	/// 型
	/// </summary>
	std::string m_type_;

	/// <summary>
	/// 最小値
	/// </summary>
	int m_min_;

	/// <summary>
	/// 最大値
	/// </summary>
	int m_max_;

	/// <summary>
	/// 変更時フック
	/// </summary>
	Fn* m_onChange_;

	/// <summary>
	///		<pre>
	/// ［ゲームエンジン倉庫］へのポインタ☆（＾ｑ＾）
    /// オプションの変更時に、ゲームエンジン倉庫の中身を変更するために必要だぜ☆（＾ｑ＾）
	///		</pre>
	/// </summary>
	MuzGameEngineStorageModel* m_pGameEngineStore_;
};
