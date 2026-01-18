#include "../../header/n080_100_sysWorld/n080_100_500_common.hpp"


#if defined LEARN
/// <summary>
/// 学習時は、SYNCCOUT 変数の型を Eraser というダミークラスに変更します。
/// </summary>
Eraser SYNCCOUT;
Eraser SYNCENDL;
#endif


/// <summary>
/// メルセンヌツイスター乱数の種☆？（＾ｑ＾）？
/// </summary>
std::mt19937_64 g_randomTimeSeed(std::chrono::system_clock::now().time_since_epoch().count());


/// <summary>
/// FIXME: ミューテックスのロック、アンロックを `<<` 演算子で指定できるが、こんなん、分かりずらい（＾～＾）
/// </summary>
/// <param name="os"></param>
/// <param name="sc"></param>
/// <returns></returns>
std::ostream& operator << (std::ostream& os, SyncCout sc)
{
	static Mutex m;
	if (sc == IOLock  ) { m.lock();   }
	if (sc == IOUnlock) { m.unlock(); }
	return os;
}
