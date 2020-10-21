#include "Message.hpp"

namespace App {
    
    Message::Message(MsgType type, std::any payload) : type(type), payload(payload) {}

    ResultMsg::ResultMsg(std::array<uint8_t, 2> score, std::array<ResultEnd, 2> end, std::array<ResultCause, 2> cause) : score(score), end(end), cause(cause) {}

    MementoMsg::MementoMsg(uint8_t startPiece, std::optional<uint32_t> lastMove, std::vector<Model::PieceColor> colorsInGame) : startPiece(startPiece), lastMove(lastMove), colorsInGame(colorsInGame) {}

} // namespace App
