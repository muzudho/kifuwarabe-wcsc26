#include <map>
#include "../../header/n165_movStack/n165_300_moveType.hpp"
#include "../../header/n165_movStack/n165_400_move.hpp"
#include "../../header/n165_movStack/n165_600_convMove.hpp"
#include "../../header/n220_position/n220_645_gameStats.hpp"
#include "../../header/n220_position/n220_650_position.hpp"
#include "../../header/n350_pieceTyp/n350_030_makePromoteMove.hpp"
#include "../../header/n407_moveGen_/n407_900_moveList.hpp"
#include "../../header/n720_usi_____/n720_260_usiOperation.hpp"
#include "../../src/layer_game_engine/muz_game_engine_storage_model.hpp"
#include "../../src/lib_shogi/muz_shogi_model.hpp"


/// <summary>
/// CSA形式の駒種類文字列を PieceType に変換するマップ☆ 
/// </summary>
class StringToPieceTypeCSA : public std::map<std::string, PieceType> {


public:


	/// <summary>
	/// 生成。
	/// </summary>
	StringToPieceTypeCSA() {
		(*this)["FU"] = N01_Pawn;
		(*this)["KY"] = N02_Lance;
		(*this)["KE"] = N03_Knight;
		(*this)["GI"] = N04_Silver;
		(*this)["KA"] = N05_Bishop;
		(*this)["HI"] = N06_Rook;
		(*this)["KI"] = N07_Gold;
		(*this)["OU"] = N08_King;
		(*this)["TO"] = N09_ProPawn;
		(*this)["NY"] = N10_ProLance;
		(*this)["NK"] = N11_ProKnight;
		(*this)["NG"] = N12_ProSilver;
		(*this)["UM"] = N13_Horse;
		(*this)["RY"] = N14_Dragon;
	}


	/// <summary>
    /// 文字列から PieceType を取得する。 
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	PieceType value(const std::string& str) const {
		return this->find(str)->second;
	}


	/// <summary>
    /// 合法な文字列かどうか。
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	bool isLegalString(const std::string& str) const {
		return (this->find(str) != this->end());
	}
};
const StringToPieceTypeCSA g_stringToPieceTypeCSA;


/// <summary>
/// 考え始めるのはここ。
/// </summary>
/// <param name="pos"></param>
/// <param name="ssCmd"></param>
void UsiOperation::Go(GameStats& gameStats, const Position& pos, std::istringstream& ssCmd)
{
	LimitsDuringGo limits;
	std::vector<Move> moves;
	std::string token;

	// go コマンドを分解（＾▽＾）
	while (ssCmd >> token) {
		// 相手の思考時間中にも思考（ポンダー）しろだぜ（＾▽＾）
		if      (token == "ponder"     ) { limits.m_canPonder = true; }

		// TODO: 時間管理のために Positon 変数に［残り持ち時間］を記憶しておきたいぜ（＾～＾）
		// 先手の残り時間（ミリ秒）
		else if (token == "btime"      )
		{
			long long milliseconds;
			ssCmd >> milliseconds;
			limits.SetTimeLeftFromStream(Color::Black, milliseconds);
			gameStats.SetTimeLeftFromStream(Color::Black, milliseconds);
		}

        // 後手の残り時間（ミリ秒）
		else if (token == "wtime"      )
		{
			long long milliseconds;
			ssCmd >> milliseconds;
			limits.SetTimeLeftFromStream(Color::White, milliseconds);
			gameStats.SetTimeLeftFromStream(Color::White, milliseconds);
		}

        // 時間無制限で思考だぜ（＾▽＾）
		else if (token == "infinite"   ) { limits.m_isInfinite = true; }

        // 秒読み、ムーブタイムだぜ（＾▽＾）
		else if (token == "byoyomi" ||
				 token == "movetime"   ) {
			// btime wtime の後に byoyomi が来る前提になっているので良くない。
			limits.SetMoveTimeFromStream(ssCmd);
			if (limits.GetMoveTime() != 0) {
//#if !defined(FISCHER_RULE)
				// フィッシャー・ルールでないときは、秒読みがあるのだろう☆（＾ｑ＾）
				limits.DecrementMoveTime( pos.GetOurCarriage()->m_engineSettings.GetOptionByKey("Byoyomi_Margin"));
//#endif
			}
		}

        // 深さだぜ（＾▽＾）
		else if (token == "depth"      ) { ssCmd >> limits.m_depth; }

        // ノード数だぜ（＾▽＾）
		else if (token == "nodes"      ) { ssCmd >> limits.m_visitedNodesNum; }

        // 指し手リストだぜ（＾▽＾）
		else if (token == "searchmoves") {
			UsiOperation usiOperation;
			while (ssCmd >> token)
			{
				moves.push_back(usiOperation.UsiToMove(pos, token));
			}
		}

		// 追加☆（＾ｑ＾）
		else if (token == "winc") {
			ssCmd >> limits.m_increment[Color::White];
		}

		// 追加☆（＾ｑ＾）
		else if (token == "binc") {
			ssCmd >> limits.m_increment[Color::Black];
		}
	}
	pos.GetOurCarriage()->m_ourMoves = moves;

	// 思考を開始☆
	pos.GetOurCarriage()->m_pub.StartThinking(gameStats, pos, limits, moves);
}


