#include "muz_5a24b1c_piece_view.hpp"
#include "muz_5a25b_board_view.hpp"
#include <iomanip>   // ← これ必須！ setw, right とか入ってる


// ========================================
// 主要メソッド
// ========================================


void MuzBoardView::print(const MuzBoardModel& b)
{
    auto pretty_piece = [&](const Square sq) -> std::string
    {
        return MuzPieceView::pretty(b.get_piece(sq));
    };

    std::cout
        << "  9   8   7   6   5   4   3   2   1\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M91)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M81)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M71)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M61)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M51)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M41)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M31)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M21)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M11)
        << "| 一\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M92)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M82)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M72)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M62)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M52)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M42)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M32)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M22)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M12)
        << "| 二\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M93)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M83)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M73)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M63)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M53)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M43)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M33)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M23)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M13)
        << "| 三\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M94)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M84)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M74)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M64)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M54)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M44)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M34)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M24)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M14)
        << "| 四\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M95)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M85)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M75)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M65)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M55)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M45)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M35)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M25)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M15)
        << "| 五\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M96)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M86)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M76)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M66)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M56)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M46)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M36)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M26)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M16)
        << "| 六\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M97)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M87)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M77)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M67)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M57)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M47)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M37)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M27)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M17)
        << "| 七\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M98)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M88)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M78)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M68)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M58)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M48)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M38)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M28)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M18)
        << "| 八\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M99)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M89)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M79)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M69)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M59)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M49)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M39)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M29)
        << "|" << std::right << std::setw(3) << pretty_piece(Square::M19)
        << "| 九\n"
        << "+---+---+---+---+---+---+---+---+---+\n"
        ;
}
