#include "GameManager.hpp"

namespace Logic {
    
    GameManager::GameManager(const std::vector<Model::PieceColor>* const colorsInGame) : colorsInGame(colorsInGame) {}

    void GameManager::setColor(const Model::PlayerColor& color) {
        ownColor = color;
    }

    void GameManager::updateWithMemento(const App::MementoMsg& memento) {
        /* code */
    }

    const Model::Move* GameManager::moveRequest() {
        // This will throw a ptr error when dereferenced (Just so test compilation works)
        Model::Move m = Model::Move(0, Util::Position(0, 0), Model::Rotation::ZERO, Model::PieceColor::NONE);
        return &m;
    }

}
