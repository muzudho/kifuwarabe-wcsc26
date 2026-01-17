#include "../../header/n405_movegenType/n405_070_mtAbstract.hpp"
#include "../../header/n405_movegenType/n405_100_mtCapture.hpp"
#include "../../header/n405_movegenType/n405_110_mtNonCapture.hpp"
#include "../../header/n405_movegenType/n405_120_mtDrop.hpp"
#include "../../header/n405_movegenType/n405_130_mtCapturePlusPro.hpp"
#include "../../header/n405_movegenType/n405_140_mtNonCaptureMinusPro.hpp"
#include "../../header/n405_movegenType/n405_150_mtRecapture.hpp"
#include "../../header/n405_movegenType/n405_160_mtEvasion.hpp"
#include "../../header/n405_movegenType/n405_170_mtNonEvasion.hpp"
#include "../../header/n405_movegenType/n405_180_mtLegal.hpp"
#include "../../header/n405_movegenType/n405_190_mtLegalAll.hpp"
#include "../../header/n405_movegenType/n405_200_mtMoveTypeNone.hpp"
#include "../../header/n405_movegenType/n405_500_movegenTypeAllCollections.hpp"


/// <summary>
/// 駒を取る手、取らない手、駒打ち、成る手、成らない手、逃げる手、逃げない手、合法手全て、何もしない手、の配列☆ 
/// </summary>
const MovegenTypeCapture				MovegenTypeAllCollection::m_mtCapture;
const MovegenTypeNonCapture			MovegenTypeAllCollection::m_mtNonCapture;
const MovegenTypeDrop					MovegenTypeAllCollection::m_mtDrop;
const MovegenTypeCapturePlusPro		MovegenTypeAllCollection::m_mtCapturePlusPro;
const MovegenTypeNonCaptureMinusPro	MovegenTypeAllCollection::m_mtNonCaptureMinusPro;
const MovegenTypeRecapture				MovegenTypeAllCollection::m_mtRecapture;
const MovegenTypeEvasion				MovegenTypeAllCollection::m_mtEvasion;
const MovegenTypeNonEvasion			MovegenTypeAllCollection::m_mtNonEvasion;
const MovegenTypeLegal					MovegenTypeAllCollection::m_mtLegal;
const MovegenTypeLegalAll				MovegenTypeAllCollection::m_mtLegalAll;
const MovegenTypeNone					MovegenTypeAllCollection::m_mtNone;

const MovegenTypeAbstract*			MovegenTypeAllCollection::m_mtArray[11] = {
	&MovegenTypeAllCollection::m_mtCapture,
	&MovegenTypeAllCollection::m_mtNonCapture,
	&MovegenTypeAllCollection::m_mtDrop,
	&MovegenTypeAllCollection::m_mtCapturePlusPro,
	&MovegenTypeAllCollection::m_mtNonCaptureMinusPro,
	&MovegenTypeAllCollection::m_mtRecapture,
	&MovegenTypeAllCollection::m_mtEvasion,
	&MovegenTypeAllCollection::m_mtNonEvasion,
	&MovegenTypeAllCollection::m_mtLegal,
	&MovegenTypeAllCollection::m_mtLegalAll,
	&MovegenTypeAllCollection::m_mtNone
};


MovegenTypeAllCollection g_movegenTypeCollection;