#if defined LEARN
/// <summary>
/// 学習用。通常の go 呼び出しは文字列を扱って高コストなので、大量に探索の開始、終了を行う学習では別の呼び出し方にする。
/// </summary>
/// <param name="GetPos"></param>
/// <param name="GetDepth"></param>
/// <param name="GetMove"></param>
void UsiOperation::Go(const Position& GetPos, const Ply GetDepth, const Move GetMove) {
	LimitsDuringGo m_limits;
	std::vector<Move> moves;
	m_limits.GetDepth = GetDepth;
	moves.push_back(GetMove);
	GetPos.GetRucksack()->m_ownerHerosPub.StartThinking(gameStats, GetPos, m_limits, moves);
}
#endif



#if !defined NDEBUG
/// <summary>
/// for debug
/// </summary>
/// <param name="GetPos"></param>
/// <param name="moveStr"></param>
/// <returns></returns>
Move UsiOperation::usiToMoveDebug(const Position& GetPos, const std::string& moveStr) {
	for (MoveList<N09_LegalAll> ml(GetPos); !ml.IsEnd(); ++ml) {
		if (moveStr == ml.GetMove().ToUSI()) {
			return ml.GetMove();
		}
	}
	return g_MOVE_NONE; // Move::GetMoveNone();
}


/// <summary>
/// for debug 
/// </summary>
/// <param name="GetPos"></param>
/// <param name="moveStr"></param>
/// <returns></returns>
Move UsiOperation::csaToMoveDebug(const Position& GetPos, const std::string& moveStr) {
	for (MoveList<N09_LegalAll> ml(GetPos); !ml.IsEnd(); ++ml) {
		if (moveStr == ml.GetMove().ToCSA()) {
			return ml.GetMove();
		}
	}
	return g_MOVE_NONE; // Move::GetMoveNone();
}
#endif


/// <summary>
/// USI形式の指し手文字列を Move に変換する☆ 
/// </summary>
/// <param name="pos"></param>
/// <param name="moveStr"></param>
/// <returns></returns>
Move UsiOperation::UsiToMove(const Position& pos, const std::string& moveStr) {
	const Move move = UsiToMoveBody(pos, moveStr);
	assert(move == this->usiToMoveDebug(pos, moveStr));
	return move;
}


/// <summary>
/// CSA形式の指し手文字列を Move に変換する☆ 
/// </summary>
/// <param name="pos"></param>
/// <param name="moveStr"></param>
/// <returns></returns>
Move UsiOperation::CsaToMove(const Position& pos, const std::string& moveStr) {
	const Move move = CsaToMoveBody(pos, moveStr);
	assert(move == this->csaToMoveDebug(pos, moveStr));
	return move;
}


