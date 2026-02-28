#include "muz_ply_model.hpp"
#include <string_view>
#include <charconv>     // ← これが大事！ from_string() で std::from_chars を使ってる


// ========================================
// 生成／破棄
// ========================================


// 次の手が何手目か。エラーのときは -1 を返す。
std::optional<MuzPlyModel> MuzPlyModel::from_string(MuzTurnModel turn, std::string_view half_ply_str)
{
	// 空 or 空白だけ → 即失敗
	if (half_ply_str.empty()) return std::nullopt;

	int value = 0;  // 初期化しておく（安全のため）

	// この部分が C++17〜 で導入された高速整数パース
	auto [ptr, ec] = std::from_chars(
		half_ply_str.data(),
		half_ply_str.data() + half_ply_str.size(),
		value
	);

	// 1. パース失敗（数字が1つもなかった）
	// 2. 全部消費されてない（末尾にゴミがついてる）
	// → 両方チェックするのがベストプラクティス
	if (ec != std::errc{} || ptr != half_ply_str.data() + half_ply_str.size()) return std::nullopt;

	// ここまで来たら value は有効な整数
	// 手数として負数は普通おかしいので弾くのもアリ
	if (value <= 0) return std::nullopt;

	// ボードゲームは、開始局面のとき、これから指す手を n 手目と数える。つまり 1 から始まる。これを［手目］と呼ぶことにする（＾～＾）
	// 指した数は、開始局面のとき、 0。これを［手数］と呼ぶことにする（＾～＾）
	// 
	// チェスの手目は ply。開始局面のとき 1。チェスの先手は白番。最初の白番と黒番がセットで終えて 2 ply になる。
	// 将棋の手目は half-ply。開始局面のとき 1。将棋の先手は黒番。最初の黒番が終えて 2 half-ply、次の白番が終えて 3 half-ply になる。
	// 
	// 対局を記録する方式で、チェスでは人間もコンピューターも FEN を使い、将棋では人間もコンピューターもまちまちだが、
	// Stockfish 系の将棋の思考エンジンは SFEN を使っている。
	// FEN では ply を記録し、 SFEN では half-ply を記録する。
	// 
	// しかし、開始局面で 1 から始まって記録されているのは、コンピューターを使って式を立てるにはめんどくさいので、
	// 人間の常識を無視して 0 から始めたい（＾～＾）
	// そこで、 ply から 1 引いたものを game-ply、
	// half-ply から 1 引いたものを game-half-ply と呼ぶことにする（＾～＾）
	// つまり、game って付いてたら -1 （＾～＾）
	// 
	// ［大樹の枝］の元となる［ストックフィッシュ］はチェスの思考エンジンなので、当然 game-ply を使う（＾～＾）
	// ply を、game-ply に変換するには、「2*(ply-1) + (自分が先手の色なら0、後手の色なら1)」という形でイケる（＾～＾）
	//
	// とりあえず、［きふわらぷりーＲ］は将棋の思考エンジンだが、ひとまず game-ply を使うことにする（＾～＾）。
	value = std::max(2 * (value - 1), 0) + static_cast<int>(turn.is_white());
	return MuzPlyModel(value);
}


MuzPlyModel::MuzPlyModel(Ply game_ply)
{
    this->game_ply_ = game_ply;
}
