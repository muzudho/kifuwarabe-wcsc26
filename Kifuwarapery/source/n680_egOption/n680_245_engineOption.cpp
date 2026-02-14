#include <ostream>
#include "../../header/n680_egOption/n680_245_engineOption.hpp"
#include "../../src/layer_game_engine/game_engine_storage.hpp"


/// <summary>
///
/// </summary>
/// <param name="v"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(const char* v, Fn* f, GameEngineStorageOurCarriage* s) : EngineOptionable(v, f, s)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(const bool v, Fn* f, GameEngineStorageOurCarriage* s) : EngineOptionable(v, f, s)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(Fn* f, GameEngineStorageOurCarriage* s) : EngineOptionable(f, s)
{
}


/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <param name="f"></param>
/// <param name="s"></param>
EngineOption::EngineOption(const int v, const int min, const int max, Fn* f, GameEngineStorageOurCarriage* s) : EngineOptionable(v, min, max, f, s)
{
}