/// <summary>
/// position コマンドの処理だぜ（＾▽＾） 
/// </summary>
/// <param name="pos"></param>
/// <param name="ssCmd"></param>
void UsiOperation::SetPosition(Position& pos, std::istringstream& ssCmd)
{
	std::string token;
	std::string sfen;

    // position コマンドを分解（＾▽＾）
	ssCmd >> token;

	// 平手初期局面だぜ（＾▽＾）
	if (token == "startpos") {
		sfen = g_SFEN_STARTPOS_STR;
		ssCmd >> token; // "moves" が入力されるはず。
	}

    // SFEN局面設定だぜ（＾▽＾）
	else if (token == "sfen") {
		while (ssCmd >> token && token != "moves") {
			sfen += token + " ";
		}
	}
	else { return; }

    // 指し手リストだぜ（＾▽＾）
	pos.Set(sfen, pos.GetOurCarriage()->m_pub.GetFirstCaptain());

    // 指し手を進めるぜ（＾▽＾）
	pos.GetOurCarriage()->m_setUpStates = StateStackPtr(new std::stack<StateInfo>());

	Ply currentPly = pos.GetGamePly();

	while (ssCmd >> token) {
        // 指し手文字列を Move に変換（＾▽＾）
		const Move move = this->UsiToMove(pos, token);
		if (move.IsNone()) { break; }

        // 状態情報を積むぜ（＾▽＾）
		pos.GetOurCarriage()->m_setUpStates->push(StateInfo());

        // 指し手を指すぜ（＾▽＾）
		pos.GetTurn() == Color::Black	// 自分は先手か？
			?
			pos.DoMove<Color::Black,Color::White>(move, pos.GetOurCarriage()->m_setUpStates->top())
			:
			pos.DoMove<Color::White,Color::Black>(move, pos.GetOurCarriage()->m_setUpStates->top())	// 自分が後手のとき。
			;

		++currentPly;
	}

    // 現在の手数を設定（＾▽＾）
	pos.SetStartPosPly(currentPly);
}


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <param name="moveStr">USI 形式の指し手文字列</param>
/// <returns></returns>
Move UsiOperation::UsiToMoveBody(const Position& pos, const std::string& moveStr) {
	Move move;

    // 指し手文字列の長さチェック
	if (g_charToPieceUSI.IsLegalChar(moveStr[0])) {
		// drop
		const PieceType ptTo = ConvPiece::TO_PIECE_TYPE10(g_charToPieceUSI.GetValue(moveStr[0]));
		if (moveStr[1] != '*') { return g_MOVE_NONE; }

		const File toFile = ConvFile::FROM_CHAR_USI10(moveStr[2]);
		const Rank toRank = ConvRank::FROM_CHAR_USI10(moveStr[3]);
		if (!ConvSquare::CONTAINS_OF20(toFile, toRank)) { return g_MOVE_NONE; }

		const Square to = ConvSquare::FROM_FILE_RANK10(toFile, toRank);
		move = ConvMove::Convert30_MakeDropMove_da(ConvMove::FROM_PIECETYPE_DA10(ptTo), to);
	}
	else {
		const File fromFile = ConvFile::FROM_CHAR_USI10(moveStr[0]);
		const Rank fromRank = ConvRank::FROM_CHAR_USI10(moveStr[1]);
		if (!ConvSquare::CONTAINS_OF20(fromFile, fromRank)) { return g_MOVE_NONE; }

		const Square from = ConvSquare::FROM_FILE_RANK10(fromFile, fromRank);
		const File toFile = ConvFile::FROM_CHAR_USI10(moveStr[2]);
		const Rank toRank = ConvRank::FROM_CHAR_USI10(moveStr[3]);
		if (!ConvSquare::CONTAINS_OF20(toFile, toRank)) { return g_MOVE_NONE; }

		const Square to = ConvSquare::FROM_FILE_RANK10(toFile, toRank);
		if (moveStr[4] == '\0') {
			move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_CaptureCategory(
				ConvMove::FROM_PIECETYPE_ONBOARD10( ConvPiece::TO_PIECE_TYPE10(pos.GetPiece(from))), // （＾ｑ＾）
				from, to, pos);
		}
		else if (moveStr[4] == '+') {
			if (moveStr[5] != '\0') { return g_MOVE_NONE; }

			move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_CaptureCategory(
				ConvMove::FROM_PIECETYPE_ONBOARD10( ConvPiece::TO_PIECE_TYPE10(pos.GetPiece(from))),
				from, to, pos);
			MakePromoteMove::APPEND_PROMOTE_FLAG(move);
		}
		else { return g_MOVE_NONE; }
	}

	if (
		(
            pos.GetTurn() == Color::Black	// 自分が先手か
			?
			pos.MoveIsPseudoLegal<Color::Black,Color::White>(move, true)
			:
            pos.MoveIsPseudoLegal<Color::White, Color::Black>(move, true)	// 自分が後手のとき。
		)		
		&&
		(
			pos.GetTurn()==Color::Black
			?
			pos.IsPseudoLegalMoveIsLegal<false, false,Color::Black,Color::White>(move, pos.GetPinnedBB())
			:
			pos.IsPseudoLegalMoveIsLegal<false, false,Color::White,Color::Black>(move, pos.GetPinnedBB())
		)
	) { return move; }

    // 非合法手（＾▽＾）
	return g_MOVE_NONE;
}


