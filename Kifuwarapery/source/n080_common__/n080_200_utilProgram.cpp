#include <windows.h> // ヘッダー・ファイルに書くとエラーになる。
#include "../../header/n080_common__/n080_100_common.hpp"
#include "..\..\header\n080_common__\n080_200_utilProgram.hpp"


/// <summary>
/// 
/// </summary>
void UtilProgram::ErrorBegin()
{
	SetLastError(NO_ERROR);		//エラー情報をクリアする
}


/// <summary>
/// 
/// </summary>
void UtilProgram::ErrorEnd()
{
	LPVOID lpMsgBuf;
	FormatMessage(				//エラー表示文字列作成
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	//MessageBox(NULL, (const char*)lpMsgBuf, NULL, MB_OK);	//メッセージ表示
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, NULL, MB_OK);	//メッセージ表示
	LocalFree(lpMsgBuf);
}


/// <summary>
/// カレントディレクトリーを出力
/// </summary>
void UtilProgram::ShowCurrentDirectory()
{
	TCHAR crDir[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH + 1, crDir);
	crDir[MAX_PATH] = '\0';		// 念のため終端NULLを保証

	// crDir 配列をそのまま出力すると数になってしまった。
	// Current directory=[000000E05BF83430]
	//SYNCCOUT << "Current directory=[" << crDir << "]" << SYNCENDL;

	// TCHARがwchar_t（Unicode）の場合、標準のcout系ストリームではアドレスが表示される問題を回避
	// ここでは、WideCharToMultiByteでANSI文字列に変換して出力（簡易版。必要に応じてUTF-8などに調整）
	char ansiDir[MAX_PATH + 1];
	int ansiLen = WideCharToMultiByte(CP_ACP, 0, crDir, -1, ansiDir, MAX_PATH + 1, NULL, NULL);
	if (ansiLen > 0) {
		ansiDir[ansiLen - 1] = '\0'; // 安全のため
		SYNCCOUT << "Current directory=[" << ansiDir << "]" << SYNCENDL;
	}
	else {
		SYNCCOUT << "Current directory=[Error: Failed to convert path]" << SYNCENDL;
	}
}
