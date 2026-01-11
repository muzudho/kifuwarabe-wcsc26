#pragma once

#include "../n220_position/n220_200_changedListPair.hpp"


/// <summary>
/// 
/// </summary>
struct ChangedLists {


	/// <summary>
	/// 一手で動く駒は最大2つ。(動く駒、取られる駒)
	/// </summary>
	ChangedListPair m_clistpair[2];

	/// <summary>
	/// 一手で動く駒は最大2つ。(動く駒、取られる駒)
	/// </summary>
	int m_listindex[2];

	/// <summary>
	/// 
	/// </summary>
	size_t m_size;
};
