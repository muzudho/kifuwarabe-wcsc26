#pragma once


#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"
#include "../../header/n119_score___/n119_090_ScoreValue.hpp"


/// <summary>
/// 定跡エントリ☆
/// </summary>
struct BookEntry {


	/// <summary>
	/// キー。
	/// </summary>
	Key		m_key;

	/// <summary>
	/// 移動元と成か。
	/// </summary>
	u16		m_fromToPro;

	/// <summary>
	/// 
	/// </summary>
	u16		m_count;

	/// <summary>
	/// 
	/// </summary>
	ScoreValue	m_score;
};
