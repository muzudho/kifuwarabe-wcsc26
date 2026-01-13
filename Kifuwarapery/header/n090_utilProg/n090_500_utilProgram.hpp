#pragma once


//────────────────────────────────────────────────────────────────────────────────
// ちょっと使うので追加しただけ（＾～＾）
//────────────────────────────────────────────────────────────────────────────────


/// <summary>
/// プログラム中でちょっと使うもの。
/// ディレクトリー作成時の前後を挟んだり。
/// </summary>
class UtilProgram {


public:


	/// <summary>
	/// エラーが起こりそうな処理の前に書く
	/// </summary>
	void BeginHandleError();


	/// <summary>
	/// エラーが起こりそうな処理が終わったところに書く
	/// </summary>
	void EndHandleError();


	/// <summary>
	/// カレントディレクトリーを出力
	/// </summary>
	void ShowCurrentDirectory();
};
