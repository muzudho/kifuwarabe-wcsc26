#pragma once

#include "../n405_movegenType/n405_070_mtAbstract.hpp"
#include "../n405_movegenType/n405_100_mtCapture.hpp"
#include "../n405_movegenType/n405_110_mtNonCapture.hpp"
#include "../n405_movegenType/n405_120_mtDrop.hpp"
#include "../n405_movegenType/n405_130_mtCapturePlusPro.hpp"
#include "../n405_movegenType/n405_140_mtNonCaptureMinusPro.hpp"
#include "../n405_movegenType/n405_150_mtRecapture.hpp"
#include "../n405_movegenType/n405_160_mtEvasion.hpp"
#include "../n405_movegenType/n405_170_mtNonEvasion.hpp"
#include "../n405_movegenType/n405_180_mtLegal.hpp"
#include "../n405_movegenType/n405_190_mtLegalAll.hpp"
#include "../n405_movegenType/n405_200_mtMoveTypeNone.hpp"


/// <summary>
/// 指し手生成区分の配列☆
/// </summary>
class MovegenTypeAllCollection {


public:


	/// <summary>
	/// (^q^)const型の配列を作るには、static でやるんだぜ☆
	/// </summary>
	static const MovegenTypeCapture		m_mtCapture;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeNonCapture		m_mtNonCapture;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeDrop		m_mtDrop;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeCapturePlusPro		m_mtCapturePlusPro;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeNonCaptureMinusPro		m_mtNonCaptureMinusPro;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeRecapture		m_mtRecapture;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeEvasion		m_mtEvasion;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeNonEvasion		m_mtNonEvasion;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeLegal		m_mtLegal;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeLegalAll		m_mtLegalAll;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeNone		m_mtNone;

	/// <summary>
	/// 
	/// </summary>
	static const MovegenTypeAbstract*		m_mtArray[11];
};


/// <summary>
/// 
/// </summary>
extern MovegenTypeAllCollection g_movegenTypeCollection;
