#include "color.hpp"

namespace Model {

    std::ostream& operator << (std::ostream& os, const PieceColor& color) {
        switch (color) {
            case PieceColor::RED:
                os << "Red";
                break;
            case PieceColor::BLUE:
                os << "Blue";
                break;
            case PieceColor::GREEN:
                os << "Green";
                break;
            case PieceColor::YELLOW:
                os << "Yellow";
                break;
            case PieceColor::NONE:
                os << "None";
                break;
            case PieceColor::OBSTRUCTED:
                os << "Obstructed";
                break;
        }

        return os;
    }

    std::ostream& operator << (std::ostream& os, const PlayerColor& color) {
        switch (color) {
            case PlayerColor::RED:
                os << "RED";
                break;
            case PlayerColor::BLUE:
                os << "BLUE";
                break;
        }

        return os;
    }

}