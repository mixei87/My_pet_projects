#include "controller_game.h"

GameController::GameController(QObject* parent)
    : QObject(parent), m_gameModel(9, 9) {
  DBmanager db(QDir::currentPath() + "/../resources/game.db");
}

GameController::~GameController() {}

GameModel* GameController::getModel() { return &m_gameModel; }
