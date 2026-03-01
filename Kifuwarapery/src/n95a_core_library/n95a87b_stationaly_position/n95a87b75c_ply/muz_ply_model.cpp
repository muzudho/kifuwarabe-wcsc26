#include "muz_ply_model.hpp"
#include <string_view>
#include <charconv>     // ← これが大事！ parse() で std::from_chars を使ってる


// ========================================
// 生成／破棄
// ========================================


std::optional<MuzPlyModel> MuzPlyModel::from_string(MuzTurnModel _turn, std::string_view half_ply_str)
{
    auto result = MuzPlyModel::parse(_turn, half_ply_str);
	return MuzPlyModel(result.value());
}


MuzPlyModel::MuzPlyModel(RadixHalfPly game_ply)
{
    this->radix_half_ply_ = game_ply;
}


// ========================================
// 主要メソッド
// ========================================


bool MuzPlyModel::update_from_string(MuzTurnModel turn, std::string_view half_ply_str)
{
    auto radix_half_ply = MuzPlyModel::parse(turn, half_ply_str);
	if (radix_half_ply) {
		this->radix_half_ply_ = radix_half_ply.value();
		return true;
	}

	return false;
}


// ========================================
// サブルーチン
// ========================================


std::optional<RadixHalfPly> MuzPlyModel::parse(MuzTurnModel _turn, std::string_view half_ply_str)
{
	// 空 or 空白だけ → 即失敗
	if (half_ply_str.empty()) return std::nullopt;

	int half_ply = 0;  // 初期化しておく（安全のため）

	// この部分が C++17〜 で導入された高速整数パース
	auto [ptr, ec] = std::from_chars(
		half_ply_str.data(),
		half_ply_str.data() + half_ply_str.size(),
		half_ply
	);

	// 1. パース失敗（数字が1つもなかった）
	// 2. 全部消費されてない（末尾にゴミがついてる）
	// → 両方チェックするのがベストプラクティス
	if (ec != std::errc{} || ptr != half_ply_str.data() + half_ply_str.size()) return std::nullopt;

	// ここまで来たら value は有効な整数
	// 手数として負数は普通おかしいので弾くのもアリ
	if (half_ply <= 0) return std::nullopt;

	// ボードゲームは、開始局面のとき、これから指す手を n 手目と数える。つまり 1 から始まる。これを仮に［手目］と呼ぶことにする（＾～＾）
	// 指した数は、開始局面のとき、 0。これを［手数］と呼ぶことにする（＾～＾）
	// 
	// チェスの手目は ply。開始局面のとき 1。チェスの先手は白番。最初の白番と黒番がセットで終えて 2 ply になる。
	// 将棋の手目は half_ply。開始局面のとき 1。将棋の先手は黒番。最初の黒番が終えて 2 half_ply、次の白番が終えて 3 half_ply になる。
	// 
	// 対局を記録する方式で、チェスでは人間もコンピューターも FEN を使い、将棋では人間もコンピューターもまちまちだが、
	// Stockfish 系の将棋の思考エンジンは SFEN を使っている。
	// FEN では ply を記録する。
	// SFEN では ply を記録するのか、 half_ply を記録するのかは実装による。というか GUI［将棋所］では活用されておらず。常に 1 が入っている。
	// 
	// しかし、開始局面で 1 から始まって記録されているのは、コンピューターを使って式を立てるにはめんどくさいので、
	// 人間の常識を無視して 0 から始めたい（＾～＾）
	// そこで、 ply から 1 引いたものを仮に radix_ply と造語し、
	// half_ply から 1 引いたものを radix_half_ply と造語することにする（＾～＾）
	// つまり、radix って付いてたら -1 （＾～＾）
	// 
	// ここで、［大樹の枝］の元となる［ストックフィッシュ］はチェスの思考エンジンで、game_ply を使っている。
	// これは radix_half_ply と同じ考え方をしている。
	// つまり、コンピューター将棋を作る上では、都合がいい（＾～＾）
	// 
	// ply を、game_ply に変換するには、「2*(ply-1) + (自分が先手の色なら0、後手の色なら1)」という形でイケる（＾～＾）
	// ［ストックフィッシュ］の `Position::set` は FEN を読込むから当然 はこちら。
	// ［大樹の枝］の `Position::set` はストックフィッシュと実装が同じ。（SFEN が ply なのか half_ply なのかはっきりしないのが悪い）
	// 
	// 頑固一徹な［きふわらぷりーＲ］は将棋の思考エンジンなので、SFEN には half_ply が記録されてるだろうと勝手に決めつけ、
	// 「half_ply - 1」という形に変える（＾～＾）
	return (RadixHalfPly)std::max(half_ply - 1, 0);
}
