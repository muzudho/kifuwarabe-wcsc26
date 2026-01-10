#pragma once

#include "../n405_moveType/n405_070_mtAbstract.hpp"
#include "../n405_moveType/n405_100_mtCapture.hpp"
#include "../n405_moveType/n405_110_mtNonCapture.hpp"
#include "../n405_moveType/n405_120_mtDrop.hpp"
#include "../n405_moveType/n405_130_mtCapturePlusPro.hpp"
#include "../n405_moveType/n405_140_mtNonCaptureMinusPro.hpp"
#include "../n405_moveType/n405_150_mtRecapture.hpp"
#include "../n405_moveType/n405_160_mtEvasion.hpp"
#include "../n405_moveType/n405_170_mtNonEvasion.hpp"
#include "../n405_moveType/n405_180_mtLegal.hpp"
#include "../n405_moveType/n405_190_mtLegalAll.hpp"
#include "../n405_moveType/n405_200_mtMoveTypeNone.hpp"


/// <summary>
/// 指し手生成区分の配列☆
/// </summary>
class MoveTypeArray {


public:


	/// <summary>
	/// (^q^)const型の配列を作るには、static でやるんだぜ☆
	/// </summary>
	static const MoveTypeCapture m_moveTypeCapture;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeNonCapture m_moveTypeNonCapture;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeDrop m_moveTypeDrop;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeCapturePlusPro m_moveTypeCapturePlusPro;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeNonCaptureMinusPro m_moveTypeNonCaptureMinusPro;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeRecapture m_moveTypeRecapture;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeEvasion m_moveTypeEvasion;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeNonEvasion m_moveTypeNonEvasion;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeLegal m_moveTypeLegal;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeLegalAll m_moveTypeLegalAll;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeNone m_moveTypeNone;

	/// <summary>
	/// 
	/// </summary>
	static const MoveTypeAbstract* m_moveTypeArray[11];
};


/// <summary>
/// 
/// </summary>
extern MoveTypeArray g_moveTypeArray;
