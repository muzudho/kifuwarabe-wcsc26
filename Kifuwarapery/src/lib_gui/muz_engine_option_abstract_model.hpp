#pragma once
#include <functional>
#include <string>

#if __cplusplus >= 202002L
#include <format>  // C++20
#else
#include <sstream>
#endif


/// <summary>
/// エンジン・オプション的☆（＾ｑ＾）
/// </summary>
class MuzEngineOptionAbstractModel {


public:


	// ========================================
	// 生成／破棄
	// ========================================


	// TODO: ボタン用に作った（＾～＾）
	MuzEngineOptionAbstractModel(
		std::string type,
		int min,
		int max,
		std::function<void(const MuzEngineOptionAbstractModel&)> onChanged = nullptr);

	// XXX: これを消すとコンパイルエラー。匿名関数で使ってる（＾～＾）？
	MuzEngineOptionAbstractModel(
		std::function<void(const MuzEngineOptionAbstractModel&)> onChanged = nullptr);

	// TODO: テキストボックス
	MuzEngineOptionAbstractModel(
		const char* v,
		std::function<void(const MuzEngineOptionAbstractModel&)> onChanged = nullptr);

	// TODO: チェックボックス
	MuzEngineOptionAbstractModel(
		const bool  v,
		std::function<void(const MuzEngineOptionAbstractModel&)> onChanged = nullptr);

	// TODO: スピンボックス
	MuzEngineOptionAbstractModel(
		const int   v,
		const int min,
		const int max,
		std::function<void(const MuzEngineOptionAbstractModel&)> onChanged = nullptr);


protected:


	// ========================================
	// フィールド
	// ========================================


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
	std::function<void(const MuzEngineOptionAbstractModel&)> m_onChanged_;


public:


	// ========================================
	// 演算子
	// ========================================


	/// <summary>
    /// 代入演算子☆
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	MuzEngineOptionAbstractModel& operator = (const std::string& v);


	/// <summary>
    /// 整数化☆
	/// </summary>
	operator int() const {
		//assert(m_type_ == "check" || m_type_ == "spin");
		return (m_type_ == "spin" ? atoi(m_currentValue_.c_str()) : m_currentValue_ == "true");
	}


	/// <summary>
    /// 文字列化☆
	/// </summary>
	operator std::string() const {
		//assert(this->m_type_ == "string");
		return this->m_currentValue_;
	}


	// ========================================
	// その他のメソッド
	// ========================================


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


	/// <summary>
    /// USIコード化☆（＾～＾）
	/// </summary>
	/// <returns></returns>
	virtual std::string ToUSICode()	const;	// = 0;

};
