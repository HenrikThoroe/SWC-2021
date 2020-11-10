#include "catch.hpp"
#include "XMLParser.hpp"

using namespace App;
using namespace Model;
using namespace Util;

TEST_CASE("Test XMLParser", "[app]") {
    auto parser = XMLParser();

    std::string inp = "";
    std::vector<Message> result;

    SECTION("Can parse Joined") {
        inp = "<joined roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\"/>";
        parser.splitAndParseMessages(inp, result);

        REQUIRE(result.size() == 1);
        REQUIRE(result[0].type == MsgType::JOINED);

        auto payload = std::any_cast<std::string>(result[0].payload);

        REQUIRE(payload == "0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5");
    }

    SECTION("Can parse first Memento") {
        #pragma region InpFirstMemento
        inp =   "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"memento\">"
                        "<state class=\"state\" currentColorIndex=\"0\" turn=\"0\" round=\"1\" startPiece=\"PENTO_T\">"
                        "<startTeam class=\"team\">ONE</startTeam>"
                        "<board/>"
                        "<blueShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_T</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</blueShapes>"
                        "<yellowShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_T</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</yellowShapes>"
                        "<redShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_T</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</redShapes>"
                        "<greenShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_T</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</greenShapes>"
                        "<lastMoveMono class=\"linked-hash-map\"/>"
                        "<orderedColors>"
                            "<color>BLUE</color>"
                            "<color>YELLOW</color>"
                            "<color>RED</color>"
                            "<color>GREEN</color>"
                        "</orderedColors>"
                        "<first displayName=\"One\">"
                            "<color class=\"team\">ONE</color>"
                        "</first>"
                        "<second displayName=\"Two\">"
                            "<color class=\"team\">TWO</color>"
                        "</second>"
                        "<startColor>BLUE</startColor>"
                        "</state>"
                    "</data>"
                "</room>";
        #pragma endregion
        parser.splitAndParseMessages(inp, result);

        REQUIRE(result.size() == 1);
        REQUIRE(result[0].type == MsgType::GAMESTATE);

        auto payload = std::any_cast<MementoMsg>(result[0].payload);

        REQUIRE(payload.lastMove == std::nullopt);
        REQUIRE(payload.startPiece == 19);
        REQUIRE(payload.currentTurn == 0);

        const std::vector<PieceColor>* const colorsIG = parser.getColorsInGamePtr();
        REQUIRE(colorsIG->size() == 4);
        REQUIRE(std::find(colorsIG->begin(), colorsIG->end(), PieceColor::BLUE)   != colorsIG->end());
        REQUIRE(std::find(colorsIG->begin(), colorsIG->end(), PieceColor::YELLOW) != colorsIG->end());
        REQUIRE(std::find(colorsIG->begin(), colorsIG->end(), PieceColor::RED)    != colorsIG->end());
        REQUIRE(std::find(colorsIG->begin(), colorsIG->end(), PieceColor::GREEN)  != colorsIG->end());
    }

    SECTION("Can parse normal Memento") {

        #pragma region InpNormalMemento
        inp =   "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"memento\">"
                        "<state class=\"state\" currentColorIndex=\"3\" turn=\"7\" round=\"2\" startPiece=\"PENTO_T\">"
                        "<startTeam class=\"team\">ONE</startTeam>"
                        "<board>"
                            "<field x=\"0\" y=\"0\" content=\"GREEN\"/>"
                            "<field x=\"19\" y=\"0\" content=\"YELLOW\"/>"
                            "<field x=\"0\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"1\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"2\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"17\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"18\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"19\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"0\" y=\"2\" content=\"GREEN\"/>"
                            "<field x=\"16\" y=\"2\" content=\"YELLOW\"/>"
                            "<field x=\"19\" y=\"2\" content=\"YELLOW\"/>"
                            "<field x=\"16\" y=\"3\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"3\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"4\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"18\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"17\" y=\"16\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"16\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"3\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"18\" y=\"17\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"1\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"2\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"18\" y=\"18\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"3\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"17\" y=\"19\" content=\"RED\"/>"
                            "<field x=\"18\" y=\"19\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"19\" content=\"RED\"/>"
                        "</board>"
                        "<blueShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</blueShapes>"
                        "<yellowShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</yellowShapes>"
                        "<redShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</redShapes>"
                        "<greenShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</greenShapes>"
                        "<lastMoveMono class=\"linked-hash-map\"/>"
                        "<orderedColors>"
                            "<color>BLUE</color>"
                            "<color>RED</color>"
                            "<color>GREEN</color>"
                        "</orderedColors>"
                        "<first displayName=\"One\">"
                            "<color class=\"team\">ONE</color>"
                        "</first>"
                        "<second displayName=\"Two\">"
                            "<color class=\"team\">TWO</color>"
                        "</second>"
                        "<lastMove class=\"sc.plugin2021.SetMove\">"
                            "<piece color=\"RED\" kind=\"PENTO_U\" rotation=\"MIRROR\" isFlipped=\"false\">"
                            "<position x=\"17\" y=\"15\"/>"
                            "</piece>"
                        "</lastMove>"
                        "<startColor>BLUE</startColor>"
                        "</state>"
                    "</data>"
                "</room>"
                "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"memento\">"
                        "<state class=\"state\" currentColorIndex=\"3\" turn=\"7\" round=\"2\" startPiece=\"PENTO_T\">"
                        "<startTeam class=\"team\">ONE</startTeam>"
                        "<board>"
                            "<field x=\"0\" y=\"0\" content=\"GREEN\"/>"
                            "<field x=\"19\" y=\"0\" content=\"YELLOW\"/>"
                            "<field x=\"0\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"1\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"2\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"17\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"18\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"19\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"0\" y=\"2\" content=\"GREEN\"/>"
                            "<field x=\"16\" y=\"2\" content=\"YELLOW\"/>"
                            "<field x=\"19\" y=\"2\" content=\"YELLOW\"/>"
                            "<field x=\"16\" y=\"3\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"3\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"4\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"18\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"17\" y=\"16\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"16\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"3\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"18\" y=\"17\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"1\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"2\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"18\" y=\"18\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"3\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"17\" y=\"19\" content=\"RED\"/>"
                            "<field x=\"18\" y=\"19\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"19\" content=\"RED\"/>"
                        "</board>"
                        "<blueShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</blueShapes>"
                        "<yellowShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</yellowShapes>"
                        "<redShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</redShapes>"
                        "<greenShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</greenShapes>"
                        "<lastMoveMono class=\"linked-hash-map\"/>"
                        "<orderedColors>"
                            "<color>YELLOW</color>"
                            "<color>RED</color>"
                        "</orderedColors>"
                        "<first displayName=\"One\">"
                            "<color class=\"team\">ONE</color>"
                        "</first>"
                        "<second displayName=\"Two\">"
                            "<color class=\"team\">TWO</color>"
                        "</second>"
                        "<lastMove class=\"sc.plugin2021.SetMove\">"
                            "<piece color=\"RED\" kind=\"PENTO_U\" rotation=\"MIRROR\" isFlipped=\"true\">"
                            "<position x=\"17\" y=\"15\"/>"
                            "</piece>"
                        "</lastMove>"
                        "<startColor>BLUE</startColor>"
                        "</state>"
                    "</data>"
                "</room>"
                "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"memento\">"
                        "<state class=\"state\" currentColorIndex=\"3\" turn=\"7\" round=\"2\" startPiece=\"PENTO_T\">"
                        "<startTeam class=\"team\">ONE</startTeam>"
                        "<board>"
                            "<field x=\"0\" y=\"0\" content=\"GREEN\"/>"
                            "<field x=\"19\" y=\"0\" content=\"YELLOW\"/>"
                            "<field x=\"0\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"1\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"2\" y=\"1\" content=\"GREEN\"/>"
                            "<field x=\"17\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"18\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"19\" y=\"1\" content=\"YELLOW\"/>"
                            "<field x=\"0\" y=\"2\" content=\"GREEN\"/>"
                            "<field x=\"16\" y=\"2\" content=\"YELLOW\"/>"
                            "<field x=\"19\" y=\"2\" content=\"YELLOW\"/>"
                            "<field x=\"16\" y=\"3\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"3\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"4\" content=\"YELLOW\"/>"
                            "<field x=\"17\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"18\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"15\" content=\"RED\"/>"
                            "<field x=\"17\" y=\"16\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"16\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"3\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"17\" content=\"BLUE\"/>"
                            "<field x=\"18\" y=\"17\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"1\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"2\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"18\" content=\"BLUE\"/>"
                            "<field x=\"18\" y=\"18\" content=\"RED\"/>"
                            "<field x=\"0\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"3\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"4\" y=\"19\" content=\"BLUE\"/>"
                            "<field x=\"17\" y=\"19\" content=\"RED\"/>"
                            "<field x=\"18\" y=\"19\" content=\"RED\"/>"
                            "<field x=\"19\" y=\"19\" content=\"RED\"/>"
                        "</board>"
                        "<blueShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</blueShapes>"
                        "<yellowShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</yellowShapes>"
                        "<redShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</redShapes>"
                        "<greenShapes class=\"linked-hash-set\">"
                            "<shape>MONO</shape>"
                            "<shape>DOMINO</shape>"
                            "<shape>TRIO_L</shape>"
                            "<shape>TRIO_I</shape>"
                            "<shape>TETRO_O</shape>"
                            "<shape>TETRO_T</shape>"
                            "<shape>TETRO_I</shape>"
                            "<shape>TETRO_L</shape>"
                            "<shape>TETRO_Z</shape>"
                            "<shape>PENTO_L</shape>"
                            "<shape>PENTO_V</shape>"
                            "<shape>PENTO_S</shape>"
                            "<shape>PENTO_Z</shape>"
                            "<shape>PENTO_I</shape>"
                            "<shape>PENTO_P</shape>"
                            "<shape>PENTO_W</shape>"
                            "<shape>PENTO_U</shape>"
                            "<shape>PENTO_R</shape>"
                            "<shape>PENTO_X</shape>"
                            "<shape>PENTO_Y</shape>"
                        "</greenShapes>"
                        "<lastMoveMono class=\"linked-hash-map\"/>"
                        "<orderedColors>"
                            "<color>BLUE</color>"
                            "<color>YELLOW</color>"
                            "<color>GREEN</color>"
                        "</orderedColors>"
                        "<first displayName=\"One\">"
                            "<color class=\"team\">ONE</color>"
                        "</first>"
                        "<second displayName=\"Two\">"
                            "<color class=\"team\">TWO</color>"
                        "</second>"
                        "<lastMove class=\"sc.plugin2021.SkipMove\">"
                            "<color>RED</color>"
                        "</lastMove>"
                        "<startColor>BLUE</startColor>"
                        "</state>"
                    "</data>"
                "</room>";
        #pragma endregion
        parser.splitAndParseMessages(inp, result);

        REQUIRE(result.size() == 3);

        //? Not flipped
        REQUIRE(result[0].type == MsgType::GAMESTATE);

        auto payloadNotFlipped = std::any_cast<MementoMsg>(result[0].payload);

        REQUIRE(payloadNotFlipped.lastMove.has_value());
        
        REQUIRE(payloadNotFlipped.lastMove.value() == 33139);

        REQUIRE(payloadNotFlipped.startPiece == 0);
        REQUIRE(payloadNotFlipped.currentTurn == 7);

        //? Flipped
        REQUIRE(result[1].type == MsgType::GAMESTATE);

        auto payloadFlipped = std::any_cast<MementoMsg>(result[1].payload);

        REQUIRE(payloadFlipped.lastMove.has_value());
        
        REQUIRE(payloadFlipped.lastMove.value() == 34739);

        REQUIRE(payloadFlipped.startPiece == 0);
        REQUIRE(payloadFlipped.currentTurn == 7);

        //? Skipped
        REQUIRE(result[2].type == MsgType::GAMESTATE);

        auto payloadSkipped = std::any_cast<MementoMsg>(result[2].payload);

        REQUIRE_FALSE(payloadSkipped.lastMove.has_value());

        REQUIRE(payloadSkipped.startPiece == 0);
        REQUIRE(payloadSkipped.currentTurn == 7);

        // We can test colorsInGame only here as it always holds the most current values (last to parse at the beginning of this TestCase)
        const std::vector<PieceColor>* const colorsIG = parser.getColorsInGamePtr();
        REQUIRE(colorsIG->size() == 3);
        REQUIRE(std::find(colorsIG->begin(), colorsIG->end(), PieceColor::BLUE)   != colorsIG->end());
        REQUIRE(std::find(colorsIG->begin(), colorsIG->end(), PieceColor::YELLOW) != colorsIG->end());
        REQUIRE(std::find(colorsIG->begin(), colorsIG->end(), PieceColor::GREEN)  != colorsIG->end());

        REQUIRE_FALSE(std::find(colorsIG->begin(), colorsIG->end(), PieceColor::RED) != colorsIG->end());
    }

    SECTION("Can make move") {
        inp = "<joined roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\"/>";
        parser.splitAndParseMessages(inp, result);

        SECTION("Can make SetMove") {
            std::string expected =  "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">\n"
                                    " <data class=\"sc.plugin2021.SetMove\">\n"
                                        "  <piece color=\"GREEN\" kind=\"PENTO_U\" rotation=\"MIRROR\" isFlipped=\"false\">\n"
                                            "   <position x=\"0\" y=\"0\" />\n"
                                        "  </piece>\n"
                                    " </data>\n"
                                "</room>\n";
            auto move = Move(10, Position(2, 1), Rotation::PI, PieceColor::GREEN);
            REQUIRE(parser.makeMoveMessage(&move) == expected);
        }

        SECTION("Can make SkipMove") {
            // Set turn->7 inside XMLParser so that a color for the skip can be determined (Last to move was RED -> Now GREEN)
            #pragma region InpSkipMove
            inp =   "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                        "<data class=\"memento\">"
                            "<state class=\"state\" currentColorIndex=\"3\" turn=\"7\" round=\"2\" startPiece=\"PENTO_T\">"
                            "<startTeam class=\"team\">ONE</startTeam>"
                            "<board>"
                                "<field x=\"0\" y=\"0\" content=\"GREEN\"/>"
                                "<field x=\"19\" y=\"0\" content=\"YELLOW\"/>"
                                "<field x=\"0\" y=\"1\" content=\"GREEN\"/>"
                                "<field x=\"1\" y=\"1\" content=\"GREEN\"/>"
                                "<field x=\"2\" y=\"1\" content=\"GREEN\"/>"
                                "<field x=\"17\" y=\"1\" content=\"YELLOW\"/>"
                                "<field x=\"18\" y=\"1\" content=\"YELLOW\"/>"
                                "<field x=\"19\" y=\"1\" content=\"YELLOW\"/>"
                                "<field x=\"0\" y=\"2\" content=\"GREEN\"/>"
                                "<field x=\"16\" y=\"2\" content=\"YELLOW\"/>"
                                "<field x=\"19\" y=\"2\" content=\"YELLOW\"/>"
                                "<field x=\"16\" y=\"3\" content=\"YELLOW\"/>"
                                "<field x=\"17\" y=\"3\" content=\"YELLOW\"/>"
                                "<field x=\"17\" y=\"4\" content=\"YELLOW\"/>"
                                "<field x=\"17\" y=\"15\" content=\"RED\"/>"
                                "<field x=\"18\" y=\"15\" content=\"RED\"/>"
                                "<field x=\"19\" y=\"15\" content=\"RED\"/>"
                                "<field x=\"17\" y=\"16\" content=\"RED\"/>"
                                "<field x=\"19\" y=\"16\" content=\"RED\"/>"
                                "<field x=\"0\" y=\"17\" content=\"BLUE\"/>"
                                "<field x=\"3\" y=\"17\" content=\"BLUE\"/>"
                                "<field x=\"4\" y=\"17\" content=\"BLUE\"/>"
                                "<field x=\"18\" y=\"17\" content=\"RED\"/>"
                                "<field x=\"0\" y=\"18\" content=\"BLUE\"/>"
                                "<field x=\"1\" y=\"18\" content=\"BLUE\"/>"
                                "<field x=\"2\" y=\"18\" content=\"BLUE\"/>"
                                "<field x=\"4\" y=\"18\" content=\"BLUE\"/>"
                                "<field x=\"18\" y=\"18\" content=\"RED\"/>"
                                "<field x=\"0\" y=\"19\" content=\"BLUE\"/>"
                                "<field x=\"3\" y=\"19\" content=\"BLUE\"/>"
                                "<field x=\"4\" y=\"19\" content=\"BLUE\"/>"
                                "<field x=\"17\" y=\"19\" content=\"RED\"/>"
                                "<field x=\"18\" y=\"19\" content=\"RED\"/>"
                                "<field x=\"19\" y=\"19\" content=\"RED\"/>"
                            "</board>"
                            "<blueShapes class=\"linked-hash-set\">"
                                "<shape>MONO</shape>"
                                "<shape>DOMINO</shape>"
                                "<shape>TRIO_L</shape>"
                                "<shape>TRIO_I</shape>"
                                "<shape>TETRO_O</shape>"
                                "<shape>TETRO_T</shape>"
                                "<shape>TETRO_I</shape>"
                                "<shape>TETRO_L</shape>"
                                "<shape>TETRO_Z</shape>"
                                "<shape>PENTO_L</shape>"
                                "<shape>PENTO_V</shape>"
                                "<shape>PENTO_S</shape>"
                                "<shape>PENTO_Z</shape>"
                                "<shape>PENTO_I</shape>"
                                "<shape>PENTO_P</shape>"
                                "<shape>PENTO_W</shape>"
                                "<shape>PENTO_R</shape>"
                                "<shape>PENTO_X</shape>"
                                "<shape>PENTO_Y</shape>"
                            "</blueShapes>"
                            "<yellowShapes class=\"linked-hash-set\">"
                                "<shape>MONO</shape>"
                                "<shape>DOMINO</shape>"
                                "<shape>TRIO_L</shape>"
                                "<shape>TRIO_I</shape>"
                                "<shape>TETRO_O</shape>"
                                "<shape>TETRO_T</shape>"
                                "<shape>TETRO_I</shape>"
                                "<shape>TETRO_L</shape>"
                                "<shape>PENTO_L</shape>"
                                "<shape>PENTO_V</shape>"
                                "<shape>PENTO_S</shape>"
                                "<shape>PENTO_Z</shape>"
                                "<shape>PENTO_I</shape>"
                                "<shape>PENTO_P</shape>"
                                "<shape>PENTO_W</shape>"
                                "<shape>PENTO_U</shape>"
                                "<shape>PENTO_R</shape>"
                                "<shape>PENTO_X</shape>"
                                "<shape>PENTO_Y</shape>"
                            "</yellowShapes>"
                            "<redShapes class=\"linked-hash-set\">"
                                "<shape>MONO</shape>"
                                "<shape>DOMINO</shape>"
                                "<shape>TRIO_L</shape>"
                                "<shape>TRIO_I</shape>"
                                "<shape>TETRO_O</shape>"
                                "<shape>TETRO_T</shape>"
                                "<shape>TETRO_I</shape>"
                                "<shape>TETRO_L</shape>"
                                "<shape>TETRO_Z</shape>"
                                "<shape>PENTO_L</shape>"
                                "<shape>PENTO_V</shape>"
                                "<shape>PENTO_S</shape>"
                                "<shape>PENTO_Z</shape>"
                                "<shape>PENTO_I</shape>"
                                "<shape>PENTO_P</shape>"
                                "<shape>PENTO_W</shape>"
                                "<shape>PENTO_R</shape>"
                                "<shape>PENTO_X</shape>"
                                "<shape>PENTO_Y</shape>"
                            "</redShapes>"
                            "<greenShapes class=\"linked-hash-set\">"
                                "<shape>MONO</shape>"
                                "<shape>DOMINO</shape>"
                                "<shape>TRIO_L</shape>"
                                "<shape>TRIO_I</shape>"
                                "<shape>TETRO_O</shape>"
                                "<shape>TETRO_T</shape>"
                                "<shape>TETRO_I</shape>"
                                "<shape>TETRO_L</shape>"
                                "<shape>TETRO_Z</shape>"
                                "<shape>PENTO_L</shape>"
                                "<shape>PENTO_V</shape>"
                                "<shape>PENTO_S</shape>"
                                "<shape>PENTO_Z</shape>"
                                "<shape>PENTO_I</shape>"
                                "<shape>PENTO_P</shape>"
                                "<shape>PENTO_W</shape>"
                                "<shape>PENTO_U</shape>"
                                "<shape>PENTO_R</shape>"
                                "<shape>PENTO_X</shape>"
                                "<shape>PENTO_Y</shape>"
                            "</greenShapes>"
                            "<lastMoveMono class=\"linked-hash-map\"/>"
                            "<orderedColors>"
                                "<color>BLUE</color>"
                                "<color>RED</color>"
                                "<color>GREEN</color>"
                            "</orderedColors>"
                            "<first displayName=\"One\">"
                                "<color class=\"team\">ONE</color>"
                            "</first>"
                            "<second displayName=\"Two\">"
                                "<color class=\"team\">TWO</color>"
                            "</second>"
                            "<lastMove class=\"sc.plugin2021.SetMove\">"
                                "<piece color=\"RED\" kind=\"PENTO_U\" rotation=\"MIRROR\" isFlipped=\"false\">"
                                "<position x=\"17\" y=\"15\"/>"
                                "</piece>"
                            "</lastMove>"
                            "<startColor>BLUE</startColor>"
                            "</state>"
                        "</data>"
                    "</room>";
            #pragma endregion
            parser.splitAndParseMessages(inp, result);

            std::string expected =  "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">\n"
                                    " <data class=\"sc.plugin2021.SkipMove\">\n"
                                        "  <color>GREEN</color>\n"
                                    " </data>\n"
                                "</room>\n";
            REQUIRE(parser.makeMoveMessage(nullptr) == expected);
        }
    }

    SECTION("Can parse MoveRequest") {
        inp =   "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"sc.framework.plugins.protocol.MoveRequest\"/>"
                "</room>";
        parser.splitAndParseMessages(inp, result);

        REQUIRE(result.size() == 1);
        REQUIRE(result[0].type == MsgType::MOVEREQUEST);

        auto payload = std::any_cast<nullptr_t>(result[0].payload);
        REQUIRE(payload == nullptr);
    }

    SECTION("Can parse WelcomeMessage") {
        inp =   "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"welcomeMessage\" color=\"one\"/>"
                "</room>"
                "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"welcomeMessage\" color=\"two\"/>"
                "</room>";
        parser.splitAndParseMessages(inp, result);

        REQUIRE(result.size() == 2);

        //? One (Blue)
        REQUIRE(result[0].type == MsgType::WELCOME);

        auto payloadOne = std::any_cast<PlayerColor>(result[0].payload); 
        REQUIRE(payloadOne == PlayerColor::BLUE);

        //? Two (Red)
        REQUIRE(result[1].type == MsgType::WELCOME);

        auto payloadTwo = std::any_cast<PlayerColor>(result[1].payload); 
        REQUIRE(payloadTwo == PlayerColor::RED);
    }

    SECTION("Can parse Left") {
        inp = "<left roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\"/>";
        parser.splitAndParseMessages(inp, result);

        REQUIRE(result.size() == 1);
        REQUIRE(result[0].type == MsgType::LEFT);

        auto payload = std::any_cast<nullptr_t>(result[0].payload);
        REQUIRE(payload == nullptr);
    }

    SECTION("Can parse Result") {
        #pragma region InpResult
        inp =   "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"result\">"
                        "<definition>"
                            "<fragment name=\"Gewinner\">"
                                "<aggregation>SUM</aggregation>"
                                "<relevantForRanking>true</relevantForRanking>"
                            "</fragment>"
                            "<fragment name=\"Ôêà Punkte\">"
                                "<aggregation>AVERAGE</aggregation>"
                                "<relevantForRanking>true</relevantForRanking>"
                            "</fragment>"
                        "</definition>"
                        "<score cause=\"LEFT\" reason=\"Der Spieler hat das Spiel verlassen\">"
                            "<part>0</part>"
                            "<part>2</part>"
                        "</score>"
                        "<score cause=\"REGULAR\" reason=\"\">"
                            "<part>2</part>"
                            "<part>4</part>"
                        "</score>"
                        "<winner displayName=\"One\">"
                            "<color class=\"team\">ONE</color>"
                        "</winner>"
                        "<winner displayName=\"Two\">"
                            "<color class=\"team\">TWO</color>"
                        "</winner>"
                    "</data>"
                "</room>"
                "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"result\">"
                        "<definition>"
                            "<fragment name=\"Gewinner\">"
                                "<aggregation>SUM</aggregation>"
                                "<relevantForRanking>true</relevantForRanking>"
                            "</fragment>"
                            "<fragment name=\"Ôêà Punkte\">"
                                "<aggregation>AVERAGE</aggregation>"
                                "<relevantForRanking>true</relevantForRanking>"
                            "</fragment>"
                        "</definition>"
                        "<score cause=\"RULE_VIOLATION\" reason=\"Der Spieler hat das Spiel verlassen\">"
                            "<part>1</part>"
                            "<part>17</part>"
                        "</score>"
                        "<score cause=\"SOFT_TIMEOUT\" reason=\"\">"
                            "<part>1</part>"
                            "<part>17</part>"
                        "</score>"
                        "<winner displayName=\"One\">"
                            "<color class=\"team\">ONE</color>"
                        "</winner>"
                        "<winner displayName=\"Two\">"
                            "<color class=\"team\">TWO</color>"
                        "</winner>"
                    "</data>"
                "</room>"
                "<room roomId=\"0a1b2c3d-4e5f-6g7h-i8j9-k0l1m2n3o4p5\">"
                    "<data class=\"result\">"
                        "<definition>"
                            "<fragment name=\"Gewinner\">"
                                "<aggregation>SUM</aggregation>"
                                "<relevantForRanking>true</relevantForRanking>"
                            "</fragment>"
                            "<fragment name=\"Ôêà Punkte\">"
                                "<aggregation>AVERAGE</aggregation>"
                                "<relevantForRanking>true</relevantForRanking>"
                            "</fragment>"
                        "</definition>"
                        "<score cause=\"REGULAR\" reason=\"Der Spieler hat das Spiel verlassen\">"
                            "<part>2</part>"
                            "<part>13</part>"
                        "</score>"
                        "<score cause=\"HARD_TIMEOUT\" reason=\"\">"
                            "<part>0</part>"
                            "<part>12</part>"
                        "</score>"
                        "<winner displayName=\"One\">"
                            "<color class=\"team\">ONE</color>"
                        "</winner>"
                        "<winner displayName=\"Two\">"
                            "<color class=\"team\">TWO</color>"
                        "</winner>"
                    "</data>"
                "</room>"
                ;
        #pragma endregion
        parser.splitAndParseMessages(inp, result);

        REQUIRE(result.size() == 3);

        //* 1
        REQUIRE(result[0].type == MsgType::RESULT);

        auto payload1 = std::any_cast<ResultMsg>(result[0].payload);

        //? End (Tournament points)
        REQUIRE(payload1.end[0] == ResultMsg::ResultEnd::LOSE);
        REQUIRE(payload1.end[1] == ResultMsg::ResultEnd::WIN);

        //? Score
        REQUIRE(payload1.score[0] == 2);
        REQUIRE(payload1.score[1] == 4);

        //? Cause
        REQUIRE(payload1.cause[0] == ResultMsg::ResultCause::LEFT);
        REQUIRE(payload1.cause[1] == ResultMsg::ResultCause::REGULAR);


        //* 2
        REQUIRE(result[1].type == MsgType::RESULT);

        auto payload2 = std::any_cast<ResultMsg>(result[1].payload);

        //? End (Tournament points)
        REQUIRE(payload2.end[0] == ResultMsg::ResultEnd::DRAW);
        REQUIRE(payload2.end[1] == ResultMsg::ResultEnd::DRAW);

        //? Score
        REQUIRE(payload2.score[0] == 17);
        REQUIRE(payload2.score[1] == 17);

        //? Cause
        REQUIRE(payload2.cause[0] == ResultMsg::ResultCause::RULE_VIOLATION);
        REQUIRE(payload2.cause[1] == ResultMsg::ResultCause::SOFT_TIMEOUT);


        //* 3
        REQUIRE(result[2].type == MsgType::RESULT);

        auto payload3 = std::any_cast<ResultMsg>(result[2].payload);

        //? End (Tournament points)
        REQUIRE(payload3.end[0] == ResultMsg::ResultEnd::WIN);
        REQUIRE(payload3.end[1] == ResultMsg::ResultEnd::LOSE);

        //? Score
        REQUIRE(payload3.score[0] == 13);
        REQUIRE(payload3.score[1] == 12);

        //? Cause
        REQUIRE(payload3.cause[0] == ResultMsg::ResultCause::REGULAR);
        REQUIRE(payload3.cause[1] == ResultMsg::ResultCause::HARD_TIMEOUT);
    }
}