/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <param name="moveStr">CSA 形式の指し手文字列。</param>
/// <returns></returns>
Move UsiOperation::CsaToMoveBody(const Position& pos, const std::string& moveStr) {
	if (moveStr.size() != 6) { return g_MOVE_NONE; }

	const File toFile = ConvFile::FROM_CHAR_CSA10(moveStr[2]);
	const Rank toRank = ConvRank::FROM_CHAR_CSA10(moveStr[3]);
	if (!ConvSquare::CONTAINS_OF20(toFile, toRank)) { return g_MOVE_NONE; }

	const Square to = ConvSquare::FROM_FILE_RANK10(toFile, toRank);
	const std::string ptToString(moveStr.begin() + 4, moveStr.end());
	if (!g_stringToPieceTypeCSA.isLegalString(ptToString)) { return g_MOVE_NONE; }

	const PieceType ptTo = g_stringToPieceTypeCSA.value(ptToString);
	Move move;
	if (moveStr[0] == '0' && moveStr[1] == '0') {
		// drop
		move = ConvMove::Convert30_MakeDropMove_da(ConvMove::FROM_PIECETYPE_DA10(ptTo), to);
	}
	else {
		const File fromFile = ConvFile::FROM_CHAR_CSA10(moveStr[0]);
		const Rank fromRank = ConvRank::FROM_CHAR_CSA10(moveStr[1]);
		if (!ConvSquare::CONTAINS_OF20(fromFile, fromRank)) { return g_MOVE_NONE; }

		const Square from = ConvSquare::FROM_FILE_RANK10(fromFile, fromRank);
		PieceType ptFrom = ConvPiece::TO_PIECE_TYPE10(pos.GetPiece(from));
		if (ptFrom == ptTo) {
			// non promote
			move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_CaptureCategory(
				ConvMove::FROM_PIECETYPE_ONBOARD10(ptFrom),
				from, to, pos);
		}
		else if (ptFrom + PTPromote == ptTo) {
			// promote
			move = g_makePromoteMove.GetSelectedMakeMove_ExceptPromote_CaptureCategory(
				ConvMove::FROM_PIECETYPE_ONBOARD10(ptFrom),
				from, to, pos);
			MakePromoteMove::APPEND_PROMOTE_FLAG(move);//, N00_Capture, ptFrom
		}
		else { return g_MOVE_NONE; }	// 非合法手（＾▽＾）
	}

	if (
		(
			pos.GetTurn() == Color::Black	// 自分が先手か。
			?
            pos.MoveIsPseudoLegal<Color::Black, Color::White>(move, true) // 自分が先手のとき、疑似合法手かどうかのチェック☆
			:
			pos.MoveIsPseudoLegal<Color::White,Color::Black>(move, true) // 自分が後手。
		)		
		&&
		(
            pos.GetTurn() == Color::Black	// 自分が先手か。
			?
            pos.IsPseudoLegalMoveIsLegal<false, false, Color::Black, Color::White>(move, pos.GetPinnedBB())	// 疑似合法手が合法手かどうかのチェック☆
			:
			pos.IsPseudoLegalMoveIsLegal<false, false,Color::White,Color::Black>(move, pos.GetPinnedBB())
			)
	){ return move; }	// 合法な指し手☆

    // 不正な指し手☆
	return g_MOVE_NONE;
}
