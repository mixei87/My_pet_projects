#include "controller_game.h"

GameController::GameController(QObject* parent) : QObject(parent) {
  m_gameModel = new GameModel();
}

GameController::~GameController() {
  qDebug() << "destructor of controller";
  delete m_gameModel;
}

GameModel* GameController::getModel() { return m_gameModel; }
