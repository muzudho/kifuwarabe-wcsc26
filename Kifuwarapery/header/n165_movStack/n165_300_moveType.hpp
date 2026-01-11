#pragma once


/// <summary>
/// 指し手生成器の種類
/// </summary>
enum MoveType {
	/// <summary>
	/// 駒を取る手。     歩, 飛, 角 の不成は含まない。香の二段目の不成を含まない。
	/// </summary>
	N00_Capture,

	/// <summary>
	/// 駒を取らない手。 歩, 飛, 角 の不成は含まない。香の二段目の不成を含まない。
	/// </summary>
	N01_NonCapture,

	/// <summary>
	/// 駒打ち。 二歩、打ち歩詰めは含まない。
	/// </summary>
	N02_Drop,

	/// <summary>
	/// Capture + (歩 の駒を取らない成る手)
	/// </summary>
	N03_CapturePlusPro,

	/// <summary>
	/// NonCapture - (歩 の駒を取らない成る手) - (香の三段目への駒を取らない不成)
	/// </summary>
	N04_NonCaptureMinusPro,

	/// <summary>
	/// 特定の位置への取り返しの手
	/// </summary>
	N05_Recapture,

	/// <summary>
	/// 王手回避。歩, 飛, 角 の不成はは含まない。
	/// </summary>
	N06_Evasion,

	/// <summary>
	/// 王手が掛かっていないときの合法手 (玉の移動による自殺手、pinされている駒の移動による自殺手は回避しない。)
	/// </summary>
	N07_NonEvasion,

	/// <summary>
	/// 王手が掛かっていれば Evasion, そうでないなら NonEvasion を生成し、
	/// 玉の自殺手と pin されてる駒の移動による自殺手を排除。(連続王手の千日手は排除しない。)
	/// </summary>
	N08_Legal,

	/// <summary>
	/// Legal + 歩, 飛, 角 の不成、香の二段目の不成、香の三段目への駒を取らない不成を生成
	/// </summary>
	N09_LegalAll,

	/// <summary>
	/// 
	/// </summary>
	N10_MoveTypeNone
};
