#include "catch.hpp"
#include "XMLParser.hpp"
#include "GameManager.hpp"
#include "checkBoard.hpp"

using namespace App;
using namespace Logic;
using namespace Model;
using namespace Util;

TEST_CASE("Test Replays", "[app]") {
    auto parser = XMLParser();
    auto state  = GameManager(parser.getColorsInGamePtr());

    std::string inp = "";
    std::vector<Message> result;

    SECTION("Can parse only startPiece") {
        // We have two entries as the last one is always omitted (send again by the actual GameServer)
        inp =   "startPiece:PENTO_U\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_U\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"0\" y=\"0\"/></piece></data>";
        parser.splitAndParseReplay(inp, result);

        REQUIRE(result.size() == 1);
        REQUIRE(result[0].type == MsgType::GAMESTATE);

        auto payload = std::any_cast<MementoMsg>(result[0].payload);

        REQUIRE(payload.startPiece == 10);

        state.updateWithMemento(payload);

        const auto& gState = state.getManagedState();
        REQUIRE(gState.initialPiece == 10);
        REQUIRE(gState.getTurn() == 0);
        REQUIRE(gState.getCurrentPieceColor() == PieceColor::BLUE);

        const auto& board = gState.getBoard();
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                REQUIRE(board.at(x, y) == PieceColor::NONE);
            }
        }
    }

    SECTION("Can parse small consistent replay") {
        #pragma region InpSmallReplay
        inp =   "startPiece:PENTO_U\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_U\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"0\" y=\"0\"/></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_U\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"17\" y=\"0\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_U\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"0\" y=\"18\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_U\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"17\" y=\"18\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_S\" rotation=\"LEFT\" isFlipped=\"true\"><position x=\"2\" y=\"2\" /></piece></data>";
        #pragma endregion
        parser.splitAndParseReplay(inp, result);

        REQUIRE(result.size() == 5);
        for (const auto msg : result) {
            REQUIRE(msg.type == MsgType::GAMESTATE);
            auto payload = std::any_cast<MementoMsg>(msg.payload);
            state.updateWithMemento(payload);
        }

        const auto& gState = state.getManagedState();
        REQUIRE(gState.initialPiece == 10);
        REQUIRE(gState.getTurn() == 4);
        REQUIRE(gState.getCurrentPieceColor() == PieceColor::BLUE);

        const auto& board = gState.getBoard();
        BoardPositions blue{{0,0},{0,1},{1,1},{2,0},{2,1}};
        BoardPositions red{{0,18},{0,19},{1,19},{2,18},{2,19}};
        BoardPositions yellow{{17,0},{17,1},{18,1},{19,0},{19,1}};
        BoardPositions green{{17,18},{17,19},{18,19},{19,18},{19,19}};
        REQUIRE(checkBoard(board, blue, red, yellow, green) == BoardPositions{});
    }

    SECTION("Can parse complete game replay") {
        #pragma region InpCompleteReplay
        inp =   "startPiece:PENTO_Z\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_Z\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"0\" y=\"0\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_Z\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"17\" y=\"0\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_Z\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"0\" y=\"17\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_Z\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"17\" y=\"17\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_S\" rotation=\"LEFT\" isFlipped=\"true\"><position x=\"2\" y=\"3\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_S\" rotation=\"LEFT\" isFlipped=\"true\"><position x=\"17\" y=\"3\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_S\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"3\" y=\"18\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_S\" rotation=\"MIRROR\" isFlipped=\"true\"><position x=\"13\" y=\"17\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_T\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"0\" y=\"7\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_T\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"17\" y=\"7\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_T\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"7\" y=\"17\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_T\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"11\" y=\"14\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_Y\" rotation=\"RIGHT\" isFlipped=\"true\"><position x=\"3\" y=\"6\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_Y\" rotation=\"RIGHT\" isFlipped=\"true\"><position x=\"13\" y=\"2\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_Y\" rotation=\"MIRROR\" isFlipped=\"true\"><position x=\"0\" y=\"13\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_Y\" rotation=\"LEFT\" isFlipped=\"false\"><position x=\"13\" y=\"12\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_X\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"2\" y=\"10\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_X\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"14\" y=\"9\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_X\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"10\" y=\"17\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_X\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"14\" y=\"14\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_R\" rotation=\"RIGHT\" isFlipped=\"true\"><position x=\"5\" y=\"10\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_R\" rotation=\"RIGHT\" isFlipped=\"true\"><position x=\"10\" y=\"1\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_R\" rotation=\"LEFT\" isFlipped=\"false\"><position x=\"6\" y=\"14\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_R\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"17\" y=\"10\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_W\" rotation=\"LEFT\" isFlipped=\"false\"><position x=\"5\" y=\"3\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_W\" rotation=\"LEFT\" isFlipped=\"false\"><position x=\"7\" y=\"4\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_W\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"8\" y=\"12\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_W\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"10\" y=\"9\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_P\" rotation=\"NONE\" isFlipped=\"true\"><position x=\"8\" y=\"1\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_P\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"11\" y=\"4\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_P\" rotation=\"RIGHT\" isFlipped=\"true\"><position x=\"3\" y=\"13\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_P\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"18\" y=\"13\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_V\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"7\" y=\"8\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"PENTO_V\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"14\" y=\"5\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_V\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"0\" y=\"10\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_L\" rotation=\"RIGHT\" isFlipped=\"true\"><position x=\"8\" y=\"7\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_L\" rotation=\"RIGHT\" isFlipped=\"true\"><position x=\"10\" y=\"0\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"TETRO_Z\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"12\" y=\"8\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"PENTO_L\" rotation=\"LEFT\" isFlipped=\"true\"><position x=\"3\" y=\"8\" /></piece></data>\n" 
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"TETRO_Z\" rotation=\"RIGHT\" isFlipped=\"true\"><position x=\"8\" y=\"10\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_U\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"3\" y=\"0\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"TETRO_T\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"14\" y=\"0\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"DOMINO\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"9\" y=\"16\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"DOMINO\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"12\" y=\"19\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"TETRO_I\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"2\" y=\"13\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"MONO\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"8\" y=\"3\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"TETRO_L\" rotation=\"LEFT\" isFlipped=\"false\"><position x=\"3\" y=\"15\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"TRIO_L\" rotation=\"LEFT\" isFlipped=\"false\"><position x=\"6\" y=\"12\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"DOMINO\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"0\" y=\"17\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"TETRO_L\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"6\" y=\"0\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"TRIO_L\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"11\" y=\"12\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"MONO\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"13\" y=\"10\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"PENTO_I\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"3\" y=\"17\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"TRIO_L\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"5\" y=\"3\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"MONO\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"2\" y=\"7\" /></piece></data>\n"   
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_U\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"14\" y=\"8\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"TETRO_L\" rotation=\"MIRROR\" isFlipped=\"true\"><position x=\"10\" y=\"4\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"YELLOW\" kind=\"DOMINO\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"3\" y=\"2\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"RED\" kind=\"TETRO_Z\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"0\" y=\"5\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"TRIO_I\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"13\" y=\"5\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"TETRO_T\" rotation=\"LEFT\" isFlipped=\"false\"><position x=\"0\" y=\"3\" /></piece></data>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>YELLOW</color></fake>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>RED</color></fake>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"GREEN\" kind=\"PENTO_V\" rotation=\"MIRROR\" isFlipped=\"false\"><position x=\"14\" y=\"4\" /></piece></data>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"TRIO_I\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"10\" y=\"11\" /></piece></data>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>YELLOW</color></fake>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>RED</color></fake>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>GREEN</color></fake>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"MONO\" rotation=\"NONE\" isFlipped=\"false\"><position x=\"8\" y=\"16\" /></piece></data>\n" 
                "<fake class=\"sc.plugin2021.SkipMove\"><color>YELLOW</color></fake>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>RED</color></fake>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>GREEN</color></fake>\n"
                "<data class=\"sc.plugin2021.SetMove\"><piece color=\"BLUE\" kind=\"TRIO_L\" rotation=\"RIGHT\" isFlipped=\"false\"><position x=\"9\" y=\"17\" /></piece></data>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>YELLOW</color></fake>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>RED</color></fake>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>GREEN</color></fake>\n"
                "<fake class=\"sc.plugin2021.SkipMove\"><color>BLUE</color></fake>";
                // The last turn would not be generated by the replay system and is only here
                // because we pop the last turn as it would normally be send by the server on connect.
                // We want to test the whole game/board here though, which is why we added the 2x fake turn
        #pragma endregion
        parser.splitAndParseReplay(inp, result);

        REQUIRE(result.size() == 77);
        for (const auto msg : result) {
            REQUIRE(msg.type == MsgType::GAMESTATE);
            auto payload = std::any_cast<MementoMsg>(msg.payload);
            state.updateWithMemento(payload);
        }

        const auto& gState = state.getManagedState();
        REQUIRE(gState.initialPiece == 17);
        REQUIRE(gState.getTurn() == 76);
        REQUIRE(gState.getCurrentPieceColor() == PieceColor::BLUE);
        // We dont 'REQUIRE(gState.isGameOver() == true);' because of an optimization that would return false

        const auto& board = gState.getBoard();
        BoardPositions blue{{0,0},{0,3},{0,4},{0,5},{0,9},{0,17},{1,0},{1,1},{1,2},{1,4},{1,7},{1,8},{1,9},{1,17},{2,2},{2,5},{2,6},{2,9},{2,11},{2,13},
            {2,14},{2,15},{2,16},{3,0},{3,1},{3,3},{3,4},{3,5},{3,7},{3,10},{3,11},{3,12},{3,17},{4,1},{4,6},{4,7},{4,11},{4,17},{5,0},{5,1},{5,5},{5,7},
            {5,12},{5,17},{6,4},{6,5},{6,7},{6,10},{6,11},{6,12},{6,17},{7,3},{7,4},{7,8},{7,11},{7,17},{8,1},{8,2},{8,8},{8,16},{9,1},{9,2},{9,3},{9,8},
            {9,9},{9,10},{9,17},{9,18},{10,0},{10,4},{10,5},{10,6},{10,11},{10,12},{10,13},{10,17},{11,0},{11,4},{12,0},{13,0},{13,1}};
        BoardPositions red{{0,6},{0,7},{0,10},{0,11},{0,12},{0,15},{0,18},{0,19},{1,5},{1,6},{1,10},{1,13},{1,14},{1,15},{1,16},{1,18},{2,7},{2,10},{2,17},
            {2,18},{3,8},{3,9},{3,13},{3,14},{3,16},{3,19},{4,9},{4,13},{4,14},{4,16},{4,19},{5,9},{5,13},{5,15},{5,16},{5,18},{5,19},{6,9},{6,14},{6,18},
            {7,14},{7,15},{7,16},{7,19},{8,12},{8,13},{8,15},{8,17},{8,18},{8,19},{9,13},{9,14},{9,16},{9,19},{10,14},{10,16},{10,18},{11,12},{11,13},
            {11,17},{11,18},{11,19},{12,12},{12,18}};
        BoardPositions yellow{{3,2},{4,2},{5,3},{5,4},{6,0},{6,3},{7,0},{7,1},{7,2},{7,6},{8,3},{8,5},{8,6},{9,4},{9,5},{10,3},{11,1},{11,2},{11,3},{11,5},
            {11,6},{12,2},{12,4},{12,5},{12,6},{12,9},{12,10},{13,3},{13,8},{13,9},{14,0},{14,2},{14,3},{14,5},{14,6},{14,7},{14,10},{15,0},{15,1},{15,3},
            {15,7},{15,9},{15,10},{15,11},{16,0},{16,3},{16,7},{16,10},{17,1},{17,2},{17,5},{17,6},{17,9},{18,1},{18,3},{18,4},{18,5},{18,7},{18,8},{18,9},
            {19,0},{19,1},{19,9}};
        BoardPositions green{{6,13},{7,12},{7,13},{8,7},{8,10},{8,11},{9,7},{9,11},{9,12},{10,7},{10,9},{10,10},{11,7},{11,8},{11,10},{11,11},{11,14},{12,11},
            {12,14},{12,15},{12,16},{12,19},{13,5},{13,6},{13,7},{13,10},{13,12},{13,14},{13,17},{13,19},{14,4},{14,8},{14,9},{14,12},{14,13},{14,15},{14,17},
            {14,18},{15,4},{15,8},{15,12},{15,14},{15,15},{15,16},{15,18},{16,4},{16,5},{16,6},{16,8},{16,9},{16,12},{16,15},{16,18},{17,11},{17,17},{18,11},
            {18,12},{18,14},{18,15},{18,17},{18,18},{18,19},{19,10},{19,11},{19,13},{19,14},{19,15},{19,19}};
        REQUIRE(checkBoard(board, blue, red, yellow, green) == BoardPositions{});
    }
}
